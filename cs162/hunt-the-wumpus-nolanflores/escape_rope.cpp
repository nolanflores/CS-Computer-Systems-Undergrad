#include "escape_rope.hpp"

void Escape_Rope::print_char() const{
    printw("R");
}

void Escape_Rope::print_precept() const{}

bool Escape_Rope::encounter(Gamestate& gs){
    if(gs.have_gold)
        gs.win = true;
    return false;
}