#ifndef PROJETO_2_LOGIC_H
#define PROJETO_2_LOGIC_H

#include <unordered_map>
#include <memory>
#include "Graph.h"
#include "Airport.h"

/**
 * @brief The Logic class represents the main logic of the application, providing functionality to interact with the graph of airports.
 */
class Logic {
private:
private:
    Graph<Airport> graph; /**< Graph representing airports and flights. */
    unordered_map<std::string, std::string> NamesToCodes; /**< Maps Airport names to codes. */
    unordered_map<std::string, Airline> AirlinesCodes; /**< Maps Airlines codes to Airline objects. */
public:
    /**
     * @brief Default constructor for the Logic class.
     */
    Logic();
    /**
     * @brief Parameterized constructor for the Logic class.
     * @param g Graph to initialize the Logic with.
     */
    Logic(Graph<Airport>& g);

    /**
     * @brief Maps Airport names to corresponding codes using the data from the graph.
     */
    void MapAirports();
    /**
     * @brief Gets the map of Airport names to codes.
     * @return Map of Airport names to codes.
     */
    unordered_map<std::string , std::string> getNamesToCodes();
    /**
     * @brief Computes the total number of vertices in the graph.
     * @return Total number of vertices.
     */
    int GlobalNumbers();
    /**
     * @brief Computes the total number of airports in the graph.
     * @return Total number of airports.
     */
    int GlobalNumberOfAirports();
    /**
     * @brief Computes the number of flights departing from a specific city.
     * @param city City code.
     * @return Number of flights departing from the specified city.
     */
    int NumberOfFlightsPerCity(std::string city , std::string country);
    /**
     * @brief Computes the number of flights operated by a specific airline.
     * @param airlineCode Airline code.
     * @return Number of flights operated by the specified airline.
     */
    int NumberOfFlightsPerAirline(const std::string& airlineCode);
    /**
     * @brief Computes the number of countries that an airport flies to.
     * @param airportCode Airport code.
     * @return Number of countries that an airport flies to.
     */
    int NumberOfCountries(std::string airportCode);
    /**
     * @brief Computes the number of different countries that a city flies to.
     * @param city City code , country Country name.
     * @return Number of countries that an city flies to.
     */
    int NumberOfCountriesThatCityFliesTo(std::string city , std::string country);
    /**
     * @brief Performs a breadth-first search (BFS) traversal to find the maximum trip with a given number of stops.
     * @param Airport Source airport for the BFS.
     * @param k Maximum number of stops.
     * @return Vector of vectors representing the maximum trips.
     */
    vector<vector<Airport>> FindMaxTripBfs(const Airport &Airport, int k);
    /**
     * @brief Computes the greatest K indegrees in the graph.
     * @param k Number of greatest indegrees to find.
     * @return Vector of airport codes with the greatest K indegrees.
     */
    vector<string> GreatestKIndeegrees(int k);
    /**
     * @brief Computes the global number of flights in the graph.
     * @return Global number of flights.
     */
    size_t GlobalNumberOfFlights();
    /**
     * @brief Computes the number of flights departing from a specific airport
     * and operated by different airlines.
     * @param AirportCode Airport code.
     * @return Pair of integers representing the number of flights and airlines.
    */
    std::pair<int , int> FlightsOutOfAirportAndDifferentAirlines(const std::string& AirportCode);
    /**
    * @brief Computes the pair of airports at maximum distance in the graph.
    * @return Pair of airports and the distance between them.
    */
    std::pair<std::vector<std::pair<Airport, Airport>> , int> AirportAtMaximumDistance();
    /**
     * @brief Computes the number of destinations for a specific airport.
     * @param airportCode Airport code.
     * @return Number of destinations for the specified airport.
     */
    int NumberOfDestinationsForAirport(const string &airportCode);
    /**
    * @brief Computes the number of destinations for a city.
    * @param city City code.
    * @param country Country code.
    * @return Number of destinations for the specified city.
    */
    int NumberOfDestinationsForCity(const string &airportCode);
    /**
     * @brief Computes the number of destinations for a country.
     * @param country Country code.
     * @return Number of destinations for the specified country.
     */
    int NumberOfDestinationsForCountry(const string &airportCode);

    /**
     * @brief Finds articulation points in the graph.
     * @return Unordered set of Airport objects representing articulation points.
     */
    unordered_set<Airport> findArticulationPoints();
    /**
     * @brief Depth-First Search (DFS) traversal for finding articulation points.
     * @param v Vertex to start the DFS traversal.
     * @param articPoints Unordered set to store articulation points.
     * @param s Stack for DFS traversal.
     * @param index Index for DFS traversal.
     */
    void dfs_articulationPoints(Vertex<Airport> *v, unordered_set<Airport> &articPoints, stack<Vertex<Airport> *> &s,int &index);
    /**
     * @brief Computes the shortest path between two airports using Dijkstra's algorithm.
     * @param initialAirport Starting airport.
     * @param destAirport Destination airport.
     * @return Vector of Airport objects representing the shortest path.
     */
    vector<Airport> shortestPath(const Airport& initialAirport , const Airport& destAirport);
    /**
     * @brief Finds the paths from one airport to another.
     * @param initialAirport Starting airport.
     * @param destAirport Destination airport.
     * @return List of vectors representing paths.
     */
    list<vector<Airport>> AirportToAirport(const Airport& initialAirport, const Airport& destAirport);
    /**
     * @brief Finds paths from one airport to another with specified airline filters.
     * @param initialAirport Starting airport.
     * @param destAirport Destination airport.
     * @param airlines Set of airline codes to include in the paths.
     * @return List of vectors representing paths.
     */
    list<vector<Airport>> AirportToAirportAirlineOnlyFilters(const Airport& initialAirport, const Airport& destAirport , unordered_set<std::string> airlines);
    /**
     * @brief Finds paths from one airport to another with specified airline avoidance filters.
     * @param initialAirport Starting airport.
     * @param destAirport Destination airport.
     * @param airlines Set of airline codes to avoid in the paths.
     * @return List of vectors representing paths.
     */
    list<vector<Airport>> AirportToAirportAirlineAvoidFilters(const Airport& initialAirport, const Airport& destAirport , unordered_set<std::string> airlines);


    list<vector<Airport>> AirportToCity(const Airport& initialAirport, const std::string& city , const std::string& country);
    /**
     * @brief Finds paths from one airport to a city with specified airline avoidance filters.
     * @param initialAirport Starting airport.
     * @param city City code.
     * @param country Country code.
     * @param airlines Set of airline codes to avoid in the paths.
     * @return List of vectors representing paths.
     */
    list<vector<Airport>> AirportToCityAirlineAvoidFilter(const Airport& initialAirport ,const std::string& city , const std::string& country,unordered_set<std::string> airlines);
    /**
     * @brief Finds paths from one airport to a city with specified airline filters.
     * @param initialAirport Starting airport.
     * @param city City code.
     * @param country Country code.
     * @param airlines Set of airline codes to include in the paths.
     * @return List of vectors representing paths.
     */
    list<vector<Airport>> AirportToCityAirlineOnlyFilter(const Airport& initialAirport ,const std::string& city , const std::string& country,unordered_set<std::string> airlines);

    /**
     * @brief Finds paths from one airport to a country.
     * @param initialAirport Starting airport.
     * @param country Country code.
     * @return List of vectors representing paths.
     */
    list<vector<Airport>> AirportToCountry(const Airport& initialAirport, const std::string& country);
    /**
     * @brief Finds paths from one airport to a country with specified airline avoidance filters.
     * @param initialAirport Starting airport.
     * @param country Country code.
     * @param airlines Set of airline codes to avoid in the paths.
     * @return List of vectors representing paths.
     */
    list<vector<Airport>> AirportToCountryAirlineAvoidFilter(Airport initialAirport , std::string country,unordered_set<std::string> airlines);
    /**
     * @brief Finds paths from one airport to a country with specified airline filters.
     * @param initialAirport Starting airport.
     * @param country Country code.
     * @param airlines Set of airline codes to include in the paths.
     * @return List of vectors representing paths.
     */
    list<vector<Airport>> AirportToCountryAirlineOnlyFilter(Airport initialAirport , std::string country,unordered_set<std::string> airlines);

    /**
     * @brief Finds paths from a city to an airport with specified filters.
     * @param destAirport Destination airport.
     * @param city City code.
     * @param country Country code.
     * @param choice Integer representing the type of filter.
     * @param airlines Set of airline codes to include or avoid in the paths.
     * @return List of vectors representing paths.
     */
    list<vector<Airport>> CityToAirport(const Airport& destAirport , const std::string& city, const std::string& country , int choice , unordered_set<std::string> airlines);
    /**
     * @brief Finds paths between two cities with specified filters.
     * @param InitialCity Starting city code.
     * @param InitialCountry Starting country code.
     * @param FinalCity Destination city code.
     * @param FinalCountry Destination country code.
     * @param choice Integer representing the type of filter.
     * @param airlines Set of airline codes to include or avoid in the paths.
     * @return List of vectors representing paths.
     */
    list<vector<Airport>> CityToCity(const std::string& InitialCity, const std::string& InitialCountry,const std::string& FinalCity, const std::string& FinalCountry, int choice , const unordered_set<std::string>& airlines);
    /**
     * @brief Finds paths from a city to a country with specified filters.
     * @param InitialCity Starting city code.
     * @param InitialCountry Starting country code.
     * @param country Destination country code.
     * @param choice Integer representing the type of filter.
     * @param airlines Set of airline codes to include or avoid in the paths.
     * @return List of vectors representing paths.
     */
    list<vector<Airport>> CityToCountry(const std::string& Initialcity, const std::string& InitialCountry, const std::string& country , int choice , const unordered_set<std::string>& airlines);

    /**
  * @brief Finds paths from a country to an airport with specified filters.
  * @param destAirport Destination airport.
  * @param country Country code.
  * @param choice Integer representing the type of filter.
  * @param airlines Set of airline codes to include or avoid in the paths.
  * @return List of vectors representing paths.
  */
    list<vector<Airport>> CountryToAirport(const Airport& destAirport , const std::string& country , int choice , unordered_set<std::string> airlines);
    /**
     * @brief Finds paths from a country to a city with specified filters.
     * @param InitialCountry Starting country code.
     * @param FinalCity Destination city code.
     * @param FinalCountry Destination country code.
     * @param choice Integer representing the type of filter.
     * @param airlines Set of airline codes to include or avoid in the paths.
     * @return List of vectors representing paths.
     */
    list<vector<Airport>> CountryToCity(const string &InitialCountry, const string &FinalCity,const string &FinalCountry, int choice, const unordered_set<std::string> &airlines);
    /**
    * @brief Finds paths between two countries with specified filters.
    * @param InitialCountry Starting country code.
    * @param country Destination country code.
    * @param choice Integer representing the type of filter.
    * @param airlines Set of airline codes to include or avoid in the paths.
    * @return List of vectors representing paths.
    */
    list<vector<Airport>> CountryToCountry(const std::string& InitialCountry, const std::string& country , int choice , const unordered_set<std::string>& airlines);

    /**
     * @brief Finds paths from coordinates to an airport with specified filters.
     * @param source_latitude Source latitude.
     * @param source_longitude Source longitude.
     * @param dest Destination airport.
     * @return List of vectors representing paths.
     */
    list<vector<Airport>> LocationToAirport(double source_latitude, double source_longitude, Airport dest);
    /**
     * @brief Finds paths from coordinates to a city with specified filters.
     * @param source_latitude Source latitude.
     * @param source_longitude Source longitude.
     * @param city Destination city code.
     * @param country Destination country code.
     * @return List of vectors representing paths.
     */
    list<vector<Airport>> LocationToCity(double source_latitude, double source_longitude, const std::string city, const std::string& country);
    /**
     * @brief Finds paths from coordinates to a country with specified filters.
     * @param source_latitude Source latitude.
     * @param source_longitude Source longitude.
     * @param country Destination country code.
     * @return List of vectors representing paths.
     */
    list<vector<Airport>> LocationToCountry(double source_latitude, double source_longitude, const std::string country);
    /**
     * @brief Finds paths from an airport to coordinates with specified filters.
     * @param source Source airport.
     * @param dest_latitude Destination latitude.
     * @param dest_longitude Destination longitude.
     * @return List of vectors representing paths.
     */
    list<vector<Airport>> AirportToLocation(Airport source, double dest_latitude, double dest_longitude);
    /**
     * @brief Finds paths from a city to coordinates with specified filters.
     * @param city Source city code.
     * @param country Source country code.
     * @param dest_latitude Destination latitude.
     * @param dest_longitude Destination longitude.
     * @return List of vectors representing paths.
     */
    list<vector<Airport>> CityToLocation(const std::string city, const std::string country, double dest_latitude, double dest_longitude);

    /**
     * @brief Finds the closest airports to a given location using Breadth-First Search (BFS).
     * @param Latitude Latitude of the location.
     * @param Longitude Longitude of the location.
     * @return Vector of Airport objects representing the closest airports.
     */
    vector<Airport> FindClosestAirportsToLocation(double Latitude, double Longitude);
    /**
     * @brief Finds paths from coordinates to an airport with specified airline filters.
     * @param source_latitude Source latitude.
     * @param source_longitude Source longitude.
     * @param dest Destination airport.
     * @param airlines Set of airline codes to include in the paths.
     * @return List of vectors representing paths.
     */
    list<vector<Airport>> LocationToAirportAirlineOnlyFilters(double source_latitude, double source_longitude, Airport dest, unordered_set<std::string> airlines);
    /**
     * @brief Finds paths from coordinates to an airport with specified airline avoidance filters.
     * @param source_latitude Source latitude.
     * @param source_longitude Source longitude.
     * @param dest Destination airport.
     * @param airlines Set of airline codes to avoid in the paths.
     * @return List of vectors representing paths.
     */
    list<vector<Airport>> LocationToAirportAirlineAvoidFilters(double source_latitude, double source_longitude, Airport dest, unordered_set<std::string> airlines);
    /**
     * @brief Finds paths from coordinates to a city with specified airline filters.
     * @param source_latitude Source latitude.
     * @param source_longitude Source longitude.
     * @param city Destination city code.
     * @param country Destination country code.
     * @param airlines Set of airline codes to include in the paths.
     * @return List of vectors representing paths.
     */
    list<vector<Airport>> LocationToCityAirlineOnlyFilters(double source_latitude, double source_longitude, const std::string city, const std::string& country, unordered_set<std::string> airlines);

    /**
     * @brief Finds paths from coordinates to a city with specified airline avoidance filters.
     * @param source_latitude Source latitude.
     * @param source_longitude Source longitude.
     * @param city Destination city code.
     * @param country Destination country code.
     * @param airlines Set of airline codes to avoid in the paths.
     * @return List of vectors representing paths.
     */
    list<vector<Airport>> LocationToCityAirlineAvoidFilters(double source_latitude, double source_longitude, const std::string city, const std::string& country, unordered_set<std::string> airlines);
    /**
    * @brief Finds paths from coordinates to a country with specified airline filters.
    * @param source_latitude Source latitude.
    * @param source_longitude Source longitude.
    * @param country Destination country code.
    * @param airlines Set of airline codes to include in the paths.
    * @return List of vectors representing paths.
    */
    list<vector<Airport>> LocationToCountryAirlineOnlyFilter(double source_latitude, double source_longitude, const std::string country, unordered_set<std::string> airlines);
    /**
     * @brief Computes a list of paths between a source location and a destination country
     *        with airline avoidance filters using DFS traversal.
     * @param source_latitude Latitude of the source location.
     * @param source_longitude Longitude of the source location.
     * @param country Destination country code.
     * @param airlines Set of airline codes to avoid in the paths.
     * @return List of vectors representing paths between the source location and the destination country
     *         with airline avoidance filters.
     */
    list<vector<Airport>> LocationToCountryAirlineAvoidFilter(double source_latitude, double source_longitude, const std::string country, unordered_set<std::string> airlines);
    /**
     * @brief Computes a list of paths between an airport and a destination location
     *        with airline-only filters using DFS traversal.
     * @param source Starting airport.
     * @param dest_latitude Latitude of the destination location.
     * @param dest_longitude Longitude of the destination location.
     * @param airline Set of airline codes to include in the paths.
     * @return List of vectors representing paths between the airport and the destination location
     *         with airline-only filters.
     */
    list<vector<Airport>> AirportToLocationAirlineOnlyFilters(Airport source, double dest_latitude, double dest_longitude, unordered_set<std::string> airline);
    /**
     * @brief Computes a list of paths between an airport and a destination location
     *        with airline avoidance filters using DFS traversal.
     * @param source Starting airport.
     * @param dest_latitude Latitude of the destination location.
     * @param dest_longitude Longitude of the destination location.
     * @param airline Set of airline codes to avoid in the paths.
     * @return List of vectors representing paths between the airport and the destination location
     *         with airline avoidance filters.
     */
    list<vector<Airport>> AirportToLocationAirlineAvoidFilters(Airport source, double dest_latitude, double dest_longitude, unordered_set<std::string> airline);

    //Auxiliary functions
    /**
    * @brief Haversine Algorithm for computing distances between two points on the Earth.
    * @param lat1 Latitude of the first point.
    * @param lon1 Longitude of the first point.
    * @param lat2 Latitude of the second point.
    * @param lon2 Longitude of the second point.
    * @return Distance between the two points in kilometers.
    */
    double HaversineAlgorithm(double lat1, double lon1,double lat2, double lon2);
    /**
     * @brief Computes a list of airports at a certain distance from a specified airport
     *        using breadth-first search (BFS).
     * @param airportCode Source airport code.
     * @param k Maximum distance from the source airport.
     * @return Vector representing the list of airports at a certain distance.
     */
    vector<Airport> nodesAtDistanceBFS(const string &airportCode, int k);
    /**
     * @brief Analyzes the list of reachable airports and counts the occurrences of each distance value.
     * @param reachableAirports Vector representing the list of reachable airports.
     * @return Vector containing the count of occurrences for each distance.
     */
    vector<int> analyzeReachableAirports(const vector<Airport> &reachableAirports);
    /**
     * @brief Normalizes the given list of vectors by sorting and removing duplicates.
     * @param list1 List of vectors to be normalized.
     */
    void NormaliseList(list<vector<Airport>>& list1);
};


#endif //PROJETO_2_LOGIC_H
