//
// Created by Michel Kunkler on 24.04.18.
//

#ifndef PARALLEL_DIJKSTRA_POSTGRESQLLOADER_H
#define PARALLEL_DIJKSTRA_POSTGRESQLLOADER_H

#include <string>
#include <array>
#include <vector>
#include "libpq/libpq-fs.h"
#include "libpq-fe.h"
#include "DijkstraGraph.h"

class PostgreSQLLoader {
private:
    static std::string db_name;
    static std::string user_name;

    PGconn     *conn;
public:
    PostgreSQLLoader ();
    ~PostgreSQLLoader();
    DijkstraGraph * loadStreets();
    std::vector<std::array<double, 2>> getCoordinatesFromLineString(std::string line_string);
    void addNodesToGraph(DijkstraGraph *graph, int64_t osm_id, std::vector<std::array<double, 2>> coordinates);

    void saveClassDistances(DijkstraGraph *graph);
    void insertPostgresLine(DijkstraNode* first_node, DijkstraNode* second_node);
};
#endif //PARALLEL_DIJKSTRA_POSTGRESQLLOADER_H
