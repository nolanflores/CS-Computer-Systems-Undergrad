#include <vector>

#include "game.hpp"
#include "event.hpp"
#include "apple_pie.hpp"
#include "zombie.hpp"
#include "tornado.hpp"

int main() {
	// TODO Create vector of event pointers. Initialize those pointers like so:
	std::vector<event*> events;
	events.push_back(nullptr);
	events.push_back(new zombie);
	events.push_back(new zombie);
	events.push_back(new apple_pie);
	events.push_back(new tornado);
	events.push_back(nullptr);
	events.push_back(new zombie);
	events.push_back(new apple_pie);
	events.push_back(nullptr);
	events.push_back(new zombie);


	// Create the player object, p
	player p;

	// TODO Pass your vector of event pointers and p to the global play() function,
	// provided by game.hpp
	play(events, p);
}
