#ifndef LADDER_HPP
#define LADDER_HPP

#include "event.hpp"

class Ladder : public Event{
    int z_offset;   //the number of floors to move on encounter
public:
    /*
     * Non-default constructor: Ladder(int z_offset)
     * Description: Instantiates the number of floors the
     *      player moves when interacting with the Ladder
     * Parameter:
     *      z_offset (int): number of floors to move
    */
    Ladder(int z_offset);

    /*
     * Function: print_char
     * Description: Inhereted from Event class
     *      prints '^' or 'v' or 'L' via ncurses
     *      '^' (up) if the z_offset is negative
     *      'v' (down) if the z_offset is positive
     *      'L' if z_offset is 0 (this should not happen)
    */
    void print_char() const;

    /*
     * Function: print_char
     * Description: Inhereted from Event class
     *      prints different precepts depending on
     *      if the z_offset is positive or negative
    */
    void print_precept() const;

    /*
     * Function: encounter
     * Description: Inhereted from Event class
     *      changes the Player z by the ammount in z_offset
     * Returns (bool): false, Ladders can be encountered again
    */
    bool encounter(Gamestate& gs);
};

#endif