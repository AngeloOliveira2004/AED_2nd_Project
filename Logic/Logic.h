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

    std::pair<int , int> FlightsOutOfAirportAndDifferentAirlines(const std::string& AirportCode);
    std::pair<std::vector<std::pair<Airport, Airport>> , int> AirportAtMaximumDistance();

    int NumberOfDestinationsForAirport(const string &airportCode);
    int NumberOfDestinationsForCity(const string &airportCode);
    int NumberOfDestinationsForCountry(const string &airportCode);

    unordered_set<Airport> findArticulationPoints();

    void dfs_articulationPoints(Vertex<Airport> *v, unordered_set<Airport> &articPoints, stack<Vertex<Airport> *> &s,int &index);

    vector<Airport> shortestPath(const Airport& initialAirport , const Airport& destAirport);

    list<vector<Airport>> AirportToAirport(const Airport& initialAirport, const Airport& destAirport);
    list<vector<Airport>> AirportToAirportAirlineOnlyFilters(const Airport& initialAirport, const Airport& destAirport , unordered_set<std::string> airlines);
    list<vector<Airport>> AirportToAirportAirlineAvoidFilters(const Airport& initialAirport, const Airport& destAirport , unordered_set<std::string> airlines);

    list<vector<Airport>> AirportToCity(const Airport& initialAirport, const std::string& city , const std::string& country);
    list<vector<Airport>> AirportToCityAirlineAvoidFilter(const Airport& initialAirport ,const std::string& city , const std::string& country,unordered_set<std::string> airlines);
    list<vector<Airport>> AirportToCityAirlineOnlyFilter(const Airport& initialAirport ,const std::string& city , const std::string& country,unordered_set<std::string> airlines);

    list<vector<Airport>> AirportToCountry(const Airport& initialAirport, const std::string& country);
    list<vector<Airport>> AirportToCountryAirlineAvoidFilter(Airport initialAirport , std::string country,unordered_set<std::string> airlines);
    list<vector<Airport>> AirportToCountryAirlineOnlyFilter(Airport initialAirport , std::string country,unordered_set<std::string> airlines);

    list<vector<Airport>> CityToAirport(const Airport& destAirport , const std::string& city, const std::string& country , int choice , unordered_set<std::string> airlines);
    list<vector<Airport>> CityToCity(const std::string& InitialCity, const std::string& InitialCountry,const std::string& FinalCity, const std::string& FinalCountry, int choice , const unordered_set<std::string>& airlines);
    list<vector<Airport>> CityToCountry(const std::string& Initialcity, const std::string& InitialCountry, const std::string& country , int choice , const unordered_set<std::string>& airlines);

    list<vector<Airport>> CountryToAirport(const Airport& destAirport , const std::string& country , int choice , unordered_set<std::string> airlines);
    list<vector<Airport>> CountryToCity(const string &InitialCountry, const string &FinalCity,const string &FinalCountry, int choice, const unordered_set<std::string> &airlines);
    list<vector<Airport>> CountryToCountry(const std::string& InitialCountry, const std::string& country , int choice , const unordered_set<std::string>& airlines);

    //Auxiliary functions
    double HaversineAlgorithm(double lat1, double lon1,double lat2, double lon2);
    vector<Airport> nodesAtDistanceBFS(const string &airportCode, int k);
    vector<int> analyzeReachableAirports(const vector<Airport> &reachableAirports);
    void NormaliseList(list<vector<Airport>>& list1);
};


#endif //PROJETO_2_LOGIC_H
