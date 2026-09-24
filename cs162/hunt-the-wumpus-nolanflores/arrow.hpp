#ifndef ARROW_HPP
#define ARROW_HPP

#include "event.hpp"

class Arrow : public Event{
public:
    /*
     * Function: print_char
     * Description: Inhereted from Event class
     *      prints 'A' via ncurses
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
     *      Adds 1 to number of Arrows
     * Returns (bool): true, arrows are removed after being picked up
    */
    bool encounter(Gamestate& gs);
};

#endif
