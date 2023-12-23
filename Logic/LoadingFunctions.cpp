//
// Created by jose-costa on 12/23/23.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>
#include "LoadingFunctions.h"
#include "Logic.h"

std::unordered_set<Airport> LoadingFunctions::airports;
std::unordered_set<Airline> LoadingFunctions::airlines;

void LoadingFunctions::NormaliseString(std::string& str) {
    size_t pos = str.find('\r');
    if (pos != std::string::npos) {
        str.erase(pos);
    }
}
/**
 * @class LoadFiles
 * @brief A class for loading data from CSV files.
 */


/**
     * @brief Loads the respective classes for Ucs of a given Student from a CSV file.
     * @param students The vector of Student objects to be populated.
     * @param AttendencePair The map for attendance data.
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
        NormaliseString(temp);

        Airline airline = Airline(tokens[0] , tokens[1] , tokens[2] , temp);

        airlines.insert(airline);
    }
    file.close();
}

void LoadingFunctions::LoadFlights(Graph<Airport> &g) {
    int failed = 0;
    int succeded = 0;
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
            succeded++;
        }
        else{failed++;}

        auto it1 = airports.find(destAirport);
        if (it1 != airports.end()) {
            destAirport = *it1;
            succeded++;
        }
        else
        {
            failed++;
        }

        double result = HaversineAlgorithm(sourceAirport.getLatitude(),sourceAirport.getLongitude(),destAirport.getLatitude(),destAirport.getLongitude());
        g.addEdge(sourceAirport,destAirport,result,tokens[2]);
    }
    file.close();
    cout << succeded << " " << failed;
}

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