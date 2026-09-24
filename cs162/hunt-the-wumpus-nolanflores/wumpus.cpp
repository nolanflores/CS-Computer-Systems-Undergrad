#include "wumpus.hpp"

void Wumpus::print_char() const{
    printw("W");
}

void Wumpus::print_precept() const{
    printw("You smell a terrible stench.\n");
}

bool Wumpus::encounter(Gamestate& gs){
    if(gs.armor > 0){
        gs.armor--;
    }else{
        gs.lives--;
        gs.x = gs.rope_x;
        gs.y = gs.rope_y;
        gs.z = 0;
    }
    return false;
}