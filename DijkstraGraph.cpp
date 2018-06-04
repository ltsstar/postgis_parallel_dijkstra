//
// Created by Michel Kunkler on 24.04.18.
//

#include "DijkstraGraph.h"
#include "DijkstraNode.h"

void DijkstraGraph::addNode(DijkstraNode * node) {
    this->nodes.insert( std::pair<NodeCord, DijkstraNode *>(node->cord, node) );
    this->nodes_id.insert( std::pair<nodeID, DijkstraNode *>(node->id, node) );
}

DijkstraNode* DijkstraGraph::getNode(int64_t osm_id) {
    for(int i=0; i<100; i++) { //very bad style
        nodeID node_id = nodeID(osm_id, i);
        if (nodes_id.find(node_id) != nodes_id.end()) {
            DijkstraNode *node = nodes_id.find(node_id)->second;
            return node;
        }
    }
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

DijkstraGraph::DijkstraGraph() {
    nodes = std::map<NodeCord, DijkstraNode*>();
    nodes_id = std::map<nodeID, DijkstraNode*>();
}
