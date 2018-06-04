//
// Created by Michel Kunkler on 24.04.18.
//

#ifndef PARALLEL_DIJKSTRA_DIJKSTRAGRAPH_H
#define PARALLEL_DIJKSTRA_DIJKSTRAGRAPH_H

#include <map>
#include <cstdint>
#include "DijkstraNode.h"


class DijkstraGraph {
private:
public:
    std::map<NodeCord, DijkstraNode*> nodes;
    std::map<nodeID, DijkstraNode*> nodes_id;
    void addNode(DijkstraNode * node);
    DijkstraNode* getNode(int64_t osm_id);
    DijkstraNode * makeNodeStarting(int64_t osm_id, uint32_t dijkstra_class);
    DijkstraGraph();
};


#endif //PARALLEL_DIJKSTRA_DIJKSTRAGRAPH_H
