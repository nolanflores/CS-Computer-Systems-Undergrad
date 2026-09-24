#include "stalactites.hpp"
#include <cstdlib>

void Stalactites::print_char() const{
    printw("S");
}

void Stalactites::print_precept() const{
    printw("You hear water dripping.\n");
}

bool Stalactites::encounter(Gamestate& gs){
    bool fall = std::rand() % 2;
    if(fall){
        if(gs.armor > 0){
            gs.armor--;
        }else{
            gs.lives--;
            gs.x = gs.rope_x;
            gs.y = gs.rope_y;
            gs.z = 0;
        }
    }
    return false;
}