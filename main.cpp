#include <iostream>
#include <chrono>
#include "Logic/Graph.h"
#include "Logic/LoadingFunctions.h"
#include "Logic/Logic.h"

int main() {
    Graph<Airport> g;

    auto start_time = std::chrono::high_resolution_clock::now();

    // Measure time taken by LoadFlights function
    LoadingFunctions::LoadFlights(g);

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    std::cout << "Time taken by LoadFlights: " << duration.count()/1000 << " seconds" << std::endl;

    Logic logic = Logic(g);
/*
    cout << "Number of Airports: " << logic.GlobalNumberOfAirports() << endl;

    cout << "Number of Flights: " << logic.GlobalNumberOfFlights() << endl;

    std::pair<int, int> a;

    a = logic.FlightsOutOfAirportAndDifferentAirlines("VSA");

    std::cout << "Number of flights: " << a.first << " | Number of different airlines: " << a.second << endl;

    std::cout << "Number of flights of TOK: " << logic.NumberOfFlightsPerAirline("ANG") << endl;

    std::cout << "Airport JFK flies to " << logic.NumberOfCountries("JFK") << " countries" << endl;

    std::cout << "Elko has " << logic.NumberOfFlightsPerCity("Elko") << " flights available" << endl;

    std::cout << "Paris flies to " << logic.NumberOfCountriesThatCityFliesTo("Paris") << " cities" << endl;

    vector<Airport> tempVector = logic.nodesAtDistanceBFS("INL" , 3);

    vector<int> tempValues = logic.analyzeReachableAirports(tempVector);

    cout << "Number of distinct airports: " << tempValues[0] << endl;
    cout << "Number of distinct countries: " << tempValues[1] << endl;
    cout << "Number of distinct cities: " << tempValues[2] << endl;
*/

    cout << "diameter: " << g.calculateDiameter();
/*
    std::vector<std::pair<Airport, Airport>> d = logic.AirportAtMaximumDistance();
    std::cout << "airport: " << d[0].first.getCode() ;
    for(auto e : d)
    {
        std::cout << "max_dest :" << e.second.getCode();
    }
*/
    return 0;
}
