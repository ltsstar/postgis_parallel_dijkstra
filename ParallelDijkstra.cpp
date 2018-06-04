//
// Created by Michel Kunkler on 23.04.18.
//

#include <math.h>
#include "ParallelDijkstra.h"
#include "DijkstraNode.h"

ParallelDijkstra::ParallelDijkstra(DijkstraGraph * dijkstraGraph, std::vector<std::pair<int64_t, uint32_t>> starting_nodes) :
        dijkstraGraph(dijkstraGraph)
{
    for(auto it = starting_nodes.begin();
            it != starting_nodes.end();
            ++it) {
        DijkstraNode *node = this->dijkstraGraph->makeNodeStarting((*it).first, (*it).second);
        this->node_heap.push_back(node);
    }
    this->ProcessHeap();
}

void ParallelDijkstra::ProcessHeap() {
    while( this->node_heap.size() ) {
        DijkstraNode * node = this->node_heap.at(0);
        node->marked = true;
        this->scansuc(node);
        this->node_heap.erase(this->node_heap.begin());
    }
}

void ParallelDijkstra::scansuc(DijkstraNode *node) {
    for(auto it = node->other_nodes.begin();
            it != node->other_nodes.end();
            ++it) {
        if((*it)->marked)
            continue;
        uint32_t distance_delta = distance(*(*it), *node) + node->distance;
        if( (*it)->distance == (uint32_t)-1 ) {
            (*it)->distance = distance_delta;
            (*it)->dijkstra_class = node->dijkstra_class;
            this->node_heap.push_back((*it));
        } else if( (*it)->distance > distance_delta ) {
            (*it)->distance = distance_delta;
            (*it)->dijkstra_class = node->dijkstra_class;
        }
    }
}

uint32_t ParallelDijkstra::distance(DijkstraNode node1, DijkstraNode node2) {
    return static_cast<uint32_t>(
            sqrt((node1.cord.lat - node2.cord.lat) * (node1.cord.lat - node2.cord.lat)
            + (node1.cord.lon - node2.cord.lon) * (node1.cord.lon - node2.cord.lon)
            )
    );
}