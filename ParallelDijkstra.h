//
// Created by Michel Kunkler on 23.04.18.
//

#ifndef PARALLEL_DIJKSTRA_PARALLEL_DIJKSTRA_H
#define PARALLEL_DIJKSTRA_PARALLEL_DIJKSTRA_H

#include <stdint.h>
#include "DijkstraGraph.h"


class ParallelDijkstra {
private:
    DijkstraGraph * dijkstraGraph;
    std::vector<DijkstraNode*> node_heap;
public:
    ParallelDijkstra(DijkstraGraph * dijkstraGraph, std::vector<std::pair<int64_t, uint32_t>> starting_nodes);
    void ProcessHeap();
    void scansuc(DijkstraNode * node);
    uint32_t distance(DijkstraNode node1, DijkstraNode node2);
};


#endif //PARALLEL_DIJKSTRA_PARALLEL_DIJKSTRA_H
