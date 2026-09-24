#ifndef GOLD_HPP
#define GOLD_HPP

#include "event.hpp"

class Gold : public Event{
public:
    /*
     * Function: print_char
     * Description: Inhereted from Event class
     *      prints 'G' via ncurses
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
     *      sets have_gold to true in Gamestate
     * Returns (bool): true, Gold is removed after being picked up
    */
    bool encounter(Gamestate& gs);
};

#endif
