#include <thread>
#include <chrono>
#include "UI.h"

UI::UI() {}


/**
 * @brief Display a loading message and initialize the application data.
 *
 * This function displays a loading message narrating a story about a tree and a man, while
 * it loads flight data, initializes the application's logic, and sets up additional data required for the program.
 * The user is prompted to press 'A' to start the program after the loading is complete.
 * @param ui The user interface instance.
 *
 */
void UI::loading_stuff(UI &ui) {
    std::cout << "                                                                                                    ###Loading###" << endl << endl << endl << endl;
    std::cout << "Once upon a time, there lived a huge apple tree. There was a little boy who loved to come and play around the tree every day. He used to climb to the treetop, eat the apples, and take naps under its shade. He loved the tree and the tree also loved to play with him. As time went by, the little boy grew up and he would no longer play around the tree every day.\n"
                 "One fine day, the boy returned to the tree; he was looking sad. The tree asked the boy to come and play with it.\n"
                 "The boy replied that he was no longer a kid and he did not like to play around trees any more. He also mentioned that he wished to buy toys, for which he needed money.\n"
                 "The tree apologised and said, “I am sorry…but I do not have any money. However, you can pick out all my apples and sell them so that you can earn some money”.\n"
                 "The boy was so excited that he quickly grabbed all the apples hanging from the tree and left merrily. The boy never returned after he got what he needed, the apples.\n"
                 "The Little Boy Plucking Apples From the Tree\n"
                 "The tree felt lonely and sad.\n"
                 "One day, the boy, who had now turned into a man, returned, and the tree was excited again.\n"
                 "The tree asked the boy to play with it as usual.\n"
                 "“I haven’t got any time to play. I need to work to take care of my family. We are in need of a house to shelter us. Can you please help me?”, asked the boy.\n"
                 "The tree was distressed and replied, “Sorry…but I do not have any house to give to you. However, you can chop off my branches and take them with you. They will help you build your house”.\n"
                 "So, the man hastily cut all the branches off the tree and left satisfied. The tree was glad to see him happy, but, as usual, the man did not care to come back since then. The tree was once again lonely and sorrowful.\n"
                 "It was a hot summer day; to the tree’s delight, the man had returned! \n"
                 "“Come and play with me!”, the tree exclaimed in a joyful tone.\n"
                 "The man replied deeply, “I am getting old. I wish I could go sailing and spend some leisure time all by myself. Do you have a boat I can use?”.\n"
                 "“You can use my trunk to build your boat and sail far away, and you’ll be happy”, said the tree. \n"
                 "Like his usual routine, the man once again cut the tree trunk and built a boat out of it. He went sailing. And guess what? He didn’t show up for a very long time.\n"
                 "Finally, the man came back to the tree after many years. \n"
                 "“Sorry, my boy. But I have nothing that I can give you anymore. There are no more apples left for you”, the tree said.\n"
                 "“That won’t be a problem, I do not have any teeth left to bite on them anyway”, the man replied.\n"
                 "“No more trunk for you to climb on”, said the tree. \n"
                 "The man smiled and replied, “I am too old for that too”.\n"
                 "The tree said while shedding tears that it really could not give him anything except for its dying roots.\n"
                 "“I do not need much now, just a place where I can rest. I am weary after these long years”, the man replied with a sigh.\n"
                 "“Good then! Old tree roots can serve as excellent resting places. Come, sit down with me and relax”.\n"
                 "The man sat down comfortably. This made the tree really glad and it smiled with tears of joy.\n";
    LoadingFunctions::LoadFlights(g);
    this->logic = Logic(g);
    logic.MapAirports();
    ui.load_sets();
    for(auto airline : LoadingFunctions::getAirlines()){
        airlines.insert(airline.getCode());
    }
    diameter = g.calculateDiameter();
    cout << "Load Finished" << endl;
    cout << "Press A to start the program: ";
    char op;
    validate_input(op,'A','A');
}

/**
 * @brief This function iterates over the vertices in the graph and populates sets of cities, airport codes,
 * and countries based on the information stored in each airport. The unordered sets are member variables of the UI class,
 * allowing efficient retrieval of unique values for further use in the user interface.
 */
void UI::load_sets(){
    for(auto airport: g.getVertexSet()){
        this->cities.insert(airport->getInfo().getCity());
        this->airport_codes.insert(airport->getInfo().getCode());
        this->countries.insert(airport->getInfo().getCountry());
    }
}

/**
 * @brief Clears the console screen by printing empty lines.
 */
void UI::clear_screen() {
    int i = 0;
    while(i != 100) {
        cout << endl;
        i++;
    }
}

/**
 * @brief Validate and read a character input within a specified range.
 *
 * This function prompts the user to input a character and validates that it is a single character.
 * It then converts the character to uppercase and ensures it falls within the specified range [lower_bound, upper_bound].
 * If the input is not valid, the user is prompted to try again until a valid input is provided.
 *
 * @param op Reference to the character variable where the validated input will be stored.
 * @param lower_bound The lower bound of the valid range (inclusive).
 * @param upper_bound The upper bound of the valid range (inclusive).
 * @return Returns true after successfully validating and storing the input.
 */
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

/**
 * @brief Display the start menu for the Air Travel Flight Management System.
 *
 */
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
            main_menu();
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

/**
 * @brief Display the main menu of the Air Travel Flight Management System.
 *
 */
void UI::main_menu(){
    char op;
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
            break;
        case 'C':
            trip_planner();
            break;
        case 'D':
            cout << "Thanks for using our management system app!" << endl << "\n"
                 << "Made by: " << endl
                 << "Ângelo Oliveira || 202207798" << endl
                 << "José Costa      || 202207871" << endl
                 << "Bernardo Sousa  || 202206009" << endl;
            this_thread::sleep_for(chrono::seconds(2)); // Espera 2 segundos antes de fechar o terminal
            exit(0);
        default:
            std::cerr << "Error";
    }
}

/**
 * @brief Initiates the trip planning process based on user preferences.
 *
 * This function prompts the user to choose the starting point of the trip (origin airport, city, country, or coordinates),
 * and then requests additional information for the destination. It takes into account various filters provided by the user,
 * such as airline preferences or restrictions. The function then invokes the appropriate logic functions to plan the trip,
 * displaying the relevant information to the user.
 */
void UI::trip_planner(){
    char op;
    cout << "How would you like to chose your starting point?" << endl
         << "A. Origin Airport (You may use the name or the code of the airport)" << endl
         << "B: Origin City (We'll pick all airports in the city)" << endl
         << "C. Origin Country (We'll pick all airports in the country)" << endl
         << "D. Origin Coordinates (We'll pick the closest airport/s to the given coordinates)" << endl
         << "Insert your option:";
    validate_input(op, 'A', 'D');
    string initial_Airport;
    string destination;
    unordered_set<string> filters;
    int choice = 0;
    bool Avoid_Or_Only ;
    bool Yes_or_No;

    std::string city;
    std::string country;
    std::string second_city;
    std::string second_country;

    auto commaPos = country.begin();
    switch ((op)) {
        case 'A':
            cin.ignore();
            cout << "Insert the code of the airport where you would like to depart from:" << endl;
            std::getline(std::cin , initial_Airport);

            initial_Airport = find_apCode(initial_Airport);
            get_destination(destination , choice , filters);
            switch (choice) {
                case 1:
                    filters = get_Filters(Avoid_Or_Only , Yes_or_No);
                    if(Yes_or_No)
                    {
                        if(Avoid_Or_Only)
                        {
                            printList(logic.AirportToAirportAirlineOnlyFilters(Airport(initial_Airport) , Airport(destination) , filters));
                        }else
                        {
                            printList(logic.AirportToAirportAirlineAvoidFilters(Airport(initial_Airport) , Airport(destination) , filters));
                        }
                    }
                    else
                    {
                        printList(logic.AirportToAirport(Airport(initial_Airport) , Airport(destination)));
                    }
                    back_menu();
                    break;
                case 2:
                    filters = get_Filters(Avoid_Or_Only , Yes_or_No);

                    commaPos = std::find(destination.begin(), destination.end(), ',');
                    if (commaPos != destination.end()) {
                        // Extract the first part (before the comma) and remove spaces
                        city = std::string(destination.begin(), commaPos);

                        // Extract the second part (after the comma) and remove spaces
                        country = std::string(std::find_if_not(commaPos + 1, destination.end(), ::isspace), destination.end());
                    } else {
                        std::cout << "Input not valid";
                        back_menu();
                    }

                    if(Yes_or_No)
                    {
                        if(Avoid_Or_Only)
                        {
                            printList(logic.AirportToCityAirlineOnlyFilter(Airport(initial_Airport) , city , country , filters));
                        }else
                        {
                            printList(logic.AirportToCityAirlineAvoidFilter(Airport(initial_Airport) , city , country , filters));
                        }
                    }
                    else
                    {
                        printList(logic.AirportToCity(Airport(initial_Airport) , city , country));
                    }
                    back_menu();
                    break;
                case 3:
                    filters = get_Filters(Avoid_Or_Only , Yes_or_No);
                    if(Yes_or_No)
                    {
                        if(Avoid_Or_Only)
                        {
                            printList(logic.AirportToCountryAirlineOnlyFilter(Airport(initial_Airport) , destination , filters));
                        }else
                        {
                            printList(logic.AirportToCountryAirlineAvoidFilter(Airport(initial_Airport) , destination , filters));
                        }
                    }
                    else
                    {
                        printList(logic.AirportToCountry(initial_Airport , destination));
                    }
                    back_menu();
                    break;
                case 4:
                    filters = get_Filters(Avoid_Or_Only , Yes_or_No);
                    double dest_lat, dest_lon;
                    string str_lat, str_lon;
                    commaPos = std::find(destination.begin(), destination.end(), ',');
                    if (commaPos != destination.end()) {
                        str_lat = std::string(destination.begin(), commaPos);
                        str_lon = std::string(std::find_if_not(commaPos + 1, destination.end(), ::isspace), destination.end());
                    }
                    dest_lat = stod(str_lat);
                    dest_lon = stod(str_lon);
                    if(Yes_or_No){
                        if(Avoid_Or_Only){
                            printList(logic.AirportToLocationAirlineOnlyFilters(Airport(initial_Airport), dest_lat, dest_lon, filters));
                        }
                        else{
                            printList(logic.AirportToLocationAirlineAvoidFilters(Airport(initial_Airport), dest_lat, dest_lon, filters));
                        }
                    }
                    else{
                        printList(logic.AirportToLocation(Airport(initial_Airport), dest_lat, dest_lon));
                    }
                    back_menu();
                    break;
            }
            break;
        case 'B':
            std::cin.ignore(); // Clear the input stream
            cout << "Insert the city of the airport where you would like to depart from (Introduce the city in format [City,Country]):" << endl;
            std::getline(std::cin, initial_Airport);
            get_destination(destination , choice , filters);

            commaPos = std::find(initial_Airport.begin(), initial_Airport.end(), ',');
            if (commaPos != initial_Airport.end()) {
                // Extract the first part (before the comma) and remove spaces
                city = std::string(initial_Airport.begin(), commaPos);

                // Extract the second part (after the comma) and remove spaces
                country = std::string(std::find_if_not(commaPos + 1, initial_Airport.end(), ::isspace), initial_Airport.end());
            } else {
                std::cout << "Input not valid";
                back_menu();
            }

            switch (choice) {
                case 1:
                    filters = get_Filters(Avoid_Or_Only , Yes_or_No);
                    if(Yes_or_No)
                    {
                        if(Avoid_Or_Only)
                        {
                            printList(logic.CityToAirport(Airport(destination) , city , country , 3 , filters));
                        }else
                        {
                            printList(logic.CityToAirport(Airport(destination) , city , country , 2 , filters));
                        }
                    }
                    else
                    {
                        printList(logic.CityToAirport(Airport(destination) , city , country , 1 , filters));
                    }
                    back_menu();
                    break;
                case 2:
                    filters = get_Filters(Avoid_Or_Only , Yes_or_No);

                    commaPos = std::find(destination.begin(), destination.end(), ',');
                    if (commaPos != destination.end()) {
                        // Extract the first part (before the comma) and remove spaces
                        second_city = std::string(destination.begin(), commaPos);

                        // Extract the second part (after the comma) and remove spaces
                        second_country = std::string(std::find_if_not(commaPos + 1, destination.end(), ::isspace), destination.end());
                    } else {
                        std::cout << "Input not valid";
                        back_menu();
                    }

                    if(Yes_or_No)
                    {
                        if(Avoid_Or_Only)
                        {
                            printList(logic.CityToCity(city , country , second_city , second_country , 3 , filters));
                        }else
                        {
                            printList(logic.CityToCity(city , country , second_city , second_country , 2 , filters));
                        }
                    }
                    else
                    {
                        printList(logic.CityToCity(city , country , second_city , second_country , 1 , filters));
                    }
                    back_menu();
                    break;
                case 3:
                    filters = get_Filters(Avoid_Or_Only , Yes_or_No);
                    if(Yes_or_No)
                    {
                        if(Avoid_Or_Only)
                        {
                            printList(logic.CityToCountry(city , country , destination , 3 , filters));
                        }else
                        {
                            printList(logic.CityToCountry(city , country , destination , 2 , filters));
                        }
                    }
                    else
                    {
                        printList(logic.CityToCountry(city , country , destination , 1 , filters));
                    }
                    back_menu();
                    break;
                case 4:
                    double dest_lat, dest_lon;
                    string str_lat, str_lon;
                    commaPos = std::find(destination.begin(), destination.end(), ',');
                    if (commaPos != destination.end()) {
                        str_lat = std::string(destination.begin(), commaPos);
                        str_lon = std::string(std::find_if_not(commaPos + 1, destination.end(), ::isspace), destination.end());
                    }
                    dest_lat = stod(str_lat);
                    dest_lon = stod(str_lon);
                    vector<Airport> destinations = logic.FindClosestAirportsToLocation(dest_lat, dest_lon);
                    //CIty to location
                    filters = get_Filters(Avoid_Or_Only , Yes_or_No);
                    if(Yes_or_No){
                        if(Avoid_Or_Only){
                            for(auto dest: destinations){
                                printList(logic.CityToAirport(dest, city , country , 3, filters));
                            }
                        }
                        else{
                            for(auto dest: destinations){
                                printList(logic.CityToAirport(dest , city , country , 2 , filters));
                            }
                        }
                    }
                    else{
                        for(auto dest: destinations){
                            printList(logic.CityToAirport(dest , city , country , 1 , filters));
                        }
                    }
                    back_menu();
                    break;
            }
            break;
        case 'C':
            cout << "Insert the country where you would like to depart from:" << endl;
            cin >> country;
            get_destination(destination , choice , filters);

            switch (choice) {

                case 1:
                    filters = get_Filters(Avoid_Or_Only , Yes_or_No);
                    if(Yes_or_No)
                    {
                        if(Avoid_Or_Only)
                        {
                            printList(logic.CountryToAirport(Airport(destination) , country , 3 , filters));
                        }else
                        {
                            printList(logic.CountryToAirport(Airport(destination) , country , 2 , filters));
                        }
                    }
                    else
                    {
                        printList(logic.CountryToAirport(Airport(destination) , country , 1 , filters));
                    }
                    back_menu();
                    break;
                case 2:

                    filters = get_Filters(Avoid_Or_Only , Yes_or_No);

                    commaPos = std::find(destination.begin(), destination.end(), ',');
                    if (commaPos != destination.end()) {
                        // Extract the first part (before the comma) and remove spaces
                        second_city = std::string(destination.begin(), commaPos);

                        // Extract the second part (after the comma) and remove spaces
                        second_country = std::string(std::find_if_not(commaPos + 1, destination.end(), ::isspace), destination.end());
                    } else {
                        std::cout << "Input not valid";
                        back_menu();
                    }

                    if(Yes_or_No)
                    {
                        if(Avoid_Or_Only)
                        {
                            printList(logic.CountryToCity(country , second_city , second_country , 3 , filters));
                        }else
                        {
                            printList(logic.CountryToCity(country , second_city , second_country , 2 , filters));
                        }
                    }
                    else
                    {
                        printList(logic.CountryToCity(country , second_city , second_country , 1 , filters));
                    }
                    back_menu();
                    break;
                case 3:

                    filters = get_Filters(Avoid_Or_Only , Yes_or_No);
                    if(Yes_or_No)
                    {
                        if(Avoid_Or_Only)
                        {
                            printList(logic.CountryToCountry(country , destination , 3 , filters));
                        }else
                        {
                            printList(logic.CountryToCountry(country , destination , 2 , filters));
                        }
                    }
                    else
                    {
                        printList(logic.CountryToCountry(country , destination , 1 , filters));
                    }
                    back_menu();
                    break;

                    break;
                case 4:
                    filters = get_Filters(Avoid_Or_Only, Yes_or_No);
                    double dest_lat, dest_lon;
                    string str_lat, str_lon;
                    commaPos = std::find(destination.begin(), destination.end(), ',');
                    if (commaPos != destination.end()) {
                        str_lat = std::string(destination.begin(), commaPos);
                        str_lon = std::string(std::find_if_not(commaPos + 1, destination.end(), ::isspace), destination.end());
                    }
                    dest_lat = stod(str_lat);
                    dest_lon = stod(str_lon);
                    vector<Airport> destinations = logic.FindClosestAirportsToLocation(dest_lat, dest_lon);
                    if(Yes_or_No){
                        if(Avoid_Or_Only){
                            for(auto dest: destinations){
                                printList(logic.CountryToAirport(dest,  country, 3, filters));
                            }
                        }
                        else{
                            for(auto dest: destinations){
                                printList(logic.CountryToAirport(dest,  country, 2, filters));
                            }
                        }
                    }
                    else{
                        for(auto dest: destinations){
                            printList(logic.CountryToAirport(dest,  country, 1, filters));
                        }
                    }
                    back_menu();
                    break;

            }
            break;
        case 'D':
            cout << "Insert the coordinates where you would like to depart from:" << endl;
            double latitude, longitude;
            string str_lat, str_lon;
            string latlong;
            cin >> latlong;
            commaPos = std::find(latlong.begin(), latlong.end(), ',');
            if (commaPos != latlong.end()) {
                str_lat = std::string(latlong.begin(), commaPos);
                str_lon = std::string(std::find_if_not(commaPos + 1, latlong.end(), ::isspace), latlong.end());
            }
            latitude = stod(str_lat);
            longitude = stod(str_lon);
            get_destination(destination , choice , filters);


            switch(choice){
                case 1:
                    filters = get_Filters(Avoid_Or_Only , Yes_or_No);
                    if(Yes_or_No)
                    {
                        if(Avoid_Or_Only)
                        {
                            printList(logic.LocationToAirportAirlineOnlyFilters(latitude, longitude, Airport(destination), filters));

                        }else{
                            printList(logic.LocationToAirportAirlineAvoidFilters(latitude, longitude, Airport(destination), filters));
                        }
                    }
                    else
                    {

                        printList(logic.LocationToAirport(latitude, longitude, destination));
                    }
                    back_menu();
                    break;
                case 2:
                    filters = get_Filters(Avoid_Or_Only, Yes_or_No);
                    commaPos = std::find(destination.begin(), destination.end(), ',');
                    if (commaPos != destination.end()) {
                        // Extract the first part (before the comma) and remove spaces
                        city = std::string(destination.begin(), commaPos);

                        // Extract the second part (after the comma) and remove spaces
                        country = std::string(std::find_if_not(commaPos + 1, destination.end(), ::isspace), destination.end());
                    } else {
                        std::cout << "Input not valid";
                        back_menu();
                    }

                    if(Yes_or_No){
                        if(Avoid_Or_Only){
                            printList(logic.LocationToCityAirlineOnlyFilters(latitude, longitude, city, country, filters));

                        }
                        else{
                            printList(logic.LocationToCityAirlineAvoidFilters(latitude, longitude, city, country, filters));
                        }
                    }
                    else{
                        printList(logic.LocationToCity(latitude, longitude, city, country));
                    }
                    back_menu();
                    break;
                case 3:
                    filters = get_Filters(Avoid_Or_Only, Yes_or_No);
                    if(Yes_or_No){
                        if(Avoid_Or_Only){
                            printList(logic.LocationToCountryAirlineOnlyFilter(latitude, longitude, country, filters));
                        }
                        else{
                            printList(logic.LocationToCountryAirlineAvoidFilter(latitude, longitude, country, filters));
                        }
                    }
                    else{
                        printList(logic.LocationToCountry(latitude, longitude, country));
                    }
                    back_menu();
                    break;
                case 4:
                    filters = get_Filters(Avoid_Or_Only, Yes_or_No);
                    double dest_lat, dest_lon;
                    string str_lat, str_lon;
                    commaPos = std::find(destination.begin(), destination.end(), ',');
                    if (commaPos != destination.end()) {
                        str_lat = std::string(destination.begin(), commaPos);
                        str_lon = std::string(std::find_if_not(commaPos + 1, destination.end(), ::isspace), destination.end());
                    }
                    dest_lat = stod(str_lat);
                    dest_lon = stod(str_lon);
                    vector<Airport> destinations = logic.FindClosestAirportsToLocation(dest_lat, dest_lon);
                    if(Yes_or_No){
                        if(Avoid_Or_Only){
                            for (auto dest: destinations){
                                printList(logic.LocationToAirportAirlineOnlyFilters(latitude, longitude, dest, filters));
                            }
                        }
                        else{

                            for (auto dest: destinations){
                                printList(logic.LocationToAirportAirlineAvoidFilters(latitude, longitude, dest, filters));
                            }

                        }
                    }
                    else{
                        for (auto dest: destinations){
                            printList(logic.LocationToAirport(latitude, longitude, dest));
                        }

                    }
            }
    }
}

/**
 * @brief Obtains user input for the destination point and sets choice variable accordingly.
 *
 *
 * @param input String variable where the info about the destination will be stored.
 * @param choice Integer that indicates the chosen destination type algorithm (1: Airport, 2: City, 3: Country, 4: Coordinates).
 * @param filters An unordered set of strings where filters may be stored.
 */
void UI::get_destination(std::string& input , int& choice , unordered_set<std::string>& filters)
{
    char op;
    cout << "Which of these would you like to choose for destination point?" << endl
         << "A. Destination Airport (You may use the name or the code of the airport)" << endl
         << "B: Destination City (We'll pick all airports in the city)" << endl
         << "C. Destination Country (We'll pick all airports in the country)" << endl
         << "D. Destination Coordinates (We'll pick the closest airport/s to the given coordinates)" << endl
         << "Insert your option:";
    validate_input(op, 'A', 'D');
    switch ((op)) {
        case 'A':
            cin.ignore();
            cout << "Insert the code of the airport where you would like to go to:" << endl;
            std::getline(std::cin , input);
            input = find_apCode(input);
            choice = 1;
            break;
        case 'B':
            std::cin.ignore(); // Clear the input stream
            cout << "Insert the city where you would like to go to(Introduce it in the format [City,Country] :" << endl;
            std::getline(std::cin, input);
            choice = 2;
            break;
        case 'C':
            std::cin.ignore();
            cout << "Insert the country of the airport where you would like to go to:" << endl;
            std::getline(std::cin, input);
            choice = 3;
            break;
        case 'D':
            std::cin.ignore();
            cout << "Insert the coordinates of the closest airport where you would like to go to:" << endl;
            std::getline(std::cin, input);
            choice = 4;
            break;
    }
}

/**
 * @brief Collects user input for airline filters and returns the filters value accordingly.
 *
 *
 * @param Avoid_Or_Only Boolean variable indicating whether the user wants to ONLY travel by the specified airlines (true) or to AVOID them (false).
 * @param Yes_or_No A reference to a boolean variable indicating whether the user wants to use airline filters (true) or not (false).
 *
 * @return An unordered set of strings containing the airline codes specified by the user as filters.
 */
unordered_set<string> UI::get_Filters(bool& Avoid_Or_Only , bool& Yes_or_No)
{
    unordered_set<std::string> filters;
    string input;
    char op;
    cout << "Do you want to use airline filters?"<< endl;
    cout << "A - Yes" << endl
         << "B - No" << endl;
    validate_input(op , 'A' , 'B');

    Yes_or_No = op == 'A';
    string airline;
    if(Yes_or_No)
    {
        cout << "Introduce all airlines codes that you wish to include. Press 'd' when you're done" << endl;
        while (airline[0] != 'd')
        {
            std::cin >> airline;
            if(valid_airline(airline))
            {
                filters.insert(airline);
            }else
            {
                cout << "Please introduce a proper airline code" << endl;
            }
        }

        cout << "Do you wish to travel ONLY by these Airlines or to AVOID them?" << endl;
        cout << "A - ONLY" << endl
             << "B - AVOID" << endl;
        validate_input(op , 'A' , 'B');

        if(op == 'A'){
            Avoid_Or_Only = true;
        }else
        {
            Avoid_Or_Only = false;
        }
    }

    return filters;
}
/**
 * @brief Checks whether the airline code is valid or not.
 *
 * This function checks if the given airline code is valid. An airline code is considered valid if it meets the following criteria:
 * - It is not 'd' (used to indicate the end of input during filtering).
 * - It has a length of 3 characters all being uppercase letters, since all the airline codes consists of 3 uppercase letters.
 *
 * @param airline A string with the airline code to be validated.
 *
 * @return True if the airline code is valid; otherwise, false.
 */
bool UI::valid_airline(std::string& airline)
{
    if(airline[0] == 'd' && airline.size() == 1)
        return true;

    if (airline.length() != 3) {
        return false;
    }

    return std::all_of(airline.begin(), airline.end(), [](char c) {
        return std::isupper(c);
    });
}

/**
 * @brief Finds the airport code based on its name.
 *
 * This function searches for the airport code corresponding to the given airport name, inside an unordered map.
 * If the provided string is already a three-letter airport code, it is returned as is, since it means that it's already an airport code.
 * Otherwise, the function looks up the name in the map.
 *
 * @param name A string reference representing the airport name or code to be looked up.
 *
 * @return The airport code corresponding to the given string.
 */
std::string UI::find_apCode(std::string& name){
    if(name.length() == 3){
        return name;
    }
    else{
        for(auto air: logic.getNamesToCodes()){
            if(air.first == name){
                return air.second;
            }
        }
    }
    return "";
}
/**
 * @brief Prints a normalized list of vectors representing trips.
 *
 * This function takes a list of vectors of airports representing trips, normalizes the list,
 * and then prints the trips. If the normalized list is empty, it prints a message indicating
 * that no trips are available. Each trip is printed by concatenating the airport codes with "->".
 *
 * @param a A list of vectors of airports representing trips.
 */
void UI::printList(list<vector<Airport>> a)
{
    list<vector<Airport>> normalised;
    normalised = NormaliseList(a);
    if(normalised.empty())
    {
        std::cout << "No trip available" << endl;
    }
    for(auto v : normalised){
        for(int i = 0 ; i < v.size()-1 ; i++){
            cout << v[i].getCode() << "->";
        }
        cout << v[v.size()-1].getCode() << endl;
    }
}

/**
 * @brief Initiates the flight consultation menu, receiving an input that leads to the chosen function call.
 *
 */
void UI::flight_consultation() {
    char op;
    cout << "How would you like to search for your flight? " << endl
         << "A. Consult number of flights out of an airport and from how many different airlines;" << endl
         << "B. Consult the number of different destinations that an airport flies to; " << endl
         << "Insert your choice: ";

    validate_input(op, 'A', 'B');
    switch(op){
        case 'A':
            number_out();
            break;
        case 'B':
            different_destinations();
            break;
    }
    main_menu();
}
/**
 * @brief Initiates the statistics menu.
 */
void UI::statistics_menu(){
    char op;
    cout << "What statistics would you like to see?" << endl
         << "A. Global Statistics" << endl
         << "B. Airport Statistics" << endl
         << "C. Airline/City Statistics" << endl
         << "D. Country Statistics" << endl
         << "E. Consult longest possible flights" << endl
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
        case 'E':
            longest_trip();
            break;
    }
}

/**
 * @brief Initiates the airport statistics menu.
 *
 */
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

/**
 * @brief Navigates back to the main menu.
 *
 */
void UI::back_menu(){
    char op;
    std::cout << "Press A to go back to the menu: ";
    validate_input(op,'A','A');
    main_menu();
}

/**
 * @brief Displays global numbers of airports and flights.
 */
void UI::global_numbers() {
    cout << "Number of Airports: " << logic.GlobalNumberOfAirports() << endl;
    cout << "Number of Flights: " << logic.GlobalNumberOfFlights() << endl << endl << endl << endl << endl << endl << endl << endl << endl;
    back_menu();
}


/**
 * @brief Displays the number of flights and different airlines departing from a specified airport.
 */
void UI::number_out() {
    bool validate = false;
    std::pair<int, int> z;
    string airport_code;
    cout << "What's the code of the airport you would like to know the information?(You may use airport name as well): ";
    while(!validate){
        airport_code = "";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::getline(cin , airport_code);
        airport_code = find_apCode(airport_code);
        Airport airport = Airport(airport_code);
        if(g.findVertex(airport)){
            break;
        }else{
            cout << "Please insert a valid airport code" << endl;
        }
    }

    cout << endl;
    z = logic.FlightsOutOfAirportAndDifferentAirlines(airport_code);
    std::cout << "Number of flights: " << z.first << endl << "Number of different airlines: " << z.second << endl << endl << endl << endl << endl << endl << endl << endl << endl;
    back_menu();
}

void UI::different_destinations()
{
    string airport;
    std::cin.ignore();
    std::cout << "Introduce the name of the airport that you wish to check the destinations (You may use the name or the code of the airport): "<<endl;
    std::getline(std::cin , airport);
    airport = find_apCode(airport);

    std::cout << "Destinations: " << logic.NumberOfDestinationsForAirport(airport) << endl;
}

/**
 * @brief Displays the number of flights, either per city or per airline, as chosen by the user.
 */
void UI::number_flights() {
    char op;
    cout << "Would you like to consult the flights per: " << endl;
    cout << "A. City" << endl;
    cout << "B. Airlines" << endl << endl << endl << endl << endl << endl << endl << endl;
    std::cout << "Insert the letter: ";
    validate_input(op,'A','B');
    switch(op){
        case 'A':{
            string city_name;
            string country;
            string city;
            auto commaPos = country.begin();
            while(true){
                city_name = "";
                cin.ignore();
                cout << "What's the name of the city you would like to know the information?(Introduce the city in format [City,Country]) : ";
                std::getline(std::cin, city_name);

                commaPos = std::find(city_name.begin(), city_name.end(), ',');
                if (commaPos != city_name.end()) {
                    // Extract the first part (before the comma) and remove spaces
                    city = std::string(city_name.begin(), commaPos);
                    // Extract the second part (after the comma) and remove spaces
                    country = std::string(std::find_if_not(commaPos + 1, city_name.end(), ::isspace), city_name.end());
                } else {
                    std::cout << "Input not valid";
                    back_menu();
                }
                break;
            }
            std::cout << "Number of flights out of " << city_name << " : " <<logic.NumberOfFlightsPerCity(city , country) << endl;
            back_menu();
        }
        case 'B':{
            string airline_name;
            while(true){
                airline_name = "";
                cout << "What's the code of the airline you would like to know the information?: ";
                cin >> airline_name;
                if(this->airlines.find(airline_name) != this->airlines.end()){
                    break;
                }
            }
            std::cout << "Number of flights with airline " << airline_name << " : " << logic.NumberOfFlightsPerAirline(airline_name) << endl;
            back_menu();
        }
    }
}

/**
 * @brief Displays the number of different countries reachable from a city or airport, as chosen by the user.
 */
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
            string country;
            string city;
            auto commaPos = country.begin();
            while(true){
                city_name = "";
                std::cin.ignore();
                cout << "What's the name of the city you would like to know the information?(Introduce the city in format [City,Country]): ";
                std::getline(std::cin, city_name);

                commaPos = std::find(city_name.begin(), city_name.end(), ',');
                if (commaPos != city_name.end()) {
                    // Extract the first part (before the comma) and remove spaces
                    city = std::string(city_name.begin(), commaPos);
                    // Extract the second part (after the comma) and remove spaces
                    country = std::string(std::find_if_not(commaPos + 1, city_name.end(), ::isspace), city_name.end());
                } else {
                    std::cout << "Input not valid";
                    back_menu();
                }
                break;
            }
            std::cout << "Number of different countries that " << city_name << " flies to: " <<logic.NumberOfCountriesThatCityFliesTo(city , country) << endl;
            back_menu();
        }
        case 'B':{
            string airport_code;
            cout << "What's the code of the airport you would like to know the information?(You may use airport name as well): ";
            while(true){
                airport_code = "";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(cin , airport_code);
                airport_code = find_apCode(airport_code);
                Airport airport = Airport(airport_code);
                if(g.findVertex(airport)){
                    break;
                }else{
                    cout << "Please insert a valid airport code" << endl;
                }
            }
            std::cout << "Number of flights of " << airport_code << " airport : " << logic.NumberOfCountries(airport_code) << endl;
            back_menu();
        }
    }
}

/**
 * @brief Displays the number of distinct airports, countries, and cities reachable from a specified airport.
 */
void UI::number_reachable_destinations() {
    string airport_code;
    cout << "What's the code of the airport you would like to know the information?(You may use airport name as well): ";
    while(true){
        airport_code = "";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::getline(cin , airport_code);
        airport_code = find_apCode(airport_code);
        Airport airport = Airport(airport_code);
        if(g.findVertex(airport)){
            break;
        }else{
            cout << "Please insert a valid airport code" << endl;
        }
    }
    vector<Airport> tempVector = logic.nodesAtDistanceBFS(airport_code, diameter);

    vector<int> tempValues = logic.analyzeReachableAirports(tempVector);

    cout << "Number of distinct airports: " << tempValues[0] << endl;
    cout << "Number of distinct countries: " << tempValues[1] << endl;
    cout << "Number of distinct cities: " << tempValues[2] << endl;
    back_menu();

}

/**
 * @brief Displays the number of distinct airports, countries, and cities reachable from a specified airport within a maximum number of layovers.
 */
void UI::number_reachable_destinations_k() {
    string airport_code;
    int k;
    cout << "What's the code of the airport you would like to know the information?(You may use airport name as well): ";
    while(true){
        airport_code = "";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::getline(cin , airport_code);
        airport_code = find_apCode(airport_code);
        Airport airport = Airport(airport_code);
        if(g.findVertex(airport)){
            break;
        }else{
            cout << "Please insert a valid airport code " << endl;
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

/**
 * @brief Displays the longest trips available in the network.
 */
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

/**
 * @brief Displays information about the top airports with the greatest air traffic capacity.
 */
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

/**
 * @brief Displays information about essential airports in the network's circulation capability.
 */
void UI::essential_airports() {
    unordered_set<Airport> result = logic.findArticulationPoints();
    cout << "There are a total of " << result.size() << " essential airports" << endl;
    back_menu();
}


/**
 * @brief Normalizes a list of vectors by keeping only the vectors with the minimum size.
 * @param list1 The list of vectors to be normalized.
 * @details O(N) where n is the size of the input
 */
list<vector<Airport>> UI::NormaliseList(list<vector<Airport>> &list1) {
    int min_ = INT_MAX;

    for (const auto& it : list1) {
        if (it.size() < min_)
            min_ = it.size();
    }

    std::list<vector<Airport>> result;
    std::copy_if(list1.begin(),list1.end(),std::back_inserter(result),[min_](const auto& vec) { return vec.size() == min_;});
    return result;
}
