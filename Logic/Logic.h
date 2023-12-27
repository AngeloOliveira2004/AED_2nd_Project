//
// Created by jose-costa on 12/23/23.
//

#ifndef PROJETO_2_LOGIC_H
#define PROJETO_2_LOGIC_H

#include <unordered_map>
#include <memory>
#include "Graph.h"
#include "Airport.h"


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

    std::pair<std::vector<std::pair<Airport, Airport>> , int> AirportAtMaximumDistance();

    std::pair<int , int> FlightsOutOfAirportAndDifferentAirlines(const std::string& AirportCode);

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

    //Auxiliary functions
    double HaversineAlgorithm(double lat1, double lon1,double lat2, double lon2);
    vector<Airport> nodesAtDistanceBFS(const string &airportCode, int k);
    vector<int> analyzeReachableAirports(const vector<Airport> &reachableAirports);
    vector<Vertex<Airport>*> AiportsInCountry(const std::string& country) ;
};


#endif //PROJETO_2_LOGIC_H
