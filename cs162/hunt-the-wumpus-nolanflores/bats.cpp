#include "bats.hpp"

void Bats::print_char() const{
    printw("B");
}

void Bats::print_precept() const{
    printw("You hear wings flapping.\n");
}

bool Bats::encounter(Gamestate& gs){
    gs.is_confused = true;
    return false;
}