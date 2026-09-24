#ifndef WUMPUS_HPP
#define WUMPUS_HPP

#include "event.hpp"

class Wumpus : public Event{
public:
    /*
     * Function: print_char
     * Description: Inhereted from Event class
     *      prints 'W' via ncurses
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
     *      Removes a life, sends the Player back to the rope
     * Returns (bool): false, the Wumpus can be encountered again
    */
    bool encounter(Gamestate& gs);
};

#endif
