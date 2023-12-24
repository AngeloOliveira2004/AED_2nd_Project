//
// Created by jose-costa on 12/23/23.
//

#include "Logic.h"
#include <cmath>


Logic::Logic(Graph<Airport>& g) : graph(g) {}
// O(log n)
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

//O(1)
int Logic::GlobalNumberOfAirports() {
    return graph.getVertexSet().size();
}

//O(V)
size_t Logic::GlobalNumberOfFlights() {

    size_t numberFlights = 0;

    for(auto vertex : graph.getVertexSet())
    {
        numberFlights += vertex->getAdj().size();
    }

    return numberFlights;
}

//O(V)
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

//O(V + E)
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

// O(V)
int Logic::NumberOfFlightsPerCity(std::string city) {

    int numberFlights = 0;

    for(auto vertex : graph.getVertexSet())
    {
        auto airport = vertex->getInfo();

        if(vertex->getInfo().getCity() == city)
        {
            numberFlights += (int) vertex->getAdj().size();
        }
    }

    return numberFlights;
}

//||||||||||| Point 6 |||||||||||||||||||||||

//For values of k > 5 it stars breaking for some reason

vector<Airport> bfsCount(const Graph<Airport> *g, const Airport &source, int k);
std::pair<int , std::vector<unordered_set<std::string>>> Logic::DestinationsAtDistanceK(const string &airportCode, int k) {

    Airport airport = Airport(airportCode);

    vector<Airport> airportsAtDistanceK = bfsCount(&this->graph , airport , k);

    unordered_set<std::string> countries;
    unordered_set<std::string> cities;
    unordered_set<std::string> airportsCodes;

    for(const Airport& airport1 : airportsAtDistanceK)
    {
        countries.insert(airport1.getCountry());
        cities.insert(airport1.getCity());
        airportsCodes.insert(airport1.getCode());
    }

    std::vector<unordered_set<std::string>> unorderedSets;
    unorderedSets.push_back(airportsCodes);
    unorderedSets.push_back(countries);
    unorderedSets.push_back(cities);

    std::pair<int , std::vector<unordered_set<std::string>>> map;
    int sum = (int) (countries.size() + cities.size() + airportsCodes.size());
    map = std::make_pair( sum , unorderedSets);

    return map;
}


vector<Airport> bfsCount(const Graph<Airport> *g, const Airport &source, int k) {
    vector<Airport> res;
    queue<pair<Vertex<Airport>* , int>> q;

    Vertex<Airport>* sourceVertex = g->findVertex(source);

    for (auto vertex : g->getVertexSet()) {
        vertex->setVisited(false);
    }

    if (sourceVertex == nullptr) {
        return res;
    }

    q.push({sourceVertex,0});
    sourceVertex->setVisited(true);

    while (!q.empty()) {
        Vertex<Airport>* currVertex = q.front().first;
        int currDistance = q.front().second;
        q.pop();

        if(currDistance == k)
        {
            res.push_back(currVertex->getInfo());
        }

        for (Edge<Airport> edge : currVertex->getAdj()) {
            // Fix the condition to check if the destination vertex is visited
            if (!edge.getDest()->isVisited()) {
                edge.getDest()->setVisited(true);
                q.push({edge.getDest(), currDistance +1});
            }
        }
    }
    int a = res.size();
    return res;
}


//||||||||||||| Point 7 |||||||||||||||||||||