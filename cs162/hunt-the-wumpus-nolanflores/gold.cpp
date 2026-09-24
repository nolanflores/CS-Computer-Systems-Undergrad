#include "gold.hpp"

void Gold::print_char() const{
    printw("G");
}

void Gold::print_precept() const{
    printw("You see something shimmer nearby.\n");
}

bool Gold::encounter(Gamestate& gs){
    gs.have_gold = true;
    return true;
}