//
// Created by Michel Kunkler on 23.04.18.
//

#include "DijkstraNode.h"

bool operator< (const nodeID a, const nodeID b) {
    return a.osm_id < b.osm_id || (a.osm_id == b.osm_id && a.sub_id < b.sub_id);
}

bool operator< (const node_cord a, const node_cord b) {
    return a.lat < b.lat || (a.lat == b.lat && a.lon < b.lon);
}

bool operator== (const node_cord a, const node_cord b) {
    return a.lat == b.lat && a.lon == b.lon;
}

uint32_t DijkstraNode::wgs84_lat_to_int(double lat) {
    long intRange = 1L << 32; // ==((long)int.MaxValue - int.MinValue)
    double inputRange = 90 - (-90);
    return (uint32_t)(intRange * (lat - (-90)) / inputRange);
}

uint32_t DijkstraNode::wgs84_lon_to_int(double lon) {
    long intRange = 1L << 32; // ==((long)int.MaxValue - int.MinValue)
    double inputRange = 180 - (-180);
    return (uint32_t)(intRange * (lon - (-180)) / inputRange);
}


void DijkstraNode::addEdge(DijkstraNode *other_node) {
    this->other_nodes.push_back(other_node);
}

void DijkstraNode::addBidirectional(DijkstraNode *other_node) {
    other_node->addEdge(this);
    this->addEdge(other_node);
}

DijkstraNode::DijkstraNode(nodeID id, double wgs_lat, double wgs_lon)
: id(id), distance((uint32_t)-1), marked(false), cord({0, 0}), dijkstra_class(0)
{
    this->cord.lat = this->wgs84_lat_to_int(wgs_lat);
    this->cord.lon = this->wgs84_lon_to_int(wgs_lon);
}