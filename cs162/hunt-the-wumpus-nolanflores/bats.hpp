#ifndef BATS_HPP
#define BATS_HPP

#include "event.hpp"

class Bats : public Event{
public:
    /*
     * Function: print_char
     * Description: Inhereted from Event class
     *      prints 'B' via ncurses
    */
    void print_char() const;

    /*
     * Function: print_char
     * Description: Inhereted from Event class
    */
    void print_precept() const;

    /*
     * Function: encounter
     * Description: Inhereted from Event class
     *      Confuses the player, resulting in a random move
     * Returns (bool): false, Bats can be encountered again
    */
    bool encounter(Gamestate& gs);
};

#endif
