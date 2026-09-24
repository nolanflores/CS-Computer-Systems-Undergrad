#include "ladder.hpp"

Ladder::Ladder(int z_offset){
    this->z_offset = z_offset;
}

void Ladder::print_char() const{
    if(this->z_offset < 0)
        printw("^");
    else if(this->z_offset > 0)
        printw("v");
    else
        printw("L");
}

void Ladder::print_precept() const{
    if(this->z_offset < 0)
        printw("You see a ladder that goes up.\n");
    else if(this->z_offset > 0)
        printw("You see a ladder that goes down.\n");
}

bool Ladder::encounter(Gamestate& gs){
    gs.z += this->z_offset;
    return false;
}