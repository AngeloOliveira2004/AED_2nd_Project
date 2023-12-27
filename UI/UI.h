#ifndef PROJETO_2_TEMP_H
#define PROJETO_2_TEMP_H


#include "../Logic/Airport.h"
#include "../Logic/Graph.h"
#include <iostream>
#include "../Logic/LoadingFunctions.h"
#include "../Logic/Logic.h"

class UI {
public:
    UI();

    void menu_start();

    static void clear_screen();

    void loading_stuff(UI &ui);

    bool validate_input(char &op, const char lower_bound, const char upper_bound);

    void menu_options();

private:
    Graph<Airport> g;
    Logic logic = Logic(g);

    void global_numbers();

    void number_out();

    void number_flights();
};


#endif //PROJETO_2_TEMP_H