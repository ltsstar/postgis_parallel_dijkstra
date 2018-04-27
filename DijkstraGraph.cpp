//
// Created by Michel Kunkler on 24.04.18.
//

#include "DijkstraGraph.h"
#include "DijkstraNode.h"

void DijkstraGraph::addNode(DijkstraNode * node) {
    this->nodes.insert( std::pair<node_cord, DijkstraNode *>(node->cord, node));
}

DijkstraNode* DijkstraGraph::getNode(int64_t osm_id) {
    for( auto node = this->nodes.begin();
         node != this->nodes.end();
         ++node ) {
        if( node->second->id.osm_id == osm_id ) {
            return node->second;
        }
    }
    return nullptr;
}

DijkstraNode * DijkstraGraph::makeNodeStarting(int64_t osm_id, uint32_t dijkstra_class) {
    if( this->getNode(osm_id) ) {
        DijkstraNode * node = this->getNode(osm_id);
        node->dijkstra_class = dijkstra_class;
        node->distance = 0;
        return node;
    }
    return nullptr;
}
