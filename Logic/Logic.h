//
// Created by jose-costa on 12/23/23.
//

#ifndef PROJETO_2_LOGIC_H
#define PROJETO_2_LOGIC_H

#include <unordered_map>
#include "Graph.h"
#include "Airport.h"


class Logic {
private:
    Graph<Airport> graph;

public:
    Logic();
    Logic(Graph<Airport>& g);

    double HaversineAlgorithm(double lat1, double lon1,double lat2, double lon2);
    void DijkstraAlgorithm();
    int GlobalNumbers();
    int GlobalNumberOfAirports();
    size_t GlobalNumberOfFlights();
};


#endif //PROJETO_2_LOGIC_H
