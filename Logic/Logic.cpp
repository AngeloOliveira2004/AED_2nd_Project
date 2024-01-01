#include "Logic.h"
#include <cmath>
#include <iostream>
#include <climits>


Logic::Logic(Graph<Airport>& g) : graph(g) {}

/**
 * @brief Calculates the Haversine distance between two sets of latitude and longitude coordinates.
 * @param lat1 The latitude of the first point.
 * @param lon1 The longitude of the first point.
 * @param lat2 The latitude of the second point.
 * @param lon2 The longitude of the second point.
 * @return The Haversine distance between the two points.
 * @details Time complexity: O(log n)
 */
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

/**
 * @brief Maps airport names to their corresponding codes.
 * @details Time complexity: O(V), where V is the number of vertices (airports) in the graph.
 */
void Logic::MapAirports(){
    for(auto v: graph.getVertexSet()){
        this->NamesToCodes[v->getInfo().getName()] = v->getInfo().getCode();
    }
}

/**
 * @brief Gets the mapping of airport names to their codes.
 * @return The unordered map of airport names to codes.
 * @details Time complexity: O(1)
 */
unordered_map<std::string , std::string> Logic::getNamesToCodes(){
    return this->NamesToCodes;
}

/**
 * @brief Calculates the global number of airports and flights.
 * @return The total number of airports and flights.
 * @details Time complexity: O(1)
 */
int Logic::GlobalNumbers() {
    return GlobalNumberOfAirports() + GlobalNumberOfFlights();
}

/**
 * @brief Gets the global number of airports.
 * @return The total number of airports.
 * @details Time complexity: O(1)
 */
int Logic::GlobalNumberOfAirports() {
    return graph.getVertexSet().size();
}

/**
 * @brief Gets the global number of flights.
 * @return The total number of flights.
 * @details Time complexity: O(V), where V is the number of vertices (airports) in the graph.
 */
size_t Logic::GlobalNumberOfFlights() {

    size_t numberFlights = 0;

    for(auto vertex : graph.getVertexSet())
    {
        numberFlights += vertex->getAdj().size();
    }

    return numberFlights;
}

/**
 * @brief Calculates the number of flights out of a specific airport with different airlines.
 * @param AirportCode The code of the airport.
 * @return A pair containing the number of flights and the number of different airlines.
 * @details Time complexity: O(E), where E is the number of edges (flights) in that Vertex of the graph.
 */
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

/**
 * @brief Calculates the number of flights for a specific airline.
 * @param airlineCode The code of the airline.
 * @return The number of flights for the specified airline.
 * @details Time complexity: O(V + E), where V is the number of vertices (airports) and E is the number of edges (flights) in the graph.
 */
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

/**
 * @brief Calculates the number of countries that flights from a specific airport fly to.
 * @param airportCode The code of the airport.
 * @return The number of countries.
 * @details Time complexity: O(V + E), where V is the number of vertices (airports) and E is the number of edges (flights) in the graph.
 */
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

/**
 * @brief Calculates the number of countries that flights from a specific city fly to.
 * @param city The city name.
 * @return The number of countries.
 * @details Time complexity: O(V + E), where V is the number of vertices (airports) and E is the number of edges (flights) in the graph.
 */
int Logic::NumberOfCountriesThatCityFliesTo(std::string city , std::string country) {

    unordered_set<std::string> countries;

    for(auto vertex : graph.getVertexSet())
    {
       auto airport = vertex->getInfo();

       if(airport.getCity() == city && airport.getCountry() == country)
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

/**
 * @brief Calculates the number of flights departing from a specific city.
 * @param city The city name.
 * @return The number of flights.
 * @details Time complexity: O(V), where V is the number of vertices (airports) in the graph.
 */
int Logic::NumberOfFlightsPerCity(std::string city , std::string country) {

    int numberFlights = 0;

    for(auto vertex : graph.getVertexSet())
    {
        auto airport = vertex->getInfo();

        if(vertex->getInfo().getCity() == city && vertex->getInfo().getCountry() == country)
        {
            numberFlights += (int) vertex->getAdj().size();
        }
    }

    return numberFlights;
}
//|||||||||||||||||| Point 5 |||||||||||||||||||||||


/**
 * @brief Calculates the number of unique destinations for flights departing from a specific airport.
 * @param airportCode The code of the airport.
 * @return The number of unique destinations.
 * @details Time complexity: O(V + E), where E is the number of edges (flights) in the graph and V the number of vertices.
 */
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

/**
 * @brief Calculates the number of unique destinations reachable from the specified airport by direct flights.
 * @param airportCode The code of the airport to analyze.
 * @return The number of unique destinations reachable from the specified airport.
 * @details Time Complexity: O(E), where E is the number of edges in the graph.
 */
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

// O(V + E)
/**
 * @brief Calculates the number of unique destinations (countries) for flights departing from a specific country.
 * @param airportCode The code of the airport.
 * @return The number of unique destinations.
 * @details Time complexity: O(V + E), where V is the number of vertices (airports) and E is the number of edges (flights) in the graph.
 */
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
/**
 * @brief Performs a Breadth-First Search (BFS) to find airports at a given distance from a starting airport.
 * @param airportCode The code of the starting airport.
 * @param k The distance parameter.
 * @return A vector of airports at the specified distance.
 * @details Time complexity: O(V + E), where V is the number of vertices (airports) and E is the number of edges (flights) in the graph.
 */
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

/**
 * @brief Analyzes the reachability of airports and provides information about distinct airports, countries, and cities.
 * @param reachableAirports A vector of airports that are reachable.
 * @return A vector containing the count of distinct airports, countries, and cities.
 * @details Time complexity: O(1).
 */
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

/**
 * @brief Finds pairs of airports with the maximum distance between them.
 * @return A pair containing a vector of pairs of airports and the maximum distance.
 * @details Time complexity: O(V + E), where V is the number of vertices (airports) and E is the number of edges (flights) in the graph.
 */
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

/**
 * @brief Performs a special Depth-First Search (DFS) to set numerical values for vertices.
 * @param v The starting vertex.
 */
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

/**
 * @brief Sets all vertices in the graph as unvisited.
 * @param g The graph.
 * @details O(V) where V is the number of vertces on the graph
 */
void setUnvisited(Graph<Airport> g)
{
    for(auto& vertex : g.getVertexSet())
    {
        vertex->setVisited(false);
        vertex->setNum(0);
    }
}

/**
 * @brief Finds maximum trips using Breadth-First Search (BFS) starting from a specific airport with a given diameter.
 * @param airport_ The starting airport.
 * @param diameter The diameter parameter.
 * @return A vector of vectors representing the maximum trips.
 * @details Time complexity: O(V + E), where V is the number of vertices (airports) and E is the number of edges (flights) in the graph.
 */
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
/**
 * @brief Finds the airports with the greatest in-degrees.
 * @param k The number of airports to find.
 * @return A vector of airport codes with the greatest in-degrees.
 * @details Time complexity: O(V*log(V) + V*E), where V is the number of vertices (airports) and E is the number of edges (flights) in the graph.
 */
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
/**
 * @brief Finds the articulation points in the graph.
 * @return An unordered set of airports representing the articulation points.
 * @details Time complexity: O(V + E), where V is the number of vertices (airports) and E is the number of edges (flights) in the graph.
 */
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

// Helper function for findArticulationPoints
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
/**
 * @brief Finds the shortest path between two airports using Breadth-First Search (BFS).
 * @param initialAirport The starting airport.
 * @param destAirport The destination airport.
 * @return A vector of airports representing the shortest path.
 * @details Time complexity: O(V + E), where V is the number of vertices (airports) and E is the number of edges (flights) in the graph.
 */
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
/**
 * @brief Finds the closest airports to a given location specified by latitude and longitude.
 * @param Latitude The latitude of the location.
 * @param Longitude The longitude of the location.
 * @return A vector of airports closest to the specified location.
 * @details Time complexity: O(V), where V is the number of vertices (airports) in the graph.
 */
vector<Airport> Logic::FindClosestAirportsToLocation(double Latitude, double Longitude){
    vector<Airport> res;
    double min_distance = numeric_limits<double>::max();
    for(auto v: graph.getVertexSet()){
        Airport temp = v->getInfo();
        double dist = HaversineAlgorithm(Latitude, Longitude, temp.getLatitude(), temp.getLongitude());
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

/**
 * @brief Finds trips from the given location to the destination airport.
 * @param source_latitude The latitude of the source location.
 * @param source_longitude The longitude of the source location.
 * @param dest The destination airport.
 * @return A vector of trips, each represented as a vector of airports.
 * @details Time complexity: O(V + E), where V is the number of vertices (airports) and E is the number of edges (flights) in the graph.
 */
list<vector<Airport>> Logic::LocationToAirport(double source_latitude, double source_longitude, Airport dest){
    vector<Airport> sources = FindClosestAirportsToLocation(source_latitude, source_longitude);
    list<vector<Airport>> res;
    for(auto airport: sources){
        for(auto trip: AirportToAirport(airport, dest)){
            res.push_back(trip);
        }
    }
    return res;
}

/**
 * @brief Finds trips from the given location to the specified city in the given country.
 * @param source_latitude The latitude of the source location.
 * @param source_longitude The longitude of the source location.
 * @param city The destination city.
 * @param country The destination country.
 * @return A vector of trips, each represented as a vector of airports.
 * @details Time complexity: O(V + E), where V is the number of vertices (airports) and E is the number of edges (flights) in the graph.
 */
list<vector<Airport>> Logic::LocationToCity(double source_latitude, double source_longitude, const std::string city, const std::string& country){
    vector<Airport> sources = FindClosestAirportsToLocation(source_latitude, source_longitude);
    list<vector<Airport>> res;
    for(auto airport: sources){
        for(auto trip: AirportToCity(airport, city, country)){
            res.push_back(trip);
        }
    }
    return res;
}

/**
 * @brief Finds trips from the given location to the specified country.
 * @param source_latitude The latitude of the source location.
 * @param source_longitude The longitude of the source location.
 * @param country The destination country.
 * @return A vector of trips, each represented as a vector of airports.
 * @details Time complexity: O(V + E), where V is the number of vertices (airports) and E is the number of edges (flights) in the graph.
 */
list<vector<Airport>> Logic::LocationToCountry(double source_latitude, double source_longitude, const std::string country){
    vector<Airport> sources = FindClosestAirportsToLocation(source_latitude, source_longitude);
    list<vector<Airport>> res;
    for(auto airport: sources){
        for(auto trip: AirportToCountry(airport, country)){
            res.push_back(trip);
        }
    }
    return res;
}

/**
 * @brief Finds trips from the specified airport to the given location.
 * @param source The source airport.
 * @param dest_latitude The latitude of the destination location.
 * @param dest_longitude The longitude of the destination location.
 * @return A vector of trips, each represented as a vector of airports.
 * @details Time complexity: O(V + E), where V is the number of vertices (airports) and E is the number of edges (flights) in the graph.
 */
list<vector<Airport>> Logic::AirportToLocation(Airport source, double dest_latitude, double dest_longitude){
    vector<Airport> destinies = FindClosestAirportsToLocation(dest_latitude, dest_longitude);
    list<vector<Airport>> res;
    for(auto airport: destinies){
        for(auto trip: AirportToAirport(source, airport)){
            res.push_back(trip);
        }
    }
    return res;
}
/**
 * @brief Finds trips from the specified city in the given country to the given location.
 * @param city The source city.
 * @param country The source country.
 * @param dest_latitude The latitude of the destination location.
 * @param dest_longitude The longitude of the destination location.
 * @return A vector of trips, each represented as a vector of airports.
 * @details Time complexity: O(V + E), where V is the number of vertices (airports) and E is the number of edges (flights) in the graph.
 */
list<vector<Airport>> Logic::CityToLocation(const std::string city, const std::string country, double dest_latitude, double dest_longitude){
    vector<Airport> destinies = FindClosestAirportsToLocation(dest_latitude, dest_longitude);
    list<vector<Airport>> res;
    unordered_set<std::string> airline_names;
    for(auto airport: destinies){
        for(auto trip: CityToAirport(airport, city, country, 1, airline_names)){
            res.push_back(trip);
        }
    }
    return res;
}
/**
 * @brief Finds trips from the given location to the destination airport, considering airline filters.
 * @param source_latitude The latitude of the source location.
 * @param source_longitude The longitude of the source location.
 * @param dest The destination airport.
 * @param airlines A set of airline codes to include in the trips.
 * @return A vector of trips, each represented as a vector of airports.
 * @details Time complexity: O(V + E), where V is the number of vertices (airports) and E is the number of edges (flights) in the graph.
 */
list<vector<Airport>> Logic::LocationToAirportAirlineOnlyFilters(double source_latitude, double source_longitude, Airport dest, unordered_set<std::string> airlines){
    vector<Airport> sources = FindClosestAirportsToLocation(source_latitude, source_longitude);
    list<vector<Airport>> res;
    for(auto airport: sources){
        for(auto trip: AirportToAirportAirlineOnlyFilters(airport, dest, airlines))
            res.push_back(trip);
    }
    return res;
}
/**
 * @brief Finds trips from the given location to the destination airport, avoiding specified airlines.
 * @param source_latitude The latitude of the source location.
 * @param source_longitude The longitude of the source location.
 * @param dest The destination airport.
 * @param airlines A set of airline codes to avoid in the trips.
 * @return A vector of trips, each represented as a vector of airports.
 * @details Time complexity: O(V + E), where V is the number of vertices (airports) and E is the number of edges (flights) in the graph.
 */
list<vector<Airport>> Logic::LocationToAirportAirlineAvoidFilters(double source_latitude, double source_longitude, Airport dest, unordered_set<std::string> airlines){
    vector<Airport> sources = FindClosestAirportsToLocation(source_latitude, source_longitude);
    list<vector<Airport>> res;
    for(auto airport: sources){
        for(auto trip: AirportToAirportAirlineAvoidFilters(airport, dest, airlines))
            res.push_back(trip);
    }
    return res;
}
/**
 * @brief Finds trips from the given location to the specified city in the given country, considering airline filters.
 * @param source_latitude The latitude of the source location.
 * @param source_longitude The longitude of the source location.
 * @param city The destination city.
 * @param country The destination country.
 * @param airlines A set of airline codes to include in the trips.
 * @return A vector of trips, each represented as a vector of airports.
 * @details Time complexity: O(V + E), where V is the number of vertices (airports) and E is the number of edges (flights) in the graph.
 */
list<vector<Airport>> Logic::LocationToCityAirlineOnlyFilters(double source_latitude, double source_longitude, const std::string city, const std::string& country, unordered_set<std::string> airlines){
    vector<Airport> sources = FindClosestAirportsToLocation(source_latitude, source_longitude);
    list<vector<Airport>> res;
    for(auto airport: sources){
        for(auto trip: AirportToCityAirlineOnlyFilter(airport, city, country, airlines))
            res.push_back(trip);
    }
    return res;
}
/**
 * @brief Finds trips from the given location to the specified city in the given country, avoiding specified airlines.
 * @param source_latitude The latitude of the source location.
 * @param source_longitude The longitude of the source location.
 * @param city The destination city.
 * @param country The destination country.
 * @param airlines A set of airline codes to avoid in the trips.
 * @return A vector of trips, each represented as a vector of airports.
 * @details Time complexity: O(V + E), where V is the number of vertices (airports) and E is the number of edges (flights) in the graph.
 */
list<vector<Airport>> Logic::LocationToCityAirlineAvoidFilters(double source_latitude, double source_longitude, const std::string city, const std::string& country, unordered_set<std::string> airlines){
    vector<Airport> sources = FindClosestAirportsToLocation(source_latitude, source_longitude);
    list<vector<Airport>> res;
    for(auto airport: sources){
        for(auto trip: AirportToCityAirlineAvoidFilter(airport, city, country, airlines))
            res.push_back(trip);
    }
    return res;
}
/**
 * @brief Finds trips from the given location to the specified country, considering airline filters.
 * @param source_latitude The latitude of the source location.
 * @param source_longitude The longitude of the source location.
 * @param country The destination country.
 * @param airlines A set of airline codes to include in the trips.
 * @return A vector of trips, each represented as a vector of airports.
 * @details Time complexity: O(V + E), where V is the number of vertices (airports) and E is the number of edges (flights) in the graph.
 */
list<vector<Airport>> Logic::LocationToCountryAirlineOnlyFilter(double source_latitude, double source_longitude, const std::string country, unordered_set<std::string> airlines){
    vector<Airport> sources = FindClosestAirportsToLocation(source_latitude, source_longitude);
    list<vector<Airport>> res;
    for(auto airport: sources){
        for(auto trip: AirportToCountryAirlineOnlyFilter(airport, country, airlines)) {
            res.push_back(trip);
        }
    }
    return res;
}
/**
* @brief Finds trips from the given location to the specified country, avoiding specified airlines.
* @param source_latitude The latitude of the source location.
* @param source_longitude The longitude of the source location.
* @param country The destination country.
* @param airlines A set of airline codes to avoid in the trips.
* @return A vector of trips, each represented as a vector of airports.
* @details Time complexity: O(V + E), where V is the number of vertices (airports) and E is the number of edges (flights) in the graph.
*/
list<vector<Airport>> Logic::LocationToCountryAirlineAvoidFilter(double source_latitude, double source_longitude, const std::string country, unordered_set<std::string> airlines){
    vector<Airport> sources = FindClosestAirportsToLocation(source_latitude, source_longitude);
    list<vector<Airport>> res;
    for(auto airport: sources){
        for(auto trip: AirportToCountryAirlineAvoidFilter(airport, country, airlines)) {
            res.push_back(trip);
        }
    }
    return res;
}
/**
 * @brief Finds trips from the specified airport to the given location, considering airline filters.
 * @param source The source airport.
 * @param dest_latitude The latitude of the destination location.
 * @param dest_longitude The longitude of the destination location.
 * @param airline A set of airline codes to include in the trips.
 * @return A vector of trips, each represented as a vector of airports.
 * @details Time complexity: O(V + E), where V is the number of vertices (airports) and E is the number of edges (flights) in the graph.
 */
list<vector<Airport>> Logic::AirportToLocationAirlineOnlyFilters(Airport source, double dest_latitude, double dest_longitude, unordered_set<std::string> airline){
    vector<Airport> destinies = FindClosestAirportsToLocation(dest_latitude, dest_longitude);
    list<vector<Airport>> res;
    for(auto airport: destinies){
        for(auto trip: AirportToAirportAirlineOnlyFilters(source, airport, airline)){
            res.push_back(trip);
        }
    }
    return res;
}
/**
 * @brief Finds trips from the specified airport to the given location, avoiding specified airlines.
 * @param source The source airport.
 * @param dest_latitude The latitude of the destination location.
 * @param dest_longitude The longitude of the destination location.
 * @param airline A set of airline codes to avoid in the trips.
 * @return A vector of trips, each represented as a vector of airports.
 * @details Time complexity: O(V + E), where V is the number of vertices (airports) and E is the number of edges (flights) in the graph.
 */
list<vector<Airport>> Logic::AirportToLocationAirlineAvoidFilters(Airport source, double dest_latitude, double dest_longitude, unordered_set<std::string> airline){
    vector<Airport> destinies = FindClosestAirportsToLocation(dest_latitude, dest_longitude);
    list<vector<Airport>> res;
    for(auto airport: destinies){
        for(auto trip: AirportToAirportAirlineAvoidFilters(source, airport, airline)){
            res.push_back(trip);
        }
    }
    return res;
}

//|||||||||||||||||| FILTERS ||||||||||||||||||
/**
 * @brief Finds trips from the specified airport to the given airport.
 * @param initialAirport The source airport.
 * @param destAirport The destination airport.
 * @return A list of trips, each represented as a vector of airports.
 * @details Time complexity: O(V + E), where V is the number of vertices (airports) and E is the number of edges (flights) in the graph.
 */
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
/**
 * @brief Finds trips from the specified airport to the given airport, considering airline filters.
 * @param initialAirport The source airport.
 * @param destAirport The destination airport.
 * @param airlines A set of airline codes to include in the trips.
 * @return A list of trips, each represented as a vector of airports.
 * @details Time complexity: O(V + E), where V is the number of vertices (airports) and E is the number of edges (flights) in the graph.
 */
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
            for(auto strig : airlines)
            {
                string temp1 = strig;
            }
            if(airlines.find(e.getAirline()) != airlines.end())
            {
                string temp = e.getAirline();
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
/**
 * @brief Finds trips from the specified airport to the given airport, avoiding specified airlines.
 * @param initialAirport The source airport.
 * @param destAirport The destination airport.
 * @param airlines A set of airline codes to avoid in the trips.
 * @return A list of trips, each represented as a vector of airports.
 * @details Time complexity: O(V + E), where V is the number of vertices (airports) and E is the number of edges (flights) in the graph.
 */
list<vector<Airport>>
Logic::AirportToAirportAirlineAvoidFilters(const Airport &initialAirport, const Airport &destAirport,
                                           unordered_set<std::string> airlines) {
    for(auto string_ : airlines)
    {
        string temp = string_;
    }
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

/**
 * @brief Finds trips from the specified airport to the given city in the given country.
 * @param initialAirport The source airport.
 * @param city The destination city.
 * @param country The destination country.
 * @return A list of trips, each represented as a vector of airports.
 * @details Time complexity: O(V + E), where V is the number of vertices (airports) and E is the number of edges (flights) in the graph.
 */
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
/**
 * @brief Finds trips from the specified airport to the given city in the given country, avoiding specified airlines.
 * @param initialAirport The source airport.
 * @param city The destination city.
 * @param country The destination country.
 * @param airlines A set of airline codes to avoid in the trips.
 * @return A list of trips, each represented as a vector of airports.
 * @details Time complexity: O(V + E), where V is the number of vertices (airports) and E is the number of edges (flights) in the graph.
 */
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
/**
 * @brief Finds trips from the specified airport to the given city in the given country, considering airline filters.
 * @param initialAirport The source airport.
 * @param city The destination city.
 * @param country The destination country.
 * @param airlines A set of airline codes to include in the trips.
 * @return A list of trips, each represented as a vector of airports.
 * @details Time complexity: O(V + E), where V is the number of vertices (airports) and E is the number of edges (flights) in the graph.
 */
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
/**
 * @brief Finds trips from the specified airport to the given country.
 * @param initialAirport The source airport.
 * @param country The destination country.
 * @return A list of trips, each represented as a vector of airports.
 * @details Time complexity: O(V + E), where V is the number of vertices (airports) and E is the number of edges (flights) in the graph.
 */
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
/**
 * @brief Finds trips from the specified airport to the given country, avoiding specified airlines.
 * @param initialAirport The source airport.
 * @param country The destination country.
 * @param airlines A set of airline codes to avoid in the trips.
 * @return A list of trips, each represented as a vector of airports.
 * @details Time complexity: O(V + E), where V is the number of vertices (airports) and E is the number of edges (flights) in the graph.
 */
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
/**
 * @brief Finds trips from the specified airport to the given country, considering airline filters.
 * @param initialAirport The source airport.
 * @param country The destination country.
 * @param airlines A set of airline codes to include in the trips.
 * @return A list of trips, each represented as a vector of airports.
 * @details Time complexity: O(V + E), where V is the number of vertices (airports) and E is the number of edges (flights) in the graph.
 */
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
/**
 * @brief Finds trips from airports in a city to the specified airport.
 * @param destAirport The destination airport.
 * @param city The city where the initial airports are located.
 * @param country The country where the initial airports are located.
 * @param choice The choice of filter (1: No filter, 2: Airline Avoidance, 3: Airline Only).
 * @param airlines Set of airlines to avoid or include based on the choice.
 * @return A list of trips, each represented as a vector of airports.
 * @details Time complexity: O(I * (V + E)), where I is the number of initial airports, V is the number of vertices (airports),
 * and E is the number of edges (flights) in the graph.
 */
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
/**
 * @brief Finds trips from airports in an initial city to airports in a final city.
 * @param InitialCity The initial city.
 * @param InitialCountry The country where the initial city is located.
 * @param FinalCity The final city.
 * @param FinalCountry The country where the final city is located.
 * @param choice The choice of filter (1: No filter, 2: Airline Avoidance, 3: Airline Only).
 * @param airlines Set of airlines to avoid or include based on the choice.
 * @return A list of trips, each represented as a vector of airports.
 * @details Time complexity: O(I * (V + E)), where I is the number of initial airports, V is the number of vertices (airports),
 * and E is the number of edges (flights) in the graph.
 */
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

/**
 * @brief Finds trips from airports in an initial city to airports in a final country.
 * @param Initialcity The initial city.
 * @param InitialCountry The country where the initial city is located.
 * @param FinalCountry The country where the final city is located.
 * @param choice The choice of filter (1: No filter, 2: Airline Avoidance, 3: Airline Only).
 * @param airlines Set of airlines to avoid or include based on the choice.
 * @return A list of trips, each represented as a vector of airports.
 * @details Time complexity: O(I * (V + E)), where I is the number of initial airports, V is the number of vertices (airports),
 * and E is the number of edges (flights) in the graph.
 */
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

    for(auto v : initialAirports)
    {
        string temp = v->getInfo().getCode();
    }
    string temp1 = FinalCountry;
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
/**
 * @brief Finds trips from airports in a country to the specified airport.
 * @param destAirport The destination airport.
 * @param country The country where the initial airports are located.
 * @param choice The choice of filter (1: No filter, 2: Airline Avoidance, 3: Airline Only).
 * @param airlines Set of airlines to avoid or include based on the choice.
 * @return A list of trips, each represented as a vector of airports.
 * @details Time complexity: O(I * (V + E)), where I is the number of initial airports, V is the number of vertices (airports),
 * and E is the number of edges (flights) in the graph.
 */
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
/**
 * @brief Finds trips from airports in a country to airports in the specified city.
 * @param InitialCountry The country where the initial airports are located.
 * @param FinalCity The final city.
 * @param FinalCountry The country where the final city is located.
 * @param choice The choice of filter (1: No filter, 2: Airline Avoidance, 3: Airline Only).
 * @param airlines Set of airlines to avoid or include based on the choice.
 * @return A list of trips, each represented as a vector of airports.
 * @details Time complexity: O(I * (V + E)), where I is the number of initial airports, V is the number of vertices (airports),
 * and E is the number of edges (flights) in the graph.
 */
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
/**
 * @brief Finds trips from airports in a country to airports in another country.
 * @param InitialCountry The country where the initial airports are located.
 * @param country The country where the final airports are located.
 * @param choice The choice of filter (1: No filter, 2: Airline Avoidance, 3: Airline Only).
 * @param airlines Set of airlines to avoid or include based on the choice.
 * @return A list of trips, each represented as a vector of airports.
 * @details Time complexity: O(I * (V + E)), where I is the number of initial airports, V is the number of vertices (airports),
 * and E is the number of edges (flights) in the graph.
 */
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


void Logic::NormaliseList(list<vector<Airport>>& list1) {
    int max_ = INT_MAX;

    for (const auto& it : list1) {
        if (it.size() < max_)
            max_ = it.size();
    }

    list1.remove_if([max_](const auto& vec) { return vec.size() != max_; });
}
