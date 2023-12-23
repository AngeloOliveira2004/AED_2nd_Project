//
// Created by jose-costa on 12/23/23.
//

#ifndef PROJETO_2_LOGIC_H
#define PROJETO_2_LOGIC_H

#include <unordered_map>
#include "Graph.h"
#include "Airport.h"

template <typename T>

class Logic {
private:
    Graph<T> graph;

public:
    Logic();
    Logic(Graph<T>& g);

    ~Logic();

    double HaversineAlgorithm(double lat1, double lon1,double lat2, double lon2);
    void DijkstraAlgorithm();
};


#endif //PROJETO_2_LOGIC_H
