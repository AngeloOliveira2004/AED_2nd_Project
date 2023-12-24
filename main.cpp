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

    std::pair<int , std::vector<unordered_set<std::string>>> b = logic.DestinationsAtDistanceK("EKO" , 2);

    std::cout << "Number os possible destinations "<< b.first << " airports : ";

    for(auto c : b.second[0])
    {
        std::cout << c << " | ";
    }

    cout << endl << " Countries: ";

    for(auto c : b.second[1])
    {
        std::cout << c << " | ";
    }

    cout << endl << " Cities: ";

    for(auto c : b.second[2])
    {
        std::cout << c << " | ";
    }

    return 0;
}
