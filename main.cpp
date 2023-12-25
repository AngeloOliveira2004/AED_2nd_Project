#include <iostream>
#include "Logic/Graph.h"
#include "Logic/LoadingFunctions.h"
#include "Logic/Logic.h"

int main() {
    Graph<Airport> g;

    LoadingFunctions::LoadFlights(g);

    Logic logic = Logic(g);

    cout << "Number of Airports: " << logic.GlobalNumberOfAirports() << endl;

    cout << "Number of Flights: " << logic.GlobalNumberOfFlights() << endl;

    std::pair<int, int> a;

    a = logic.FlightsOutOfAirportAndDifferentAirlines("VSA");

    std::cout << "Number of flights: " << a.first << " | Number of different airlines: " << a.second << endl;

    std::cout << "Number of flights of TOK: " << logic.NumberOfFlightsPerAirline("ANG") << endl;

    std::cout << "Airport JFK flies to " << logic.NumberOfCountries("JFK") << " countries" << endl;

    std::cout << "Elko has " << logic.NumberOfFlightsPerCity("Elko") << " flights available" << endl;

    std::cout << "Paris flies to " << logic.NumberOfCountriesThatCityFliesTo("Paris") << " cities" << endl;

    vector<Airport> tempVector = logic.nodesAtDistanceBFS("INL" , 8);

    vector<int> tempValues = logic.analyzeReachableAirports(tempVector);

    cout << "Number of distinct airports: " << tempValues[0] << endl;
    cout << "Number of distinct countries: " << tempValues[1] << endl;
    cout << "Number of distinct cities: " << tempValues[2] << endl;



    return 0;
}
