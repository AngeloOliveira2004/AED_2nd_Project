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

        std::pair<int, int> z;

        z = logic.FlightsOutOfAirportAndDifferentAirlines("YHO");

        std::cout << "Number of flights: " << z.first << " | Number of different airlines: " << z.second << endl;

        std::cout << "Number of flights of TOK: " << logic.NumberOfFlightsPerAirline("ANG") << endl;

        std::cout << "Airport JFK flies to " << logic.NumberOfCountries("JFK") << " countries" << endl;

        std::cout << "Elko has " << logic.NumberOfFlightsPerCity("Elko") << " flights available" << endl;

        std::cout << "Paris flies to " << logic.NumberOfCountriesThatCityFliesTo("Paris") << " cities" << endl;

        vector<Airport> tempVector = logic.nodesAtDistanceBFS("INL" , 3);

        vector<int> tempValues = logic.analyzeReachableAirports(tempVector);

        cout << "Number of distinct airports: " << tempValues[0] << endl;
        cout << "Number of distinct countries: " << tempValues[1] << endl;
        cout << "Number of distinct cities: " << tempValues[2] << endl;

        auto start_time1 = std::chrono::high_resolution_clock::now();

        cout << "diameter: " << g.calculateDiameter() << endl;

        auto end_time1 = std::chrono::high_resolution_clock::now();
        auto duration1= std::chrono::duration_cast<std::chrono::milliseconds>(end_time1 - start_time1);

        std::cout << "Time taken by calculateDiameter: " << duration1.count()/1000 << " seconds" << std::endl;

        std::pair< std::vector<std::pair<Airport, Airport>> , int> d = logic.AirportAtMaximumDistance();

        for( auto pair : d.first)
        {
            std::cout << "initial airport : " << pair.first.getCode()
            << " | end airport: " << pair.second.getCode() << " | number of layovers: " << d.second << endl;
        }

        Airport airport = Airport("INL");
        Airport airport1 = Airport("LIS");
        unordered_set<std::string> a;
        a.insert("TSC");
        a.insert("TAP");
        a.insert("RZO");
        a.insert("AAL");
        a.insert("FIN");
        a.insert("BAW");
        a.insert("ANA");
        a.insert("USA");
        cout << "shortes path: " ;
        for (auto pair : logic.airlineAvoidFilters(airport, airport1 , a))
        {
            cout << pair.getCode() << " ";
        }
        a.clear();
        a.insert("RZO");
        for (auto pair : logic.airlineOnlyFilters(airport, airport1 , a))
        {
            cout << pair.getCode() << " ";
        }

        vector<Airport> tempVector1 = logic.nodesAtDistanceBFS("INL" , 11);

        vector<int> tempValues1 = logic.analyzeReachableAirports(tempVector1);

        cout << "Number of distinct airports: " << tempValues1[0] << endl;
        cout << "Number of distinct countries: " << tempValues1[1] << endl;
        cout << "Number of distinct cities: " << tempValues1[2] << endl;
        stack<pair<Airport, Airport>> pairs;

        for(auto v : g.getVertexSet())
        {
            logic.FindMaxTripBfs(pairs , v);
            while (!pairs.empty())
            {
                cout << pairs.top().first.getCode() << " " << pairs.top().second.getCode() << endl;
                pairs.pop();
            }
        }
        auto start_time1 = std::chrono::high_resolution_clock::now();

        int diameter = g.calculateDiameter();

        auto start_time2 = std::chrono::high_resolution_clock::now();

        for(auto v : g.getVertexSet())
        {
            vector<vector<Airport>> a = logic.FindMaxTripBfs(v->getInfo() , diameter);
            if(!a.empty()) {
                for (auto v: a) {
                    vector<Airport> d = v;
                    Airport z = d[0];
                    Airport p = d[d.size() -1];
                    cout << z.getCode() << " to " << p.getCode();
                    cout << endl;
                }
            }
        }

        auto end_time1 = std::chrono::high_resolution_clock::now();
        auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(end_time1 - start_time1);


        std::cout << "Time taken by everything: " << duration1.count()/1000 << " seconds" << std::endl;
*/
        //TODO NORMALISE LIST OF VECTORS FUNCTION
        Airport airport = Airport("INL");
        Airport airport1 = Airport("LIS");
        unordered_set<std::string> a;
        a.insert("TSC");
        a.insert("TAP");
        a.insert("RZO");
        cout << "shortest path: " << endl;
        for (const auto& v : logic.CityToAirport(airport1 , "Larnaca" , "Cyprus" , 1 ,a))
        {
            for(const auto& pair : v)
                cout << pair.getCode() << " ";
            cout << endl;
        }

        for(auto v : g.getVertexSet())
        {
            if(v->getInfo().getName().size() == 3)
            {
                cout << v->getInfo().getName() << endl;
            }
        }


        return 0;
    }
