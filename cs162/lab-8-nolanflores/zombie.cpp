#include <iostream>

#include "zombie.hpp"

// TODO Implement the zombie's encounter() function override to damage the
// player by 2 HP
void zombie::encounter(player& p){
    p.take_damage(2);
}

// TODO Implement the zombie's print() function override to print "Z"
// to the terminal
void zombie::print() const{
    std::cout << "Z";
}
