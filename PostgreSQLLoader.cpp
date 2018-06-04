//
// Created by Michel Kunkler on 24.04.18.
//

#include <iostream>
#include <boost/algorithm/string.hpp>
#include "PostgreSQLLoader.h"
#include "DijkstraNode.h"

std::string PostgreSQLLoader::db_name = "gis_liechtenstein";
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

DijkstraGraph* PostgreSQLLoader::loadStreets() {
    DijkstraGraph * dijkstraGraph = new DijkstraGraph();

    PGresult *res;
    if (!PQsendQuery(conn,
                     "select osm_id, st_astext(st_transform(way, 4326)) from planet_osm_line where highway is not null \
                     and osm_id > 0"))
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
            this->addNodesToGraph(dijkstraGraph, osm_id, coordinates);
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
    DijkstraNode *last_node = nullptr;
    for(auto it = coordinates.begin();
        it != coordinates.end();
        ++it) {

        nodeID node_id = nodeID(osm_id, sub_id);

        DijkstraNode *node = new DijkstraNode(node_id, (*it)[0], (*it)[1]);

        // check if node exists in graph (== intersection)
        auto graph_it = graph->nodes.find(node->cord);
        if(graph_it !=  graph->nodes.end()) {
            // node exists, don't add new
            delete node;
            node = graph_it->second;
        } else {
            graph->addNode(node);
        }
        if(last_node != nullptr) {
            node->addBidirectional(last_node);
            sub_id++;
        }

        last_node = node;
    }
}

void PostgreSQLLoader::saveClassDistances(DijkstraGraph *graph) {
    int c = 0;
    for( auto it = graph->nodes.begin();
            it != graph->nodes.end();
            ++it ) {
        for( auto it2 = it->second->other_nodes.begin();
                it2 != it->second->other_nodes.end();
                ++it2) {
            if(it->second->cord < (*it2)->cord) {
                c++;
                this->insertPostgresLine(it->second, *it2);
            }
        }
    }
    std::cout << graph->nodes_id.size() << " size" << std::endl;
    std::cout << c << " insertions" << std::endl;
}

void PostgreSQLLoader::insertPostgresLine(DijkstraNode* first_node, DijkstraNode* second_node) {
    PGresult *res;
    char query_str[512];
    if (first_node->dijkstra_class == second_node->dijkstra_class) {
        double y1 = first_node->wgs84_lon();
        double x1 = first_node->wgs84_lat();
        double y2 = second_node->wgs84_lon();
        double x2 = second_node->wgs84_lat();

        sprintf(query_str,
                "insert into dijkstra_lines VALUES (%d, %d, %d,"
                "ST_SetSRID(ST_MakeLine(ST_Point(%lf, %lf), ST_Point(%lf, %lf)), 4326)"
                ");",
                first_node->id.osm_id, first_node->id.sub_id, first_node->dijkstra_class,
                x1, y1, x2, y2);
    } else {
        return;
    }
    res = PQexec(this->conn, query_str);
    if (!res)
    {
        fprintf(stderr, "Send query failed: %s", PQresultStatus(res));
        PQfinish(conn);
        exit(1);
    }
}
