#ifndef PROJETO_2_LOADINGFUNCTIONS_H
#define PROJETO_2_LOADINGFUNCTIONS_H

#include "Graph.h"
#include "Airport.h"
#include <unordered_set>

/**
 * @class LoadingFunctions
 * @brief A class for loading data from CSV files.
 */
class LoadingFunctions {
public:
    /**
     * @brief Load airports into the graph.
     * @param g The graph to load airports into.
     * @details Time complexity: Depends on the size of the airports dataset and the graph operations.
     */
    static void LoadAirports(Graph<Airport>& g);

    /**
     * @brief Load airlines into the graph.
     * @param g The graph to load airlines into.
     * @details Time complexity: Depends on the size of the airlines dataset and the graph operations.
     */
    static void LoadAirlines(Graph<Airport>& g);

    /**
     * @brief Load flights into the graph.
     * @param g The graph to load flights into.
     * @details Time complexity: Depends on the size of the flights dataset and the graph operations.
     */
    static void LoadFlights(Graph<Airport>& g);

    /**
     * @brief Normalize a string by converting it to lowercase.
     * @param str The string to normalize.
     * @details Time complexity: O(n), where n is the length of the string.
     */
    static void NormalizeString(std::string& str);

    /**
     * @brief Get the set of loaded airlines.
     * @return The set of loaded airlines.
     * @details Time complexity: O(1)
     */
    static std::unordered_set<Airline> getAirlines();


private:
    static std::unordered_set<Airport> airports;
    static std::unordered_set<Airline> airlines;

    /**
     * @brief Calculate the Haversine distance between two sets of latitude and longitude coordinates.
     * @param lat1 The latitude of the first point.
     * @param lon1 The longitude of the first point.
     * @param lat2 The latitude of the second point.
     * @param lon2 The longitude of the second point.
     * @return The Haversine distance between the two points.
     * @details Time complexity: O(log n)
     */
    static double HaversineAlgorithm(double lat1, double lon1, double lat2, double lon2);
};

#endif //PROJETO_2_LOADINGFUNCTIONS_H
