#include <iostream>
#include "PostgreSQLLoader.h"
#include "ParallelDijkstra.h"
#include "DijkstraNode.h"

/*
 * sometimes an osm_id doesn't exist, because it has been overriden by a connected street. In this case,
 * try another osm id!
 */

int main() {
    PostgreSQLLoader postgreSQLLoader;
    DijkstraGraph * dijkstraGraph = postgreSQLLoader.loadStreets();

    // DANMARK?
    /*
    dijkstraGraph->getNode(339513180)->addBidirectional(
            dijkstraGraph->getNode(12724420)
    );
     */

    /*
    for(auto it = dijkstraGraph.nodes.begin();
            it != dijkstraGraph.nodes.end();
            ++it) {
        std::cout << it->second->id.osm_id << "," << it->second->id.sub_id << ":" <<
                  (*it->second).other_nodes.size() << "[";
        for(std::vector<DijkstraNode *>::iterator it2 = (*it->second).other_nodes.begin();
                it2 != (*it->second).other_nodes.end();
                ++it2) {
            std::cout << (*it2)->id.osm_id << ":"  << (*it2)->id.sub_id << ", ";
        }
        std::cout << "]" << std::endl;
    }
*/

/*
    std::vector<std::pair<int64_t, uint32_t>> starting_nodes = {
            {117938010, 4444},  // Skagen
            {162089319, 1337}, // Copenhagen
    };
*/



  /*
    std::vector<std::pair<int64_t, uint32_t>> starting_nodes = {
            //{46923267, 1337}, // Schaan
            {43327662, 4444},  // Balzers
            {437322836, 9999}, //Mauren
    };
*/

  /*
   Begin: AkutModtagelse København
   */
  std::vector<std::pair<int64_t, uint32_t>> starting_nodes = {
          {191586964, 1}, // Bispebjerg
          {604237532, 2}, // Gentofte Hospitalet
          {237356626, 3}, // Frederiksberg Hospital
          {601110074, 4}, // Hvidovre Hospital
          {206083837, 5}, // Amager Hospital
  };

  /*
   End: AkutModtagelse København
   */


    ParallelDijkstra(dijkstraGraph, starting_nodes);

    //std::cout << "Schaan Klasse " << dijkstraGraph->getNode(32699970)->distance << "," << dijkstraGraph->getNode(32699970)->dijkstra_class << std::endl;
    //std::cout << "Reihnndamm (Balzers) " <<dijkstraGraph->getNode(6078883)->distance << "," << dijkstraGraph->getNode(6078883)->dijkstra_class << std::endl;



    /*
    int64_t bested_thy = 101987997;
    int64_t ullerslev = 25847388;
    int64_t sonderborg = 23723102;
    int64_t aalborg = 56244660;
    int64_t kopenhagen = 3994841;

    std::cout << dijkstraGraph.getNode(bested_thy)->distance << "," << dijkstraGraph.getNode(bested_thy)->dijkstra_class << std::endl;

    std::cout << dijkstraGraph.getNode(ullerslev)->distance << "," << dijkstraGraph.getNode(ullerslev)->dijkstra_class << std::endl;
    std::cout << dijkstraGraph.getNode(sonderborg)->distance << "," << dijkstraGraph.getNode(sonderborg)->dijkstra_class << std::endl;
    std::cout << dijkstraGraph.getNode(aalborg)->distance << "," << dijkstraGraph.getNode(aalborg)->dijkstra_class << std::endl;
    std::cout << dijkstraGraph.getNode(kopenhagen)->distance << "," << dijkstraGraph.getNode(kopenhagen)->dijkstra_class << std::endl;
    */
    postgreSQLLoader.saveClassDistances(dijkstraGraph);

    return 0;
}