#ifndef EVENT_HPP
#define EVENT_HPP

#include "gamestate.hpp"
#include <ncurses.h>

class Event {
public:
	/*
	 * Name: print_char
	 * Description: prints the char representing the
	 * 		event via ncurses, for debugging purposes
	*/
	virtual void print_char() const = 0;

	/*
	 * Name: print_precept
	 * Description: prints out a precept (warning message)
	 * 		for the given event via ncurses
	*/
	virtual void print_precept() const = 0;

	/*
	 * Name: encounter
	 * Description: makes the desired changes to the game state
	 * 		upon the player entering the room with the event
	 * Parameters:
	 * 		gs (Gamestate&): reference to the struct holding
	 * 			the gamestate variables to be modified
	 * Returns (bool): Whether or not the event should be
	 * 		removed after the player encounters the event
	*/
	virtual bool encounter(Gamestate& gs) = 0;

	/*
	 * virtual destructor
	*/
	virtual ~Event() = default;
};

#endif
