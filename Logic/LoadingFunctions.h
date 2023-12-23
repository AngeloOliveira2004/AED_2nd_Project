//
// Created by jose-costa on 12/23/23.
//

#ifndef PROJETO_2_LOADINGFUNCTIONS_H
#define PROJETO_2_LOADINGFUNCTIONS_H

class Airport;
class Airlines;

#include "Graph.h"
#include "Airport.h"
#include "unordered_set"

class LoadingFunctions {
public:
    static void LoadAirports(Graph<Airport>& g);

    static void LoadAirlines(Graph<Airport>& g);

    static void LoadFlights(Graph<Airport>& g);

    static void NormaliseString(std::string& str);

    static unordered_set<Airline> getArlines(){return airlines;};

private:
    static unordered_set<Airport> airports;
    static unordered_set<Airline> airlines;

    static double HaversineAlgorithm(double lat1, double lon1, double lat2, double lon2);
};


#endif //PROJETO_2_LOADINGFUNCTIONS_H
