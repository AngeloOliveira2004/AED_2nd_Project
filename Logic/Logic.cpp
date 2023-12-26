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

vector<Airport> Logic::nodesAtDistanceBFS(const string &airportCode, int k) {
    vector<Airport> res;

    Airport SearchAirport = Airport(airportCode);

    Vertex<Airport>* airport = graph.findVertex(SearchAirport);

    for (auto vertex : graph.getVertexSet()) {
        vertex->setVisited(false);
    }

    queue<Vertex<Airport>*> q;
    q.push(airport);
    airport->setVisited(true);

    while (!q.empty() && k >= 0) {
        int lvl_size = q.size();

        while (lvl_size != 0) {
            auto ver = q.front();

            res.push_back(ver->getInfo());

            for (auto edge : ver->getAdj()) {
                auto destVert = edge.getDest();
                if (!destVert->isVisited()) {
                    q.push(destVert);
                    destVert->setVisited(true);
                }
            }

            lvl_size--;
            q.pop();
        }

        k--;
    }

    return res;
}


vector<int> Logic::analyzeReachableAirports(const vector<Airport> &reachableAirports) {
    unordered_set<Airport> distinctAirports;
    unordered_set<string> distinctCountries;
    unordered_set<string> distinctCities;

    vector<int> result;

    for (const auto &airport : reachableAirports) {
        distinctAirports.insert(airport.getCode());
        distinctCountries.insert(airport.getCountry());
        distinctCities.insert(airport.getCity());
    }

    result.push_back(distinctAirports.size());
    result.push_back(distinctCountries.size());
    result.push_back(distinctCities.size());

    return result;

}


//||||||||||||| Point 7 |||||||||||||||||||||

void setUnvisited(Graph<Airport> g);
std::vector<Airport> specialDFS(Vertex<Airport>& v , unordered_map<Airport , int>& aux , int k);
std::vector<std::pair<Airport, Airport>> Logic::AirportAtMaximumDistance() {

    std::vector<Airport> res = {};
    std::vector<std::pair<Airport, Airport>> res1 = {};
    for(auto vertex : graph.getVertexSet())
    {
        Vertex<Airport> a = *vertex;
        std::string code = a.getInfo().getCode();
        unordered_map<Airport , int> aux;
        setUnvisited(this->graph);

        res = specialDFS(a , aux , 0);

        for(const auto& airport : res)
        {
            res1.emplace_back(vertex->getInfo() , airport);
        }
    }

    return res1;
}

std::vector<Airport> specialDFS(Vertex<Airport>& v , unordered_map<Airport , int>& aux , int k)
{
    std::vector<Airport>  res;
    v.setVisited(true);
    aux.insert(make_pair(v.getInfo() , k));

    for(auto edge : v.getAdj())
    {
        if(!edge.getDest()->isVisited())
        {
            Vertex<Airport> a = *edge.getDest();
            specialDFS(a , aux , k+1);
        }
    }

    int max = INT16_MIN;

    for(auto & it : aux)
    {
        const Airport& airport = it.first;
        int distance = it.second;

        max = std::max(distance , max);
    }

    for(auto & it : aux)
    {
        const Airport& airport = it.first;
        int distance = it.second;

        if(max == distance)
        {
            res.push_back(airport);
        }
    }

    return res;
}

void setUnvisited(Graph<Airport> g)
{
    for(auto& vertex : g.getVertexSet())
    {
        vertex->setVisited(false);
        for(auto& edge : vertex->getAdj())
        {
            edge.getDest()->setVisited(false);
        }
    }
}