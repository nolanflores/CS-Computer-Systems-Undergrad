#include <iostream>

#include "tornado.hpp"

// TODO Implement the tornado's encounter() function override to push the
// player by 1 space (i.e., decrement their location by 1 by calling
// move_left() on the player object)
void tornado::encounter(player& p){
    p.move_left();
}

// TODO Implement the tornado's print() function override to print "T"
// to the terminal (do NOT print std::endl after the "T")
void tornado::print() const{
    std::cout << "T";
}