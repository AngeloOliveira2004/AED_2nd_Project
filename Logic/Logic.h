//
// Created by jose-costa on 12/23/23.
//

#ifndef PROJETO_2_LOGIC_H
#define PROJETO_2_LOGIC_H

#include <unordered_map>
#include <memory>
#include "Graph.h"
#include "Airport.h"
#include "LoadingFunctions.h"


class Logic {
private:
    Graph<Airport> graph;
    //maps Airport names to codes
    unordered_map<std::string , std::string> NamesToCodes;
    unordered_map<std::string , Airline> AirlinesCodes;
public:
    Logic();
    Logic(Graph<Airport>& g);

    int GlobalNumbers();
    int GlobalNumberOfAirports();
    int NumberOfFlightsPerCity(std::string city);
    int NumberOfFlightsPerAirline(const std::string& airlineCode);
    int NumberOfCountries(std::string airportCode);
    int NumberOfCountriesThatCityFliesTo(std::string city);
    vector<vector<Airport>> FindMaxTripBfs(const Airport &Airport, int k);
    vector<string> GreatestKIndeegrees(int k);
    size_t GlobalNumberOfFlights();

    std::pair<int , int> FlightsOutOfAirportAndDifferentAirlines(const std::string& AirportCode);
    std::pair<std::vector<std::pair<Airport, Airport>> , int> AirportAtMaximumDistance();

    int NumberOfDestinationsForAirport(const string &airportCode);
    int NumberOfDestinationsForCity(const string &airportCode);
    int NumberOfDestinationsForCountry(const string &airportCode);

    unordered_set<Airport> findArticulationPoints();

    void dfs_articulationPoints(Vertex<Airport> *v, unordered_set<Airport> &articPoints, stack<Vertex<Airport> *> &s,int &index);

    vector<Airport> shortestPath(const Airport& initialAirport , const Airport& destAirport);

    vector<vector<Airport>> AirportToAirport(const Airport& initialAirport, const Airport& destAirport);
    vector<vector<Airport>> AirportToAirportAirlineOnlyFilters(const Airport& initialAirport, const Airport& destAirport , unordered_set<std::string> airlines);
    vector<vector<Airport>> AirportToAirportAirlineAvoidFilters(const Airport& initialAirport, const Airport& destAirport , unordered_set<std::string> airlines);

    vector<vector<Airport>> AirportToCity(const Airport& initialAirport, const std::string& city , const std::string& country);
    vector<vector<Airport>> AirportToCityAirlineAvoidFilter(const Airport& initialAirport ,const std::string& city , const std::string& country,unordered_set<std::string> airlines);
    vector<vector<Airport>> AirportToCityAirlineOnlyFilter(const Airport& initialAirport ,const std::string& city , const std::string& country,unordered_set<std::string> airlines);

    vector<vector<Airport>> AirportToCountry(const Airport& initialAirport, const std::string& country);
    vector<vector<Airport>> AirportToCountryAirlineAvoidFilter(Airport initialAirport , std::string country,unordered_set<std::string> airlines);
    vector<vector<Airport>> AirportToCountryAirlineOnlyFilter(Airport initialAirport , std::string country,unordered_set<std::string> airlines);

    vector<vector<Airport>> CityToAirport(const Airport& destAirport , const std::string& city, const std::string& country , int choice , unordered_set<std::string> airlines);
    vector<vector<Airport>> CityToCity(std::string city, std::string country , int choice , unordered_set<std::string> airlines);
    vector<vector<Airport>> CityToCountry(std::string city, std::string country , int choice , unordered_set<std::string> airlines);

    vector<vector<Airport>> LocationToAirport(double source_latitude, double source_longitude, Airport dest);
    vector<vector<Airport>> LocationToCity(double source_latitude, double source_longitude, const std::string city, const std::string& country);
    vector<vector<Airport>> LocationToCountry(double source_latitude, double source_longitude, const std::string country);
    vector<vector<Airport>> AirportToLocation(Airport source, double dest_latitude, double dest_longitude);
    vector<vector<Airport>> CityToLocation(const std::string city, const std::string country, double dest_latitude, double dest_longitude);
    vector<vector<Airport>> CountryToLocation(const std::string country, double dest_latitude, double dest_longitude);

    vector<Airport> FindClosestAirportsToLocation(double Latitude, double Longitude);

    //Auxiliary functions
    double HaversineAlgorithm(double lat1, double lon1,double lat2, double lon2);
    vector<Airport> nodesAtDistanceBFS(const string &airportCode, int k);
    vector<int> analyzeReachableAirports(const vector<Airport> &reachableAirports);
    vector<Vertex<Airport>*> AiportsInCountry(const std::string& country) ;
};


#endif //PROJETO_2_LOGIC_H
