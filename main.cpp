#include <iostream>
#include "Logic/Graph.h"
#include "Logic/LoadingFunctions.h"

int main() {

    Graph<Airport> g;

    LoadingFunctions::LoadFlights(g);

    for(auto vertex : g.getVertexSet())
    {
        cout << vertex->getInfo().getCode() <<" | " << vertex->getAdj().size() << endl;
    }
    //69-12
    return 0;
}
