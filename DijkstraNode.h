//
// Created by Michel Kunkler on 23.04.18.
//

#ifndef PARALLEL_DIJKSTRA_DIJKSTRANODE_H
#define PARALLEL_DIJKSTRA_DIJKSTRANODE_H

#include <stdint.h>
#include <vector>

typedef struct {int64_t osm_id; uint32_t sub_id;} nodeID;
bool operator< (const nodeID a, const nodeID b);

typedef struct {uint32_t lat; uint32_t lon;} node_cord;
bool operator< (const node_cord a, const node_cord b);
bool operator== (const node_cord a, const node_cord b);

class DijkstraNode {
private:
    uint32_t wgs84_lat_to_int(double lat);
    uint32_t wgs84_lon_to_int(double lon);
public:
    nodeID id;
    node_cord cord;
    uint32_t dijkstra_class;
    uint32_t distance;
    bool marked;
    std::vector<DijkstraNode *> other_nodes;

    void addEdge(DijkstraNode *other_node);
    void addBidirectional(DijkstraNode *other_node);
    DijkstraNode(nodeID id, double wgs_lat, double wgs_lon);
};


#endif //PARALLEL_DIJKSTRA_DIJKSTRANODE_H
