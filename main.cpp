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

    return 0;
}
