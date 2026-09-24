#ifndef EVENT_HPP
#define EVENT_HPP

#include "player.hpp"

class event {
public:
	// TODO prototype pure virtual encounter() function here
	virtual void encounter(player& p) = 0;

	// TODO prototype pure virtual print() function here
	virtual void print() const = 0;

	// TODO Virtual destructor is required to avoid undefined
	// behavior when deleting objects polymorphically
	virtual ~event() = default;
};

#endif
