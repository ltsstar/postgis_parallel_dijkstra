//
// Created by Michel Kunkler on 23.04.18.
//

#include <tuple>
#include "DijkstraNode.h"

bool nodeID::operator< (const nodeID& b) const {
    return (osm_id < b.osm_id) || (osm_id == b.osm_id && sub_id < b.sub_id);
}

bool nodeID::operator== (const nodeID& b) const {
    return osm_id == b.osm_id && sub_id == b.sub_id;
}

nodeID::nodeID(const nodeID &node_id) {
    osm_id = node_id.osm_id;
    sub_id = node_id.sub_id;
}

nodeID::nodeID(int64_t osm_id, uint32_t sub_id) : osm_id(osm_id), sub_id(sub_id){
}


bool NodeCord::operator< (const NodeCord& b) const {
    return lat < b.lat || (lat == b.lat && lon < b.lon);
}

bool NodeCord::operator== (const NodeCord& b) const {
    return lat == b.lat && lon == b.lon;
}

NodeCord::NodeCord(const NodeCord &b) {
    lat = b.lat;
    lon = b.lon;
}

NodeCord::NodeCord(uint32_t lon, uint32_t lat) : lon(lon), lat(lat) {
}

NodeCord::NodeCord() : lon(0), lat(0) {
}


uint32_t DijkstraNode::wgs84_lat_to_int(double lat) {
    /*
    long intRange = 1L << 32; // ==((long)int.MaxValue - int.MinValue)
    double inputRange = 90 - (-90);
    return (uint32_t)(intRange * (lat - (-90)) / inputRange);
     */
    return static_cast<uint32_t>(lat * 10000000 + 0.5);
}

uint32_t DijkstraNode::wgs84_lon_to_int(double lon) {
    /*
    long intRange = 1L << 32; // ==((long)int.MaxValue - int.MinValue)
    double inputRange = 180 - (-180);
    return (uint32_t)(intRange * (lon - (-180)) / inputRange);
     */
    return static_cast<uint32_t>(lon * 10000000 + 0.5);
}

double DijkstraNode::wgs84_lat()
{
    /*
    long intRange = 1L << 32; // ==((long)int.MaxValue - int.MinValue)
    double inputRange = 90 - (-90);
    return inputRange * ((double)this->cord.lat / intRange) + (-90);
     */
    return (double)this->cord.lat / 10000000;
}

double DijkstraNode::wgs84_lon()
{
    /*
    long intRange = 1L << 32; // ==((long)int.MaxValue - int.MinValue)
    double inputRange = 180 - (-180);
    return inputRange * ((double)this->cord.lon / intRange) + (-180);
     */
    return (double)this->cord.lon / 10000000;
}


void DijkstraNode::addEdge(DijkstraNode *other_node) {
    unsigned long vsize = other_nodes.size();
    this->other_nodes.push_back(other_node);
}

void DijkstraNode::addBidirectional(DijkstraNode *other_node) {
    other_node->addEdge(this);
    this->addEdge(other_node);
}

DijkstraNode::DijkstraNode(nodeID id, double wgs_lat, double wgs_lon)
: id(id), distance((uint32_t)-1), marked(false), cord(NodeCord()), dijkstra_class(0)
{
    this->other_nodes = std::vector<DijkstraNode *>();
    this->cord.lat = wgs84_lat_to_int(wgs_lat);
    this->cord.lon = wgs84_lat_to_int(wgs_lon);

}

DijkstraNode::DijkstraNode(const DijkstraNode &dijkstra_node) :
id(dijkstra_node.id), cord(dijkstra_node.cord) {
    other_nodes = std::vector<DijkstraNode *>(dijkstra_node.other_nodes.size());
    for(auto it = dijkstra_node.other_nodes.begin(); it != dijkstra_node.other_nodes.end();
            ++it) {
        other_nodes.emplace_back(*it);
    }
}

DijkstraNode::~DijkstraNode() {

}