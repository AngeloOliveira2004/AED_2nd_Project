#include <iostream>
#include "Logic/Graph.h"
#include "Logic/LoadingFunctions.h"

int main() {

    Graph<Airport> g;

    LoadingFunctions::LoadFlights(g);


    return 0;
}
