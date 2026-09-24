#ifndef ROOM_HPP
#define ROOM_HPP

#include "event.hpp"

class Room {
private: 
	Event* room_event = nullptr;	//Event pointer for Polymorphism
public:
	/*
	 * Function: set_event
	 * Description: sets the room_event pointer to a new
	 * 		event address. Deletes the old Event from memory
	 * 		if the room_event is not a nullptr
	 * Parameter:
	 * 		e (Event*): pointer to new Event
	*/
	void set_event(Event* e);

	/*
	 * Function: get_event
	 * Returns (Event*): member room_event
	*/
	Event* get_event() const;

	/*
	 * Destructor
	 * Description: Frees the room_event from memory, if not a nullptr
	*/
	~Room();
};

#endif
