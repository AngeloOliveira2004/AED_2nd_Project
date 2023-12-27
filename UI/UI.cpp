#include <thread>
#include <chrono>
#include "UI.h"

UI::UI() {}

void UI::loading_stuff(UI &ui) {
    LoadingFunctions::LoadFlights(g);
    this->logic = Logic(g);
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
        if (std::cin.fail() || tempValue.length() != 1 || !isdigit(op)) {
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

void UI::menu_options() {
    char op;
    clear_screen();
    cout << "What option would you like to choose?" << endl << '\n'
         << "A. Consult global number of airports and number of available flights" << endl
         << "B. Consult number of flights out of an airport and from how many different airlines;" << endl
         << "C. Consult number of flights per city/airline" << endl
         << "D. Consult number of different countries that a given airport/city flies to" << endl
         << "E. Consult number of destinations (airports, cities or countries) available for a given airport;" << endl
         << "F. Consult number of reachable destinations from a given airport in a maximum of X lay-overs" << endl
         << "G. Consult trip(s) with the greatest number of stops in between them" << endl
         << "H. Consult top-k airport with the greatest air traffic capacity, " << endl
         << "I. Consult essential airports to the network's circulation capability" << endl
         << "J. Consult best flight option(s) for a given source and destination locations"
         << "Insert the letter: ";
    validate_input(op,'A','B');
    switch(op){
        case 'A':
            break;
        case 'B':
            break;
        case 'C':
            break;
        case 'D':
            break;
        case 'E':
            break;
        case 'F':
            break;
        case 'G':
            break;
        case 'H':
            break;
        case 'I':
            break;
        case 'J':
            break;
    }
}