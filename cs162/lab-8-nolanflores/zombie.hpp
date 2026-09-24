#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include "event.hpp"
#include "player.hpp"

#include <iostream>

// TODO Define the zombie class and prototype its encounter() and print()
// functions
class zombie : public event{
    void encounter(player& p);

    void print() const;
};

#endif
