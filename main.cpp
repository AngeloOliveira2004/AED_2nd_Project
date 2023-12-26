#include <iostream>
#include "Logic/Graph.h"
#include "Logic/LoadingFunctions.h"
#include "Logic/Logic.h"

int main() {
    Graph<Airport> g;

    LoadingFunctions::LoadFlights(g);

    Logic logic = Logic(g);
    /*
    cout << "Number of Airports: " << logic.GlobalNumberOfAirports() << endl;

    cout << "Number of Flights: " << logic.GlobalNumberOfFlights() << endl;


    std::pair<int, int> a;
    a = logic.FlightsOutOfAirportAndDifferentAirlines("PIP");

    std::cout << "Number of flights: " << a.first << " | Number of different airlines: " << a.second << endl;

    std::cout << "Number of flights of TOK: " << logic.NumberOfFlightsPerAirline("ANG") << endl;

    std::cout << "Airport JFK flies to " << logic.NumberOfCountries("JFK") << " countries" << endl;

    std::cout << "Paris flies to " << logic.NumberOfCountriesThatCityFliesTo("Paris") << " cities" << endl;
    */
    logic.TopTrafficAirports(5);
    return 0;
}
