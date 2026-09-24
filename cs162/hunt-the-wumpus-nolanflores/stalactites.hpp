#ifndef STALACTITES_HPP
#define STALACTITES_HPP

#include "event.hpp"

class Stalactites : public Event{
public:
    /*
     * Function: print_char
     * Description: Inhereted from Event class
     *      prints 'S' via ncurses
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
     *      50% chance of removing a life and sending
     *      the player back to the escape rope
     * Returns (bool): false, Stalactites can be encountered again
    */
    bool encounter(Gamestate& gs);
};

#endif
