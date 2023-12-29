#include <thread>
#include <chrono>
#include "UI.h"

UI::UI() {}

void UI::loading_stuff(UI &ui) {
    LoadingFunctions::LoadFlights(g);
    this->logic = Logic(g);
    ui.load_sets();
    for(auto airline : LoadingFunctions::getArlines()){
        airlines.insert(airline.getCallSign());
    }
    diameter = g.calculateDiameter();
}

void UI::load_sets(){
    for(auto airport: g.getVertexSet()){
        this->cities.insert(airport->getInfo().getCity());
        this->airport_codes.insert(airport->getInfo().getCode());
        this->countries.insert(airport->getInfo().getCountry());
    }
}

void UI::clear_screen() {
    int i = 0;
    while(i != 100) {
        cout << endl;
        i++;
    }
}

bool UI::validate_input(char &op, const char lower_bound, const char upper_bound) {
    std::string tempValue;
    while(true){
        std::cin >> tempValue;
        std::cout << "\n";
        op = tempValue[0];
        op = std::toupper(op);
        if (std::cin.fail() || tempValue.length() != 1) {
            std::cout << "Introduce a valid option (" << lower_bound << "-" << upper_bound << "): ";
        }else{
            break;
        }
    }
    while (op < lower_bound || op > upper_bound) {
        std::cout << "Introduce a valid option (" << lower_bound << "-" << upper_bound << "): ";
        std::cin.clear();
        std::cin >> op;
    }
    return true;
}

void UI::menu_start() {
    char op;
    cout << "#################################################" << endl
         << "@@@@@  @@@@@  @@@@   @@@@@   @@@   @@@@   @@@@@  " << endl
         << "@   @    @    @@ @@  @@ @@  @   @  @@ @@    @    " << endl
         << "@@@@@    @    @@@@   @@@@@  @   @  @@@@     @    " << endl
         << "@   @    @    @@ @@  @@     @   @  @@ @@    @    " << endl
         << "@   @  @@@@@  @@ @@  @@      @@@   @@ @@    @    " << endl
         << "#################################################" << endl << '\n'
         << "Welcome to the Air Travel Flight Management System, what would you like to do?" << endl
         << "A. Proceed to the application" << endl
         << "B. Close the application" << endl
         << "Insert the letter: " ;
    validate_input(op,'A','B');
    switch(op){
        case 'A':
            menu_options();
            break;
        case 'B':
            cout << "Thanks for using our management system app!" << endl << "\n"
                 << "Made by: " << endl
                 << "Ângelo Oliveira || 202207798" << endl
                 << "José Costa      || 202207871" << endl
                 << "Bernardo Sousa  || 202206009" << endl;
            this_thread::sleep_for(chrono::seconds(2)); // Espera 2 segundos antes de fechar o terminal
            exit(0);

    }
}

void UI::main_menu(){
    char op;
    clear_screen();
    cout << "What would you like to know?" << endl;
    cout << "A. Consult Flights" << endl
         << "B. Consult Flight Statistics" << endl
         << "C. Plan a Trip" << endl
         << "D. Exit the Application" << endl
         << "Insert your choice:";

    validate_input(op, 'A', 'D');
    switch(op){
        case 'A':
            flight_consultation();
        case 'B':
            statistics_menu();
        case 'C':
            //trip_planner()
        case 'D':
            //exit_menu()
    }
}

void UI::trip_planner(){
    char op;
    cout << "How would you like to chose your starting point?" << endl
         << "A. Origin Airport" << endl
         << "B. Origin Country" << endl
         << "C: Origin City" << endl
         << "C. Origin Coordinates" << endl
         << "Insert your option:";
    validate_input(op, 'A', 'D');
    switch ((op)) {
        case 'A':
            string airport_code;
            cout << "Insert the code of the airport where you would like to go from:" << endl;
            cin >> airport_code;
            if(!g.findVertex(airport_code)){
                cout << "Airport not found. Please enter a valid airport code" << endl;
            }
            else{
                Airport source_airport = Airport(airport_code);
            }
            break;
        case 'B':
    }
}

void UI::flight_consultation() {
    char op;
    cout << "How would you like to search for your flight? " << endl
    << "A. Consult number of flights out of an airport and from how many different airlines;" << endl
    << "B.Consult number of flights per city/airline " << endl
    << "Insert your choice: ";

    validate_input(op, 'A', 'B');
    switch(op){
        case 'A':
            number_out();
            break;
        case 'B':
            number_flights();
            break;

    }
}

void UI::statistics_menu(){
    char op;
    cout << "What statistics would you like to see?" << endl
    << "A. Global Statistics" << endl
    << "B. Airport Statistics" << endl
    << "C. Airline/City Statistics" << endl
    << "D. Country Statistics" << endl
    << "Insert your choice:";

    validate_input(op, 'A', 'E');
    switch(op){
        case 'A':
            global_numbers();
            break;
        case 'B':
            airport_statistics();
            break;
        case 'C':
            number_flights();
            break;
        case 'D':
            number_countries();
            break;
    }
}


void UI::airport_statistics(){
    char op;
    cout << "Which statistics would you like to know?" << endl
         <<"A. Consult number of destinations (airports, cities or countries) available for a given airport;" << endl
         <<"B. Consult number of reachable destinations from a given airport in a maximum of X lay-overs" << endl
         <<"C. Consult top-k airport with the greatest air traffic capacity, " << endl
         <<"D. Consult essential airports to the network's circulation capability" << endl
         << "Insert your option:";
    validate_input(op, 'A', 'D');
    switch (op){
        case 'A':
            number_reachable_destinations();
        case 'B':
            number_reachable_destinations_k();
        case 'C':
            greatest_traffic();
        case 'D':
            essential_airports();
    }

}


void UI::menu_options() {
    char op;
    clear_screen();
    cout << "What option would you like to choose?" << endl << '\n'
         << "A. Consult global number of airports and number of available flights" << endl //Global statistics
         << "B. Consult number of flights out of an airport and from how many different airlines;" << endl //flight consultation
         << "C. Consult number of flights per city/airline" << endl //flight consultation
         << "D. Consult number of different countries that a given airport/city flies to" << endl //Country statistics
         << "E. Consult number of destinations (airports, cities or countries) available for a given airport;" << endl // airport statistics
         << "F. Consult number of reachable destinations from a given airport in a maximum of X lay-overs" << endl // airport statistics
         << "G. Consult trip(s) with the greatest number of stops in between them" << endl
         << "H. Consult top-k airport with the greatest air traffic capacity, " << endl //airport statistics
         << "I. Consult essential airports to the network's circulation capability" << endl //airport statistics
         << "J. Consult best flight option(s) for a given source and destination locations" << endl //trip planner (ToDo)
         << "Insert the letter: ";
    validate_input(op,'A','J');
    switch(op){
        case 'A':
            global_numbers();
            break;
        case 'B':
            number_out();
            break;
        case 'C':
            number_flights();
            break;
        case 'D':
            number_countries();
            break;
        case 'E':
            number_reachable_destinations();
            break;
        case 'F':
            number_reachable_destinations_k();
            break;
        case 'G':
            longest_trip();
            break;
        case 'H':
            greatest_traffic();
            break;
        case 'I':
            essential_airports();
            break;
        case 'J':
            break;
    }
}

void UI::back_menu(){
    char op;
    std::cout << "Press A to go back to the menu: ";
    validate_input(op,'A','A');
    menu_options();
}

void UI::global_numbers() {
    char op;
    cout << "Number of Airports: " << logic.GlobalNumberOfAirports() << endl;
    cout << "Number of Flights: " << logic.GlobalNumberOfFlights() << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
    std::cout << "Press A to go back to the menu: ";
    validate_input(op,'A','A');
    menu_options();
}

void UI::number_out() {
    char op;
    bool validate = false;
    std::pair<int, int> z;
    string airport_code;
    while(!validate){
        airport_code = "";
        cout << "What's the code of the airport you would like to know the information?: ";
        cin >> airport_code;
        Airport airport = Airport(airport_code);
        if(g.findVertex(airport)){
            break;
        }else{
            cout << "Please insert a valid airport code" << endl;
        }
    }

    cout << endl;
    z = logic.FlightsOutOfAirportAndDifferentAirlines(airport_code);
    std::cout << "Number of flights: " << z.first << endl << "Number of different airlines: " << z.second << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
    back_menu();
}

void UI::number_flights() {
    char op;
    cout << "Would you like to consult the flights per: " << endl;
    cout << "A. City" << endl;
    cout << "B. Airlines" << endl << endl << endl << endl << endl << endl << endl << endl << endl;
    std::cout << "Insert the letter: ";
    validate_input(op,'A','B');
    switch(op){
        case 'A':{
            string city_name;
            while(true){
                city_name = "";
                cout << "What's the name of the city you would like to know the information?: ";
                cin >> city_name;
                if(this->cities.find(city_name) != this->cities.end()){
                    break;
                }
            }
            std::cout << "Number of flights of " << city_name << " : " <<logic.NumberOfFlightsPerCity(city_name) << endl;
            back_menu();
        }
        case 'B':{
            string airline_name;
            while(true){
                airline_name = "";
                cout << "What's the callsign of the airline you would like to know the information?: ";
                cin >> airline_name;
                if(this->airlines.find(airline_name) != this->airlines.end()){
                    break;
                }
            }
            std::cout << "Number of flights of " << airline_name << " airline : " << logic.NumberOfFlightsPerAirline(airline_name) << endl;
            back_menu();
        }
    }
}

void UI::number_countries() {
    char op;
    cout << "Would you like to consult the number of different countries reachable from: " << endl;
    cout << "A. City" << endl;
    cout << "B. Airport" << endl << endl << endl << endl << endl << endl << endl << endl << endl;
    std::cout << "Insert the letter: ";
    validate_input(op,'A','B');
    switch(op){
        case 'A':{
            string city_name;
            while(true){
                city_name = "";
                cout << "What's the name of the city you would like to know the information?: ";
                cin >> city_name;
                if(this->cities.find(city_name) != this->cities.end()){
                    break;
                }
            }
            std::cout << "Number of flights of " << city_name << " : " <<logic.NumberOfCountriesThatCityFliesTo(city_name) << endl;
            back_menu();
        }
        case 'B':{
            string airport_code;
            while(true){
                airport_code = "";
                cout << "What's the code of the airport you would like to know the information?: ";
                cin >> airport_code;
                if(this->airport_codes.find(airport_code) != this->airlines.end()){
                    break;
                }
            }
            std::cout << "Number of flights of " << airport_code << " airport : " << logic.NumberOfCountries(airport_code) << endl;
            back_menu();
        }
    }
}

void UI::number_reachable_destinations() {
    string airport_code;
    while(true){
        airport_code = "";
        cout << "What's the code of the airport you would like to know the information?: ";
        cin >> airport_code;
        if(this->airport_codes.find(airport_code) != this->airlines.end()){
            break;
        }
    }
    vector<Airport> tempVector = logic.nodesAtDistanceBFS(airport_code, diameter);

    vector<int> tempValues = logic.analyzeReachableAirports(tempVector);

    cout << "Number of distinct airports: " << tempValues[0] << endl;
    cout << "Number of distinct countries: " << tempValues[1] << endl;
    cout << "Number of distinct cities: " << tempValues[2] << endl;
    back_menu();

}

void UI::number_reachable_destinations_k() {
    string airport_code;
    int k;
    while(true){
        airport_code = "";
        cout << "What's the code of the airport you would like to know the information?: ";
        cin >> airport_code;
        if(this->airport_codes.find(airport_code) != this->airlines.end()){
            break;
        }
    }
    while(true){
        k = INT_MIN;
        cout << "What's the max number of lay-overs?: ";
        cin >> k;
        if(k >= 0 && k <= diameter){
            break;
        }
    }
    vector<Airport> tempVector = logic.nodesAtDistanceBFS(airport_code, k);

    vector<int> tempValues = logic.analyzeReachableAirports(tempVector);

    cout << "The " << airport_code << " airport within " << k << " lay-over(s) can reach:" << endl;
    cout << "Number of distinct airports: " << tempValues[0] << endl;
    cout << "Number of distinct countries: " << tempValues[1] << endl;
    cout << "Number of distinct cities: " << tempValues[2] << endl;
    back_menu();
}

void UI::longest_trip(){
    cout << "The longest distance is: " << diameter << endl << "Here are the longest flights:" << endl;
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
    back_menu();
}

void UI::greatest_traffic(){
    int k;
    while(true){
        k = INT_MIN;
        cout << "What's the number of top airports you want to get information about?: ";
        cin >> k;
        if(k >= 0 && k <= airport_codes.size()){
            break;
        }
    }
    logic.GreatestKIndeegrees(k);
    back_menu();
}

void UI::essential_airports() {
    unordered_set<Airport> result = logic.findArticulationPoints();
    cout << "There are a total of " << result.size() << " essential airports" << endl;
    back_menu();
}
