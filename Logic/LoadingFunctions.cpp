#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>
#include "LoadingFunctions.h"
#include "Logic.h"

std::unordered_set<Airport> LoadingFunctions::airports;
std::unordered_set<Airline> LoadingFunctions::airlines;



/**
 * @brief Finds and erases '\r' in the given string
 * @param g A string
 * @details Time complexity: O(n), where n is length of the string
 */
void LoadingFunctions::NormalizeString(std::string& str) {
    size_t pos = str.find('\r');
    if (pos != std::string::npos) {
        str.erase(pos);
    }
}

/**
 * @brief Loads airports into the graph from a CSV file.
 * @param g The graph to load airports into.
 * @details Time complexity: O(n*p), where n is the number of airports in the CSV file and p is the tokens vector size
 */
void LoadingFunctions::LoadAirports(Graph<Airport>& g) {
    std::ifstream file("dataset/airports.csv");
    if (!file.is_open()) {
        std::cerr << "Failed to open the CSV file." << std::endl;
    }

    std::string line;
    getline(file, line);

    while (getline(file, line)) {
        std::istringstream lineStream(line);
        std::vector<std::string> tokens;
        std::string token;

        while (getline(lineStream, token, ',')) {
            tokens.push_back(token);
        }

        Airport airport = Airport(tokens[0] , tokens[1] , tokens[2] , tokens[3] , stod(tokens[4]) ,stod(tokens[5]));

        if(!g.addVertex(airport)){
            std::cerr << "Failed to add vertex to graph" << std::endl;
        }

        airports.insert(airport);
    }
    file.close();
}

/**
 * @brief Loads airlines into the set of loaded airlines.
 * @param g The graph (not used here).
 * @details Time complexity: O(m*p), where m is the number of airlines in the CSV file and p is the tokens vector size
 */
void LoadingFunctions::LoadAirlines(Graph<Airport> &g) {
    std::ifstream file("dataset/airlines.csv");

    if (!file.is_open()) {
        std::cerr << "Failed to open the CSV file." << std::endl;
    }

    std::string line;
    getline(file, line);

    while (getline(file, line)) {
        std::istringstream lineStream(line);
        std::vector<std::string> tokens;
        std::string token;

        while (getline(lineStream, token, ',')) {
            tokens.push_back(token);
        }

        std::string temp = tokens[3];
        NormalizeString(temp);

        Airline airline = Airline(tokens[0] , tokens[1] , tokens[2] , temp);

        airlines.insert(airline);
    }
    file.close();
}

/**
 * @brief Loads flights into the graph from a CSV file.
 * @param g The graph to load flights into.
 * @details Time complexity: O(p * n), where p is the number of flights in the CSV file and n is the number of airports.
 */
void LoadingFunctions::LoadFlights(Graph<Airport> &g) {
    if(airports.empty())
    {
        LoadAirports(g);
    }
    if(airlines.empty())
    {
        LoadAirlines(g);
    }
    std::ifstream file("dataset/flights.csv");

    if (!file.is_open()) {
        std::cerr << "Failed to open the CSV file." << std::endl;
    }

    std::string line;
    getline(file, line);

    while (getline(file, line)) {

        std::istringstream lineStream(line);
        std::vector<std::string> tokens;
        std::string token;

        while (getline(lineStream, token, ',')) {
            tokens.push_back(token);
        }

        Airport sourceAirport = Airport(tokens[0] , " ", " ", " ", 0.0 , 0.0);
        Airport destAirport = Airport(tokens[1], " ", " "," ",0.0,0.0);

        auto it = airports.find(sourceAirport);
        if (it != airports.end()) {
            sourceAirport = *it;
        }

        auto it1 = airports.find(destAirport);
        if (it1 != airports.end()) {
            destAirport = *it1;
        }

        double result = HaversineAlgorithm(sourceAirport.getLatitude(),sourceAirport.getLongitude(),destAirport.getLatitude(),destAirport.getLongitude());
        g.addEdge(sourceAirport,destAirport,result,tokens[2]);
    }
    file.close();
}

// O(logn) as inbuilt sqrt function is used
/**
 * @brief Calculates the Haversine distance between two sets of latitude and longitude coordinates.
 * @param lat1 The latitude of the first point.
 * @param lon1 The longitude of the first point.
 * @param lat2 The latitude of the second point.
 * @param lon2 The longitude of the second point.
 * @return The Haversine distance between the two points.
 * @details Time complexity: O(log n) where n is the number that gets the square root calculated
 */
double LoadingFunctions::HaversineAlgorithm(double lat1, double lon1,double lat2, double lon2)
{
    double dLat = (lat2 - lat1) *
                  M_PI / 180.0;
    double dLon = (lon2 - lon1) *
                  M_PI / 180.0;

    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;


    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);

    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}
