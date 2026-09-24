#include <iostream>

#include "player.hpp"

void player::take_damage(int amount) {
	this->hp -= amount;
}

bool player::is_dead() const {
	// Return true if this->hp <= 0, false otherwise
	return this->hp <= 0;
}

void player::heal(int amount) {
	this->hp += amount;
}

void player::print_hp() const {
	std::cout << "HP Remaining (" << this->hp << "/5): ";
	
	// We'll print # green squares proportional to HP remaining, and remaining
	// as red squares for HP lost. Compute # of each color square to print.
	int total_squares = 40;
	int green_squares = static_cast<int>(this->hp / 5.0 * 40);
	int red_squares = total_squares - green_squares;
	
	// Set text background color to green (only works on *nix systems, like
	// the ENGR servers) and print green squares
	std::cout << std::flush << "\033[42m" << std::flush;
	for (int i = 0; i < green_squares; i++) {
		std::cout << ' '; // Spaces with green background
	}

	// Set text background color to red (only works on *nix systems, like
	// the ENGR servers) and print red squares
	std::cout << std::flush << "\033[41m" << std::flush;
	for (int i = 0; i < red_squares; i++) {
		std::cout << ' '; // Spaces with red background
	}

	// Reset text background color (only works on *nix systems, like the ENGR
	// servers)
	std::cout << std::flush << "\033[0m" << std::flush;

	std::cout << std::endl;
}

int player::get_location() const {
	return this->location;
}

void player::move_right() {
	this->location++;
}

void player::move_left() {
	this->location--;
}
