#ifndef ARMOR_HPP
#define ARMOR_HPP

#include "event.hpp"

class Armor : public Event{
public:
    /*
     * Function: print_char
     * Description: Inhereted from Event class
     *      prints 'O' via ncurses
    */
    void print_char() const;

    /*
     * Function: print_precept
     * Description: Inhereted from Event class
    */
    void print_precept() const;

    /*
     * Function: encounter
     * Description: Inhereted from Event class
     *      Sets the Player armor to 2
     * Returns (bool): true, armor is removed after being picked up
    */
    bool encounter(Gamestate& gs);
};

#endif