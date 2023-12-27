//
// Created by jose-costa on 12/23/23.
//

#include "Logic.h"
#include <cmath>
#include <iostream>
#include <unordered_set>


Logic::Logic(Graph<Airport>& g) : graph(g) {}

double Logic::HaversineAlgorithm(double lat1, double lon1,double lat2, double lon2)
{
    double dLat = (lat2 - lat1) *
                  M_PI / 180.0;
    double dLon = (lon2 - lon1) *
                  M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;


    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);

    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

int Logic::GlobalNumbers() {
    return GlobalNumberOfAirports() + GlobalNumberOfFlights();
}

int Logic::GlobalNumberOfAirports() {
    return graph.getVertexSet().size();
}

size_t Logic::GlobalNumberOfFlights() {

    size_t numberFlights = 0;

    for(auto vertex : graph.getVertexSet())
    {
        numberFlights += vertex->getAdj().size();
    }

    return numberFlights;
}

std::pair<int , int>
Logic::FlightsOutOfAirportAndDifferentAirlines(const std::string& AirportCode) {
    int NumberOfFlights = 0;
    unordered_set<std::string> AirlinesCodes;

    Airport tempAirport = Airport(AirportCode, " ", " ", " ", 0.0, 0.0);

    Vertex<Airport>* flight = this->graph.findVertex(tempAirport);
    
    if(flight == nullptr)
    {
        return std::make_pair(NumberOfFlights , (int) AirlinesCodes.size());
    }
    
    NumberOfFlights = static_cast<int>(flight->getAdj().size());

    for(const auto& edge : flight->getAdj())
    {
        AirlinesCodes.insert(edge.getAirline());
    }

    return std::make_pair(NumberOfFlights , (int) AirlinesCodes.size());
}

int Logic::NumberOfFlightsPerAirline(const std::string& airlineCode) {
    int NumberOfFlights = 0;

    for(auto vertex : graph.getVertexSet())
    {
        for(auto edge : vertex->getAdj())
        {
            if(edge.getAirline() == airlineCode)
            {
                NumberOfFlights++;
            }
        }
    }

    return NumberOfFlights;
}

//O(V)
int Logic::NumberOfCountries(std::string airportCode) {

    unordered_set<std::string> countries;

    Airport SearchAirport = Airport(airportCode);

    Vertex<Airport>* airport = graph.findVertex(SearchAirport);

    if(airport == NULL)
    {
        return 0;
    }

    for(auto edge : airport->getAdj())
    {
        auto child = edge.getDest();
        std::string country = child->getInfo().getCountry();
        countries.insert(child->getInfo().getCountry());
    }

    return (int) countries.size();
}


//O(V + E)
int Logic::NumberOfCountriesThatCityFliesTo(std::string city) {

    unordered_set<std::string> countries;

    for(auto vertex : graph.getVertexSet())
    {
       auto airport = vertex->getInfo();

       if(airport.getCity() == city)
       {
           for(auto edge : vertex->getAdj())
           {
               auto child = edge.getDest()->getInfo();
               countries.insert(child.getCountry());
           }
       }
    }

    return (int) countries.size();
}

vector<string> Logic::TopTrafficAirports(int k) {
    vector<std::pair<int, std::string>> airport_to_traffic;
    vector<int> traffics;
    vector<string> result;
    size_t s;
    graph.calculateIndegrees();
    for(auto vertex: graph.getVertexSet()){
        s = vertex->getAdj().size() + vertex->getIndegree();
        traffics.push_back(s);
        airport_to_traffic.push_back(std::make_pair(s, vertex->getInfo().getCode()));
    }
    std::sort(traffics.begin(), traffics.end(), greater<int>());
    std::sort(airport_to_traffic.rbegin(), airport_to_traffic.rend());
    for (int i = 0; i < k; i++){
        result.push_back(airport_to_traffic[i].second);
        std::cout << airport_to_traffic[i].second << " " << airport_to_traffic[i].first << endl;
    }
    return result;
}

vector<string> Logic::GreatestKIndeegrees(int k) {
    vector<std::pair<int, std::string>> airport_to_traffic;
    vector<int> traffics;
    vector<string> result;
    size_t s;
    graph.calculateIndegrees();
    for(auto vertex: graph.getVertexSet()){
        s = vertex->getIndegree();
        traffics.push_back(s);
        airport_to_traffic.push_back(std::make_pair(s, vertex->getInfo().getCode()));
    }
    std::sort(traffics.begin(), traffics.end(), greater<int>());
    std::sort(airport_to_traffic.rbegin(), airport_to_traffic.rend());
    for (int i = 0; i < k; i++){
        result.push_back(airport_to_traffic[i].second);
        std::cout << airport_to_traffic[i].second << " " << airport_to_traffic[i].first << endl;
    }
    return result;
}