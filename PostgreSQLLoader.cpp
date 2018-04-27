//
// Created by Michel Kunkler on 24.04.18.
//

#include <iostream>
#include <boost/algorithm/string.hpp>
#include "PostgreSQLLoader.h"
#include "DijkstraNode.h"


std::string PostgreSQLLoader::db_name = "gis";
std::string PostgreSQLLoader::user_name = "michel";

PostgreSQLLoader::PostgreSQLLoader() {
    char conninfo[200];
    sprintf(conninfo, "dbname = %s user = %s", db_name.c_str(), user_name.c_str());

    conn = PQconnectdb(conninfo);
    if (PQstatus(conn) != CONNECTION_OK) {
        std::cerr << "Connection to database failed: "
                    << PQerrorMessage(conn);
        PQfinish(conn);
    }
}

PostgreSQLLoader::~PostgreSQLLoader() {
    PQfinish(conn);
}

DijkstraGraph PostgreSQLLoader::loadStreets() {
    DijkstraGraph dijkstraGraph = DijkstraGraph();

    PGresult *res;
    if (!PQsendQuery(conn,
                     "select osm_id, st_astext(st_transform(way, 4326)) from planet_osm_line where highway is not null"))
    {
        fprintf(stderr, "Send query failed: %s", PQerrorMessage(conn));
        PQfinish(conn);
        exit(1);
    }

    int64_t osm_id;
    char* way;
    res = PQgetResult(conn);
    while(res != nullptr) {
        for (int64_t i= 0; i < PQntuples(res); i++) {
            osm_id = std::stoull(PQgetvalue(res, i, 0));
            way = PQgetvalue(res, i, 1);
            std::vector<std::array<double, 2>> coordinates = this->getCoordinatesFromLineString(std::string(way));
            this->addNodesToGraph(&dijkstraGraph, osm_id, coordinates);
        }
        PQclear(res);
        res = PQgetResult(conn);
    }

    return dijkstraGraph;
}

std::vector<std::array<double, 2>> PostgreSQLLoader::getCoordinatesFromLineString(std::string line_string) {
    std::vector<std::array<double, 2>> coordinate_list;

    line_string.pop_back();
    line_string = line_string.substr(11); // remove "LINESTRING(" and ")"

    std::vector<std::string> splits;
    boost::split(splits, line_string, boost::is_any_of(","));

    for(std::vector<std::string>::iterator it = splits.begin();
            it != splits.end();
            ++it) {
        std::vector<std::string> coordinates;
        boost::split(coordinates, *it, boost::is_any_of(" "));
        coordinate_list.push_back({stod(coordinates[0]), stod(coordinates[1])});
    }
    return coordinate_list;
}

void PostgreSQLLoader::addNodesToGraph(DijkstraGraph *graph, int64_t osm_id,
                                       std::vector<std::array<double, 2>> coordinates) {
    uint32_t sub_id = 0;
    DijkstraNode *last_node;
    for(auto it = coordinates.begin();
        it != coordinates.end();
        ++it) {

        nodeID node_id;
        node_id.osm_id = osm_id;
        node_id.sub_id = sub_id;
        DijkstraNode *node = new DijkstraNode(node_id, (*it)[0], (*it)[1]);

        // check if node exists in graph (== intersection)
        auto graph_it = graph->nodes.find(node->cord);
        if(graph_it !=  graph->nodes.end()) {
            // node exists, don't add new
            delete node;
            node = graph_it->second;
        }

        if(it != coordinates.begin()) {
            node->addBidirectional(last_node);
        }

        graph->addNode(node);
        last_node = node;
        sub_id++;
    }

}

void PostgreSQLLoader::saveClassDistances(DijkstraGraph *graph) {
    int c = 0;
    for( auto it = graph->nodes.begin();
            it != graph->nodes.end();
            ++it ) {
        if( it->second->id.sub_id == 0) {
            this->updatePostgresLine(it->second->id.osm_id, it->second->dijkstra_class, it->second->distance);
        } else {
            continue;
        }
    }
    if (!PQsendQuery(this->conn, "COMMIT"))
    {
        fprintf(stderr, "Send query failed: %s", PQerrorMessage(conn));
        PQfinish(conn);
        exit(1);
    }
}

void PostgreSQLLoader::updatePostgresLine(int64_t osm_id, int32_t dijkstra_class, int32_t dijkstra_distance) {
    PGresult *res;
    char query_str[200];
    sprintf(query_str,
            "update planet_osm_line set dijkstra_class=%d where osm_id=%d",
            dijkstra_class, osm_id);

    res = PQexec(this->conn, query_str);
    if (!res)
    {
        fprintf(stderr, "Send query failed: %s", PQresultStatus(res));
        PQfinish(conn);
        exit(1);
    }
}
