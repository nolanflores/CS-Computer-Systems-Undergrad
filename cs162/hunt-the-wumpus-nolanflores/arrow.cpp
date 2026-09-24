#include "arrow.hpp"

void Arrow::print_char() const{
    printw("A");
}

void Arrow::print_precept() const{
    printw("You see an arrow on the ground in an adjacent room.\n");
}

bool Arrow::encounter(Gamestate& gs){
    gs.arrows++;
    return true;
}