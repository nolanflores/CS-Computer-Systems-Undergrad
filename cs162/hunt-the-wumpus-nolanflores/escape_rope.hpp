#ifndef ESCAPE_ROPE_HPP
#define ESCAPE_ROPE_HPP

#include "event.hpp"

class Escape_Rope : public Event{
public:
    /*
     * Function: print_char
     * Description: Inhereted from Event class
     *      prints 'R' via ncurses
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
     *      Ends the game, if the player has collected the gold
     * Returns (bool): false, The rope stays in place
    */
    bool encounter(Gamestate& gs);
};

#endif
