#include "armor.hpp"

void Armor::print_char() const{
    printw("O");
}

void Armor::print_precept() const{
    printw("You feel the power.\n");
}

bool Armor::encounter(Gamestate& gs){
    gs.armor = 2;
    return true;
}