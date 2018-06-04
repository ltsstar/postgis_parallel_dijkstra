//
// Created by Michel Kunkler on 23.04.18.
//

#ifndef PARALLEL_DIJKSTRA_DIJKSTRANODE_H
#define PARALLEL_DIJKSTRA_DIJKSTRANODE_H

#include <stdint.h>
#include <vector>

typedef struct nodeID {
    int64_t osm_id;
    uint32_t sub_id;
    bool operator< (const nodeID& b) const;
    bool operator== (const nodeID& b) const;
    nodeID(const nodeID &node_id);
    nodeID(int64_t osm_id, uint32_t sub_id);
} nodeID;

typedef struct NodeCord {
    uint32_t lat;
    uint32_t lon;
    bool operator< (const NodeCord& b) const;
    bool operator== (const NodeCord& b) const;
    NodeCord(const NodeCord &b);
    NodeCord(uint32_t lon, uint32_t lat);
    NodeCord();
} NodeCord;


class DijkstraNode {
private:
    uint32_t wgs84_lat_to_int(double lat);
    uint32_t wgs84_lon_to_int(double lon);
public:
    nodeID id;
    NodeCord cord;
    uint32_t dijkstra_class;
    uint32_t distance;
    bool marked;
    std::vector<DijkstraNode *> other_nodes;

    double wgs84_lat();
    double wgs84_lon();

    void addEdge(DijkstraNode *other_node);
    void addBidirectional(DijkstraNode *other_node);
    DijkstraNode(nodeID id, double wgs_lat, double wgs_lon);
    DijkstraNode(const DijkstraNode &dijkstra_node);
    ~DijkstraNode();
};


#endif //PARALLEL_DIJKSTRA_DIJKSTRANODE_H
