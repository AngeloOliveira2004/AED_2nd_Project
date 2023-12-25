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

    std::cout << "Number of Airport destinations available for airport Jose Marti Intl: " << logic.NumberOfDestinationsForAirport("HAV") << endl;

    std::cout << "Number of City destinations available for airport Jose Marti Intl: " << logic.NumberOfDestinationsForCity("HAV") << endl;

    std::cout << "Number of Country destinations available for airport Jose Marti Intl: " << logic.NumberOfDestinationsForCountry("HAV") << endl;

    unordered_set<Airport> essentialAirports = logic.EssentialAirports();

    std::cout << "These airports are essential: " << std::endl;
    for (const Airport& airport : essentialAirports) {
        std::cout << airport.getCode() << "|" << airport.getName() << std::endl;
    }

    return 0;
}
