//
// Created by jose-costa on 12/23/23.
//

#include "Logic.h"
#include <cmath>
#include <iostream>
#include <climits>


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

void Logic::MapAirports(){
    for(auto v: graph.getVertexSet()){
        this->NamesToCodes[v->getInfo().getName()] = v->getInfo().getCode();
    }
}

unordered_map<std::string , std::string> Logic::getNamesToCodes(){
    return this->NamesToCodes;
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
//|||||||||||||||||| Point 5 |||||||||||||||||||||||


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
void specialDFS(Vertex<Airport>* v);
std::pair< std::vector<std::pair<Airport, Airport>> , int> Logic::AirportAtMaximumDistance() {

    std::vector<std::pair<Airport, Airport>> res = {};

    unordered_map<int , std::vector<std::pair<Airport , Airport>>> map;

    Airport initialAirport = Airport();
    Airport endAirport = Airport();

    for(auto vertex : graph.getVertexSet())
    {
        initialAirport = vertex->getInfo();
        setUnvisited(this->graph);
        specialDFS(vertex);

        int max = INT16_MIN;
        for(auto vertex1 : graph.getVertexSet())
        {
            if(vertex1->getNum() > max)
            {
                max = vertex1->getNum();
                endAirport = vertex1->getInfo();
            }
        }

        if(map.find(max) == map.end())
        {
            map[max] = {std::make_pair(initialAirport , endAirport)};
        }
        else
        {
            map[max].emplace_back(initialAirport , endAirport);
        }
    }

    int max = INT16_MIN;
    for(auto a : map)
    {
        if(a.first > max) max = a.first;
    }

    for(auto a : map)
    {
        if(a.first == max)
        {
            for(const auto& pair : a.second)
            {
                res.push_back(pair);
            }
        }
    }

    return std::make_pair(res , max);
}

void specialDFS(Vertex<Airport>* v)
{
    v->setVisited(true);
    for (auto & e : v->getAdj()) {
        auto w = e.getDest();
        if ( ! w->isVisited()) {
            w->setNum(v->getNum() + 1);
            specialDFS(w);
        }
    }
}

void setUnvisited(Graph<Airport> g)
{
    for(auto& vertex : g.getVertexSet())
    {
        vertex->setVisited(false);
        vertex->setNum(0);
    }
}

vector<vector<Airport>> Logic::FindMaxTripBfs(const Airport &airport_, int diameter) {
    vector<vector<Airport>> res;

    Vertex<Airport>* airportVertex = graph.findVertex(airport_);

    if(airportVertex == nullptr)
    {
        return {};
    }

    for (auto vertex : graph.getVertexSet()) {
        vertex->setVisited(false);
        vertex->setNum(0);
        vertex->setParent(nullptr);
    }

    queue<Vertex<Airport>*> q;
    q.push(airportVertex);
    airportVertex->setVisited(true);
    airportVertex->setNum(0);
    airportVertex->setParent(nullptr);
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        if(v->getNum() == diameter)
        {
            vector<Airport> temp;
            temp.push_back(v->getInfo());
            while (v->getParent() != nullptr)
            {
                temp.push_back(v->getParent()->getInfo());
                v = v->getParent();
            }
            std::reverse(temp.begin(), temp.end());
            res.push_back(temp);
        }
        for (auto & e : v->getAdj()) {
            auto w = e.getDest();
            if ( ! w->isVisited() ) {
                q.push(w);
                w->setVisited(true);
                w->setParent(v);
                w ->setNum(v->getNum() +1);
            }
        }
    }

    return res;
}

//||||||||||||||||||||||||||||  Point 8 |||||||||||||||||||||||||||||||

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
        std::cout << i+1 << ". " << airport_to_traffic[i].second << " " << airport_to_traffic[i].first << endl;
    }
    return result;
}

//||||||||||||||||||||||||| Point 9 |||||||||||||||||||||||||||||||||

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
            dfs_articulationPoints(v, articulationPoints, s, index);
        }
    }

    return articulationPoints;
}

void Logic::dfs_articulationPoints(Vertex<Airport>* v, unordered_set<Airport>& articPoints, stack<Vertex<Airport>*>& s, int& index) {
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
            dfs_articulationPoints(w, articPoints, s, index);
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


//|||||||||||||||||||||||||| ShortestPath ||||||||||||||||||||||||||

vector<Airport> Logic::shortestPath(const Airport& initialAirport, const Airport& destAirport) {
    vector<Airport> res;
    Vertex<Airport>* initialVertex;
    Vertex<Airport>* finalVertex;

    for(auto v : graph.getVertexSet())
    {
        if(v->getInfo() == initialAirport)
        {
            initialVertex = v;
        }
        if(v->getInfo() == destAirport)
        {
            finalVertex = v;
        }
    }

    if (initialVertex == nullptr || finalVertex == nullptr)
        return res;  // Return an empty vector indicating failure

    // Resetting visited and parent information
    for (auto v : graph.getVertexSet()) {
        v->setVisited(false);
        v->setParent(nullptr);
    }

    queue<Vertex<Airport> *> q;
    q.push(initialVertex);
    initialVertex->setVisited(true);

    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        if (v == finalVertex) {
            // Reconstruct the path
            while (v->getParent() != nullptr) {
                res.push_back(v->getInfo());
                v = v->getParent();
            }
            res.push_back(initialAirport);  // Add the initial vertex to the path
            reverse(res.begin(), res.end());  // Reverse the path to get correct order
            return res;
        }

        for (const Edge<Airport> &e : v->getAdj()) {
            Vertex<Airport>* w = e.getDest();
            if (!w->isVisited()) {
                w->setParent(v);
                q.push(w);
                w->setVisited(true);
            }
        }
    }

    return res;  // Return an empty vector indicating that no path was found
}

//|||||||||||||||||| FILTERS ||||||||||||||||||

list<vector<Airport>> Logic::AirportToAirport(const Airport& initialAirport, const Airport& destAirport) {
    list<vector<Airport>> res;
    Vertex<Airport>* initialVertex;
    Vertex<Airport>* finalVertex;

    for(auto v : graph.getVertexSet())
    {
        if(v->getInfo() == initialAirport)
        {
            initialVertex = v;
        }
        if(v->getInfo() == destAirport)
        {
            finalVertex = v;
        }
    }

    if (initialVertex == nullptr || finalVertex == nullptr)
        return res;  // Return an empty vector indicating failure

    for (auto v : graph.getVertexSet()) {
        v->setVisited(false);
        v->setParent(nullptr);
    }

    queue<Vertex<Airport> *> q;
    q.push(initialVertex);
    initialVertex->setVisited(true);

    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        if (v == finalVertex) {
            vector<Airport> temp;
            while (v->getParent() != nullptr) {
                temp.push_back(v->getInfo());
                v = v->getParent();
            }
            temp.push_back(initialAirport);
            reverse(temp.begin() , temp.end());
            res.push_back(temp);
        }

        for (const Edge<Airport> &e : v->getAdj()) {

            Vertex<Airport>* w = e.getDest();
            if (!w->isVisited()) {
                w->setParent(v);
                q.push(w);
                w->setVisited(true);
            }

        }
    }

    return res;
}

list<vector<Airport>>
Logic::AirportToAirportAirlineOnlyFilters(const Airport& initialAirport, const Airport& destAirport, unordered_set<std::string> airlines) {
    list<vector<Airport>> res;
    Vertex<Airport>* initialVertex;
    Vertex<Airport>* finalVertex;

    for(auto v : graph.getVertexSet())
    {
        if(v->getInfo() == initialAirport)
        {
            initialVertex = v;
        }
        if(v->getInfo() == destAirport)
        {
            finalVertex = v;
        }
    }

    if (initialVertex == nullptr || finalVertex == nullptr)
        return res;  // Return an empty vector indicating failure

    for (auto v : graph.getVertexSet()) {
        v->setVisited(false);
        v->setParent(nullptr);
    }

    queue<Vertex<Airport> *> q;
    q.push(initialVertex);
    initialVertex->setVisited(true);

    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        if (v == finalVertex) {
            vector<Airport> temp;
            while (v->getParent() != nullptr) {
                temp.push_back(v->getInfo());
                v = v->getParent();
            }
            temp.push_back(initialAirport);
            reverse(temp.begin() , temp.end());
            res.push_back(temp);
        }

        for (const Edge<Airport> &e : v->getAdj()) {

            if(airlines.find(e.getAirline()) != airlines.end())
            {
                Vertex<Airport>* w = e.getDest();
                if (!w->isVisited()) {
                    w->setParent(v);
                    q.push(w);
                    w->setVisited(true);
                }
            }
        }
    }

    return res;
}

list<vector<Airport>>
Logic::AirportToAirportAirlineAvoidFilters(const Airport &initialAirport, const Airport &destAirport,
                                           unordered_set<std::string> airlines) {

    list<vector<Airport>> res;
    Vertex<Airport>* initialVertex;
    Vertex<Airport>* finalVertex;

    for(auto v : graph.getVertexSet())
    {
        if(v->getInfo() == initialAirport)
        {
            initialVertex = v;
        }
        if(v->getInfo() == destAirport)
        {
            finalVertex = v;
        }
    }

    if (initialVertex == nullptr || finalVertex == nullptr)
        return res;  // Return an empty vector indicating failure

    for (auto v : graph.getVertexSet()) {
        v->setVisited(false);
        v->setParent(nullptr);
    }

    queue<Vertex<Airport> *> q;
    q.push(initialVertex);
    initialVertex->setVisited(true);

    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        if (v == finalVertex) {
            vector<Airport> temp;
            while (v->getParent() != nullptr) {
                temp.push_back(v->getInfo());
                v = v->getParent();
            }
            temp.push_back(initialAirport);
            reverse(temp.begin() , temp.end());
            res.push_back(temp);
        }

        for (const Edge<Airport> &e : v->getAdj()) {

            if(airlines.find(e.getAirline()) == airlines.end())
            {
                Vertex<Airport>* w = e.getDest();
                if (!w->isVisited()) {
                    w->setParent(v);
                    q.push(w);
                    w->setVisited(true);
                }
            }
        }
    }

    return res;
}


list<vector<Airport>> Logic::AirportToCity(const Airport& initialAirport, const std::string& city ,const std::string& country) {
    list<vector<Airport>> res;
    Vertex<Airport>* initialVertex;

    for(auto v : graph.getVertexSet())
    {
        if(v->getInfo() == initialAirport)
        {
            initialVertex = v;
        }
    }

    if (initialVertex == nullptr)
        return res;  // Return an empty vector indicating failure

    for (auto v : graph.getVertexSet()) {
        v->setVisited(false);
        v->setParent(nullptr);
    }

    queue<Vertex<Airport> *> q;
    q.push(initialVertex);
    initialVertex->setVisited(true);

    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        if (v->getInfo().getCity() == city && v->getInfo().getCountry() == country) {
            vector<Airport> temp;
            while (v->getParent() != nullptr) {
                temp.push_back(v->getInfo());
                v = v->getParent();
            }
            temp.push_back(initialAirport);
            reverse(temp.begin() , temp.end());
            res.push_back(temp);
        }

        for (const Edge<Airport> &e : v->getAdj()) {
            Vertex<Airport>* w = e.getDest();
            if (!w->isVisited()) {
                w->setParent(v);
                q.push(w);
                w->setVisited(true);
            }
        }
    }

    return res;
}

list<vector<Airport>> Logic::AirportToCityAirlineAvoidFilter(const Airport& initialAirport, const std::string& city,
                                                          const std::string& country , unordered_set<std::string> airlines) {
    list<vector<Airport>> res;
    Vertex<Airport>* initialVertex;

    for(auto v : graph.getVertexSet())
    {
        if(v->getInfo() == initialAirport)
        {
            initialVertex = v;
        }
    }

    if (initialVertex == nullptr)
        return res;  // Return an empty vector indicating failure

    for (auto v : graph.getVertexSet()) {
        v->setVisited(false);
        v->setParent(nullptr);
    }

    queue<Vertex<Airport> *> q;
    q.push(initialVertex);
    initialVertex->setVisited(true);

    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        if (v->getInfo().getCity() == city && v->getInfo().getCountry() == country) {
            vector<Airport> temp;
            while (v->getParent() != nullptr) {
                temp.push_back(v->getInfo());
                v = v->getParent();
            }
            temp.push_back(initialAirport);
            reverse(temp.begin() , temp.end());
            res.push_back(temp);
        }

        for (const Edge<Airport> &e : v->getAdj()) {

            if(airlines.find(e.getAirline()) == airlines.end())
            {
                Vertex<Airport>* w = e.getDest();
                if (!w->isVisited()) {
                    w->setParent(v);
                    q.push(w);
                    w->setVisited(true);
                }
            }
        }
    }

    return res;
}

list<vector<Airport>>
Logic::AirportToCityAirlineOnlyFilter(const Airport& initialAirport, const std::string& city, const std::string& country,
                                      unordered_set<std::string> airlines) {
    list<vector<Airport>> res;
    Vertex<Airport>* initialVertex;

    for(auto v : graph.getVertexSet())
    {
        if(v->getInfo() == initialAirport)
        {
            initialVertex = v;
        }
    }

    if (initialVertex == nullptr)
        return res;  // Return an empty vector indicating failure

    for (auto v : graph.getVertexSet()) {
        v->setVisited(false);
        v->setParent(nullptr);
    }

    queue<Vertex<Airport> *> q;
    q.push(initialVertex);
    initialVertex->setVisited(true);

    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        if (v->getInfo().getCity() == city && v->getInfo().getCountry() == country) {
            vector<Airport> temp;
            while (v->getParent() != nullptr) {
                temp.push_back(v->getInfo());
                v = v->getParent();
            }
            temp.push_back(initialAirport);
            reverse(temp.begin() , temp.end());
            res.push_back(temp);
        }

        for (const Edge<Airport> &e : v->getAdj()) {

            if(airlines.find(e.getAirline()) != airlines.end())
            {
                Vertex<Airport>* w = e.getDest();
                if (!w->isVisited()) {
                    w->setParent(v);
                    q.push(w);
                    w->setVisited(true);
                }
            }
        }
    }

    return res;
}


//||||||||||||||||||||||||||||||||||| AIRPORTS TO COUNTRY |||||||||||||||||||||||||||||||||||||||||

list<vector<Airport>> Logic::AirportToCountry(const Airport& initialAirport, const std::string& country) {
    list<vector<Airport>> res;
    Vertex<Airport>* initialVertex;

    for(auto v : graph.getVertexSet())
    {
        if(v->getInfo() == initialAirport)
        {
            initialVertex = v;
        }
    }

    if (initialVertex == nullptr)
        return res;  // Return an empty vector indicating failure

    for (auto v : graph.getVertexSet()) {
        v->setVisited(false);
        v->setParent(nullptr);
    }

    queue<Vertex<Airport> *> q;
    q.push(initialVertex);
    initialVertex->setVisited(true);

    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        if (v->getInfo().getCountry() == country) {
            vector<Airport> temp;
            while (v->getParent() != nullptr) {
                temp.push_back(v->getInfo());
                v = v->getParent();
            }
            temp.push_back(initialAirport);
            reverse(temp.begin() , temp.end());
            res.push_back(temp);
        }

        for (const Edge<Airport> &e : v->getAdj()) {
            Vertex<Airport>* w = e.getDest();
            if (!w->isVisited()) {
                w->setParent(v);
                q.push(w);
                w->setVisited(true);
            }
        }
    }

    return res;
}

list<vector<Airport>> Logic::AirportToCountryAirlineAvoidFilter(Airport initialAirport, std::string country,
                                                                  unordered_set<std::string> airlines) {
    list<vector<Airport>> res;
    Vertex<Airport>* initialVertex;

    for(auto v : graph.getVertexSet())
    {
        if(v->getInfo() == initialAirport)
        {
            initialVertex = v;
        }
    }

    if (initialVertex == nullptr)
        return res;  // Return an empty vector indicating failure

    for (auto v : graph.getVertexSet()) {
        v->setVisited(false);
        v->setParent(nullptr);
    }

    queue<Vertex<Airport> *> q;
    q.push(initialVertex);
    initialVertex->setVisited(true);

    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        if (v->getInfo().getCountry() == country) {
            vector<Airport> temp;
            while (v->getParent() != nullptr) {
                temp.push_back(v->getInfo());
                v = v->getParent();
            }
            temp.push_back(initialAirport);
            reverse(temp.begin() , temp.end());
            res.push_back(temp);
        }

        for (const Edge<Airport> &e : v->getAdj()) {

            if(airlines.find(e.getAirline()) == airlines.end())
            {
                Vertex<Airport>* w = e.getDest();
                if (!w->isVisited()) {
                    w->setParent(v);
                    q.push(w);
                    w->setVisited(true);
                }
            }
        }
    }

    return res;
}

list<vector<Airport>> Logic::AirportToCountryAirlineOnlyFilter(Airport initialAirport, std::string country,
                                                                 unordered_set<std::string> airlines){
    list<vector<Airport>> res;
    Vertex<Airport>* initialVertex;

    for(auto v : graph.getVertexSet())
    {
        if(v->getInfo() == initialAirport)
        {
            initialVertex = v;
        }
    }

    if (initialVertex == nullptr)
        return res;  // Return an empty vector indicating failure

    for (auto v : graph.getVertexSet()) {
        v->setVisited(false);
        v->setParent(nullptr);
    }

    queue<Vertex<Airport> *> q;
    q.push(initialVertex);
    initialVertex->setVisited(true);

    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        if (v->getInfo().getCountry() == country) {
            vector<Airport> temp;
            while (v->getParent() != nullptr) {
                temp.push_back(v->getInfo());
                v = v->getParent();
            }
            temp.push_back(initialAirport);
            reverse(temp.begin() , temp.end());
            res.push_back(temp);
        }

        for (const Edge<Airport> &e : v->getAdj()) {

            if(airlines.find(e.getAirline()) != airlines.end())
            {
                Vertex<Airport>* w = e.getDest();
                if (!w->isVisited()) {
                    w->setParent(v);
                    q.push(w);
                    w->setVisited(true);
                }
            }
        }
    }

    return res;
}

list<vector<Airport>>
Logic::CityToAirport(const Airport& destAirport , const std::string& city, const std::string& country, int choice, unordered_set<std::string> airlines) {
    vector<Vertex<Airport>*> initialAirports;
    for(auto v : graph.getVertexSet())
    {
        if(v->getInfo().getCountry() == country && v->getInfo().getCity() == city)
        {
            initialAirports.push_back(v);
        }
    }

    list<vector<Airport>> res;
    list<vector<Airport>> temp;

    switch (choice) {
        case 1:
            for(auto v : initialAirports)
            {
                temp = AirportToAirport(v->getInfo() , destAirport);
                for(const auto& smt : temp)
                {
                    res.push_back(smt);
                }
                temp.clear();
            }
            break;
        case 2:
            for(auto v : initialAirports)
            {
                temp = AirportToAirportAirlineAvoidFilters(v->getInfo() , destAirport , airlines);
                for(const auto& smt : temp)
                {
                    res.push_back(smt);
                }
                temp.clear();
            }
            break;
        case 3:
            for(auto v : initialAirports)
            {
                temp = AirportToAirportAirlineOnlyFilters(v->getInfo() , destAirport , airlines);
                for(const auto& smt : temp)
                {
                    res.push_back(smt);
                }
                temp.clear();
            }
            break;
    }

    return res;
}

list<vector<Airport>>
Logic::CityToCity(const std::string& InitialCity, const std::string& InitialCountry,const std::string& FinalCity, const std::string& FinalCountry, int choice, const unordered_set<std::string>& airlines) {

    vector<Vertex<Airport>*> initialAirports;
    for(auto v : graph.getVertexSet())
    {
        if(v->getInfo().getCountry() == InitialCountry && v->getInfo().getCity() == InitialCity)
        {
            initialAirports.push_back(v);
        }
    }

    list<vector<Airport>> res;
    list<vector<Airport>> temp;

    switch (choice) {
        case 1:
            for(auto v : initialAirports)
            {
                temp = AirportToCity(v->getInfo() , FinalCity , FinalCountry);
                for(const auto& smt : temp)
                {
                    res.push_back(smt);
                }
                temp.clear();
            }
            break;
        case 2:
            for(auto v : initialAirports)
            {
                temp = AirportToCityAirlineAvoidFilter(v->getInfo() , FinalCity , FinalCountry, airlines);
                for(const auto& smt : temp)
                {
                    res.push_back(smt);
                }
                temp.clear();
            }
            break;
        case 3:
            for(auto v : initialAirports)
            {
                temp = AirportToCityAirlineOnlyFilter(v->getInfo() , FinalCity , FinalCountry, airlines);
                for(const auto& smt : temp)
                {
                    res.push_back(smt);
                }
                temp.clear();
            }
            break;
    }

    return res;
}


list<vector<Airport>>
Logic::CityToCountry(const std::string& Initialcity, const std::string& InitialCountry, const std::string& FinalCountry, int choice, const unordered_set<string>& airlines) {
    vector<Vertex<Airport>*> initialAirports;
    for(auto v : graph.getVertexSet())
    {
        if(v->getInfo().getCountry() == InitialCountry && v->getInfo().getCity() == Initialcity)
        {
            initialAirports.push_back(v);
        }
    }

    list<vector<Airport>> res;
    list<vector<Airport>> temp;

    switch (choice) {
        case 1:
            for(auto v : initialAirports)
            {
                temp = AirportToCountry(v->getInfo() , FinalCountry);
                for(const auto& smt : temp)
                {
                    res.push_back(smt);
                }
                temp.clear();
            }
            break;
        case 2:
            for(auto v : initialAirports)
            {
                temp = AirportToCountryAirlineAvoidFilter(v->getInfo() , FinalCountry, airlines);
                for(const auto& smt : temp)
                {
                    res.push_back(smt);
                }
                temp.clear();
            }
            break;
        case 3:
            for(auto v : initialAirports)
            {
                temp = AirportToCountryAirlineOnlyFilter(v->getInfo() , FinalCountry, airlines);
                for(const auto& smt : temp)
                {
                    res.push_back(smt);
                }
                temp.clear();
            }
            break;
    }

    return res;
}

list<vector<Airport>>
Logic::CountryToAirport(const Airport &destAirport, const string &country, int choice,
                        unordered_set<std::string> airlines) {

    vector<Vertex<Airport>*> initialAirports;
    for(auto v : graph.getVertexSet())
    {
        if(v->getInfo().getCountry() == country)
        {
            initialAirports.push_back(v);
        }
    }

    list<vector<Airport>> res;
    list<vector<Airport>> temp;

    switch (choice) {
        case 1:
            for(auto v : initialAirports)
            {
                temp = AirportToAirport(v->getInfo() , destAirport);
                for(const auto& smt : temp)
                {
                    res.push_back(smt);
                }
                temp.clear();
            }
            break;
        case 2:
            for(auto v : initialAirports)
            {
                temp = AirportToAirportAirlineAvoidFilters(v->getInfo() , destAirport, airlines);
                for(const auto& smt : temp)
                {
                    res.push_back(smt);
                }
                temp.clear();
            }
            break;
        case 3:
            for(auto v : initialAirports)
            {
                temp = AirportToAirportAirlineOnlyFilters(v->getInfo() , destAirport, airlines);
                for(const auto& smt : temp)
                {
                    res.push_back(smt);
                }
                temp.clear();
            }
            break;
    }

    return res;
}

list<vector<Airport>>
Logic::CountryToCity(const string &InitialCountry, const string &FinalCity,
                     const string &FinalCountry, int choice, const unordered_set<std::string> &airlines) {

    vector<Vertex<Airport>*> initialAirports;
    for(auto v : graph.getVertexSet())
    {
        if(v->getInfo().getCountry() == InitialCountry)
        {
            initialAirports.push_back(v);
        }
    }

    list<vector<Airport>> res;
    list<vector<Airport>> temp;

    switch (choice) {
        case 1:
            for(auto v : initialAirports)
            {
                temp = AirportToCity(v->getInfo() , FinalCity , FinalCountry);
                for(const auto& smt : temp)
                {
                    res.push_back(smt);
                }
                temp.clear();
            }
            break;
        case 2:
            for(auto v : initialAirports)
            {
                temp = AirportToCityAirlineAvoidFilter(v->getInfo() , FinalCity , FinalCountry, airlines);
                for(const auto& smt : temp)
                {
                    res.push_back(smt);
                }
                temp.clear();
            }
            break;
        case 3:
            for(auto v : initialAirports)
            {
                temp = AirportToCityAirlineOnlyFilter(v->getInfo() , FinalCity , FinalCountry, airlines);
                for(const auto& smt : temp)
                {
                    res.push_back(smt);
                }
                temp.clear();
            }
            break;
    }

    return res;
}

list<vector<Airport>>
Logic::CountryToCountry(const string &InitialCountry, const string &country, int choice,
                        const unordered_set<std::string> &airlines) {

    vector<Vertex<Airport>*> initialAirports;
    for(auto v : graph.getVertexSet())
    {
        if(v->getInfo().getCountry() == InitialCountry)
        {
            initialAirports.push_back(v);
        }
    }

    list<vector<Airport>> res;
    list<vector<Airport>> temp;

    switch (choice) {
        case 1:
            for(auto v : initialAirports)
            {
                temp = AirportToCountry(v->getInfo() , country);
                for(const auto& smt : temp)
                {
                    res.push_back(smt);
                }
                temp.clear();
            }
            break;
        case 2:
            for(auto v : initialAirports)
            {
                temp = AirportToCountryAirlineAvoidFilter(v->getInfo() , country , airlines);
                for(const auto& smt : temp)
                {
                    res.push_back(smt);
                }
                temp.clear();
            }
            break;
        case 3:
            for(auto v : initialAirports)
            {
                temp = AirportToCountryAirlineOnlyFilter(v->getInfo() , country , airlines);
                for(const auto& smt : temp)
                {
                    res.push_back(smt);
                }
                temp.clear();
            }
            break;
    }

    return res;
}


//||||||||||||||||||||||||| Coordinates functions ||||||||||||||||||||||||||||||||||

vector<Airport> Logic::FindClosestAirportsToLocation(double Latitude, double Longitude){
    vector<Airport> res;
    double min_distance = numeric_limits<double>::max();
    for(auto v: graph.getVertexSet()){
        Airport temp = v->getInfo();
        double dist = HaversineAlgorithm( Latitude, Longitude, temp.getLatitude(), temp.getLongitude());
        std::cout << temp.getName()<< " | " << temp.getLatitude() << " | " << temp.getLongitude() << " | " << dist << endl;
        if(dist < min_distance){
            res.clear();
            min_distance = dist;
        }
        if(dist == min_distance){
            res.push_back(temp);
        }
    }
    return res;
}

vector<vector<Airport>> Logic::LocationToAirport(double source_latitude, double source_longitude, Airport dest){
    vector<Airport> sources = FindClosestAirportsToLocation(source_latitude, source_longitude);
    vector<vector<Airport>> res;
    for(auto airport: sources){
        for(auto trip: AirportToAirport(airport, dest)){
            res.push_back(trip);
        }
    }
    return res;
}

vector<vector<Airport>> Logic::LocationToCity(double source_latitude, double source_longitude, const std::string city, const std::string& country){
    vector<Airport> sources = FindClosestAirportsToLocation(source_latitude, source_longitude);
    vector<vector<Airport>> res;
    for(auto airport: sources){
        for(auto trip: AirportToCity(airport, city, country)){
            res.push_back(trip);
        }
    }
    return res;
}

vector<vector<Airport>> Logic::LocationToCountry(double source_latitude, double source_longitude, const std::string country){
    vector<Airport> sources = FindClosestAirportsToLocation(source_latitude, source_longitude);
    vector<vector<Airport>> res;
    for(auto airport: sources){
        for(auto trip: AirportToCountry(airport, country)){
            res.push_back(trip);
        }
    }
    return res;
}

vector<vector<Airport>> Logic::AirportToLocation(Airport source, double dest_latitude, double dest_longitude){
    vector<Airport> destinies = FindClosestAirportsToLocation(dest_latitude, dest_longitude);
    vector<vector<Airport>> res;
    for(auto airport: destinies){
        for(auto trip: AirportToAirport(source, airport)){
            res.push_back(trip);
        }
    }
    return res;
}

vector<vector<Airport>> Logic::CityToLocation(const std::string city, const std::string country, double dest_latitude, double dest_longitude){
    vector<Airport> destinies = FindClosestAirportsToLocation(dest_latitude, dest_longitude);
    vector<vector<Airport>> res;
    unordered_set<std::string> airline_names;
    for(auto airport: destinies){
        for(auto trip: CityToAirport(airport, city, country, 1, airline_names)){
            res.push_back(trip);
        }
    }
    return res;
}

vector<vector<Airport>> Logic::LocationToAirportAirlineOnlyFilters(double source_latitude, double source_longitude, Airport dest, unordered_set<std::string> airlines){
    vector<Airport> sources = FindClosestAirportsToLocation(source_latitude, source_longitude);
    vector<vector<Airport>> res;
    for(auto airport: sources){
        for(auto trip: AirportToAirportAirlineOnlyFilters(airport, dest, airlines))
            res.push_back(trip);
    }
    return res;
}

vector<vector<Airport>> Logic::LocationToAirportAirlineAvoidFilters(double source_latitude, double source_longitude, Airport dest, unordered_set<std::string> airlines){
    vector<Airport> sources = FindClosestAirportsToLocation(source_latitude, source_longitude);
    vector<vector<Airport>> res;
    for(auto airport: sources){
        for(auto trip: AirportToAirportAirlineAvoidFilters(airport, dest, airlines))
            res.push_back(trip);
    }
    return res;
}

vector<vector<Airport>> Logic::LocationToCityAirlineOnlyFilters(double source_latitude, double source_longitude, const std::string city, const std::string& country, unordered_set<std::string> airlines){
    vector<Airport> sources = FindClosestAirportsToLocation(source_latitude, source_longitude);
    vector<vector<Airport>> res;
    for(auto airport: sources){
        for(auto trip: AirportToCityAirlineOnlyFilter(airport, city, country, airlines))
            res.push_back(trip);
    }
    return res;
}

vector<vector<Airport>> Logic::LocationToCityAirlineAvoidFilters(double source_latitude, double source_longitude, const std::string city, const std::string& country, unordered_set<std::string> airlines){
    vector<Airport> sources = FindClosestAirportsToLocation(source_latitude, source_longitude);
    vector<vector<Airport>> res;
    for(auto airport: sources){
        for(auto trip: AirportToCityAirlineAvoidFilter(airport, city, country, airlines))
            res.push_back(trip);
    }
    return res;
}

vector<vector<Airport>> Logic::LocationToCountryAirlineOnlyFilter(double source_latitude, double source_longitude, const std::string country, unordered_set<std::string> airlines){
    vector<Airport> sources = FindClosestAirportsToLocation(source_latitude, source_longitude);
    vector<vector<Airport>> res;
    for(auto airport: sources){
        for(auto trip: AirportToCountryAirlineOnlyFilter(airport, country, airlines)) {
            res.push_back(trip);
        }
    }
    return res;
}

vector<vector<Airport>> Logic::LocationToCountryAirlineAvoidFilter(double source_latitude, double source_longitude, const std::string country, unordered_set<std::string> airlines){
    vector<Airport> sources = FindClosestAirportsToLocation(source_latitude, source_longitude);
    vector<vector<Airport>> res;
    for(auto airport: sources){
        for(auto trip: AirportToCountryAirlineAvoidFilter(airport, country, airlines)) {
            res.push_back(trip);
        }
    }
    return res;
}

vector<vector<Airport>> Logic::AirportToLocationAirlineOnlyFilters(Airport source, double dest_latitude, double dest_longitude, unordered_set<std::string> airline){
    vector<Airport> destinies = FindClosestAirportsToLocation(dest_latitude, dest_longitude);
    vector<vector<Airport>> res;
    for(auto airport: destinies){
        for(auto trip: AirportToAirportAirlineOnlyFilters(source, airport, airline)){
            res.push_back(trip);
        }
    }
    return res;
}

vector<vector<Airport>> Logic::AirportToLocationAirlineAvoidFilters(Airport source, double dest_latitude, double dest_longitude, unordered_set<std::string> airline){
    vector<Airport> destinies = FindClosestAirportsToLocation(dest_latitude, dest_longitude);
    vector<vector<Airport>> res;
    for(auto airport: destinies){
        for(auto trip: AirportToAirportAirlineAvoidFilters(source, airport, airline)){
            res.push_back(trip);
        }
    }
    return res;
}

void Logic::NormaliseList(list<vector<Airport>>& list1) {
    int max_ = INT_MAX;

    for (const auto& it : list1) {
        if (it.size() < max_)
            max_ = it.size();
    }

    list1.remove_if([max_](const auto& vec) { return vec.size() != max_; });
}
