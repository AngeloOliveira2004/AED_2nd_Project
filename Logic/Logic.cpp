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

// O(E)
int Logic::NumberOfDestinationsForAirport(const std::string& airportCode) {
    Vertex<Airport> *sourceVertex = graph.findVertex(Airport(airportCode));

    if (sourceVertex == nullptr) {
        return 0;
    }

    int destinations = 0;
    std::unordered_set<std::string> visitedDestinations;

    for (const Edge<Airport>& edge : sourceVertex->getAdj()) {
        Vertex<Airport>* neighbor = edge.getDest();

        const std::string& destinationCode = neighbor->getInfo().getCode();
        if (visitedDestinations.find(destinationCode) == visitedDestinations.end()) {
            destinations++;
            visitedDestinations.insert(destinationCode);
        }
    }

    return destinations;
}

// O(E)
int Logic::NumberOfDestinationsForCity(const std::string& airportCode) {
    Vertex<Airport> *sourceVertex = graph.findVertex(Airport(airportCode));

    if (sourceVertex == nullptr) {
        return 0;
    }

    int destinations = 0;
    std::unordered_set<std::string> visitedDestinations;

    for (const Edge<Airport>& edge : sourceVertex->getAdj()) {
        Vertex<Airport>* neighbor = edge.getDest();

        const std::string& cityName = neighbor->getInfo().getCity();
        if (visitedDestinations.find(cityName) == visitedDestinations.end()) {
            destinations++;
            visitedDestinations.insert(cityName);
        }
    }

    return destinations;
}

// O(E)
int Logic::NumberOfDestinationsForCountry(const std::string& airportCode) {
    Vertex<Airport> *sourceVertex = graph.findVertex(Airport(airportCode));

    if (sourceVertex == nullptr) {
        return 0;
    }

    int destinations = 0;
    std::unordered_set<std::string> visitedDestinations;

    for (const Edge<Airport>& edge : sourceVertex->getAdj()) {
        Vertex<Airport>* neighbor = edge.getDest();

        const std::string& countryName = neighbor->getInfo().getCountry();
        if (visitedDestinations.find(countryName) == visitedDestinations.end()) {
            destinations++;
            visitedDestinations.insert(countryName);
        }
    }

    return destinations;
}

unordered_set<Airport> Logic::findArticulationPoints() {
    int index = 1;
    unordered_set<Airport> articulationPoints;
    stack<Vertex<Airport>*> s;

    for (Vertex<Airport>* v : graph.getVertexSet()) {
        v->setVisited(false);
        v->setProcessing(false);
    }

    for (Vertex<Airport>* v : graph.getVertexSet()) {
        if (!v->isVisited()) {
            dfs_articulationPoints(v, nullptr, articulationPoints, s, index);
        }
    }

    return articulationPoints;
}

void Logic::dfs_articulationPoints(Vertex<Airport>* v, Vertex<Airport>* parent, unordered_set<Airport>& articPoints, stack<Vertex<Airport>*>& s, int& index) {
    v->setNum(index);
    v->setLow(index);
    v->setVisited(true);
    index++;

    s.push(v);
    v->setProcessing(true);

    int children = 0;
    bool isArticulationPoint = false;

    for (auto &e : v->getAdj()) {
        Vertex<Airport>* w = e.getDest();
        if (!w->isVisited()) {
            children++;
            dfs_articulationPoints(w, v, articPoints, s, index);
            v->setLow(min(v->getLow(), w->getLow()));

            if (w->getLow() >= v->getNum()) {
                isArticulationPoint = true;
            }
        } else if (w->isProcessing()) {
            v->setLow(min(v->getLow(), w->getNum()));
        }
    }

    if ((v->getNum() == v->getLow() && children > 1) || (v->getNum() != v->getLow() && isArticulationPoint)) {
        articPoints.insert(v->getInfo());

        while (!s.empty()) {
            Vertex<Airport>* poppedVertex = s.top();
            s.pop();
            poppedVertex->setProcessing(false);

            if (poppedVertex == v) {
                break;
            }
        }
    }

}













