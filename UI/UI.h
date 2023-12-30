#ifndef PROJETO_2_TEMP_H
#define PROJETO_2_TEMP_H

#include "../Logic/Airport.h"
#include "../Logic/Graph.h"
#include <iostream>
#include "../Logic/LoadingFunctions.h"
#include "../Logic/Logic.h"
#include <climits>

class UI {
public:
    UI();

    void menu_start();

    static void clear_screen();

    void loading_stuff(UI &ui);

    bool validate_input(char &op, const char lower_bound, const char upper_bound);

    void main_menu();
    void statistics_menu();
    void airport_statistics();
    void flight_consultation();
    void trip_planner();
    void get_destination(std::string &input , int& choice , unordered_set<std::string>& filters);
    void printList(list<vector<Airport>> a);
    void menu_options();

    void global_numbers();

    void number_out();

    void number_flights();

    void load_sets();

    void back_menu();

    void number_countries();

    void number_reachable_destinations();

    void number_reachable_destinations_k();

    void longest_trip();

    void greatest_traffic();

    unordered_set<std::string> get_Filters(bool & Avoid_Or_Only , bool& Yes_or_No);
    bool valid_airline(std::string& airline);
    std::string find_apCode(std::string& name);
    list<vector<Airport>> NormaliseList(list<vector<Airport>>& list1);
private:
    Graph<Airport> g;
    Logic logic = Logic(g);
    unordered_set<string> cities;
    unordered_set<string> airport_codes;
    unordered_set<string> countries;
    unordered_set<string> airlines;
    int diameter;

    void essential_airports();
};

#endif //PROJETO_2_TEMP_H