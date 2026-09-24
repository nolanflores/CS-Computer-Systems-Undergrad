#include <iostream>
// cctype provides tolower(), converting uppercase chars to lowercase
#include <cctype>

#include "game.hpp"

// Returns true if the game is over
// (not prototyped in game.hpp since it only needs to be called from other
// functions within this file)
bool game_over(const std::vector<event*>& game_board, const player& p) {
	return p.is_dead() || (p.get_location() >= game_board.size() - 1);
}

// Prints the game board to the terminal
// (not prototyped in game.hpp since it only needs to be called from other
// functions within this file)
void display_game_board(
		const std::vector<event*>& game_board,
		const player& p) {
	p.print_hp();
	std::cout << "||";
	for (int i = 0; i < game_board.size(); i++) {
		if (p.get_location() == i) {
			// If player is at this location, print an asterisk
			std::cout << '*';
		} else {
			// Else, print a space
			std::cout << ' ';
		}

		if (game_board.at(i)) {
			// If ith event pointer is "true" (i.e., if it is not nullptr /
			// 0 / "false"), then print it to the terminal
			game_board.at(i)->print();
		} else {
			// Else, print a space
			std::cout << ' ';
		}

		// One more space, and a || to separate this tile from the next tile
		std::cout << " ||";
	}

	// Print endline since the gameboard has finished printing
	std::cout << std::endl;
}

void print_error() {
	std::cout << "Error: Invalid option entered" << std::endl << std::endl;
}

bool is_bad_option(const std::string& option) {
	if (option != "A" && option != "D" && option != "a" && option != "d") {
		return true; // Bad option entered
	}

	return false;
}

bool is_bad_direction(
		char direction,
		const std::vector<event*>& game_board,
		const player& p) {
	if (direction == 'a' && p.get_location() <= 0) {
		return true; // Cannot move left; already at edge of board
	} else if (direction == 'd' && p.get_location() == game_board.size() - 1) {
		return true; // Cannot move right; already at edge of board
	}

	return false;
}

char prompt_option(const std::vector<event*>& game_board, const player& p) {
	char option_char;
	bool bad_direction;
	bool bad_option;
	do {
		std::cout << "Type A to go left or D to go right: ";
		std::string option;
		std::getline(std::cin, option);

		// Check whether the user entered a valid option (a/A/d/D)
		bad_option = is_bad_option(option);
		if (bad_option) {
			// Bad option. Error and reprompt
			std::cout << "Error: Invalid option" << std::endl << std::endl;
			bad_direction = false;
		} else {
			// Good option.

			// Get first character of option and convert to lowercase
			option_char = tolower(option[0]);

			// Check whether the player can move in the specified direction
			// (they might be at the edge of the game board)
			bad_direction = is_bad_direction(option_char, game_board, p);

			if (bad_direction) {
				std::cout << "Error: You can't move in that direction!" <<
					std::endl;
			}
		}
	} while (bad_option || bad_direction);

	// User entered a good direction that they can move in. Return that
	// direction's lowercase character ('a' or 'd')
	return option_char;
}

void move_player(player& p, char direction) {
	if (direction == 'a') {
		p.move_left();
	} else {
		p.move_right();
	}
}

void trigger_encounter(std::vector<event*>& game_board, player& p) {
	int location = p.get_location();

	if (game_board.at(location)) {
		game_board.at(location)->encounter(p);
		delete game_board.at(location);
		game_board.at(location) = nullptr;
	}
}

// Call at the end of the game. Determines whether the player won or lost
// and prints the appropriate message to the terminal.
void print_game_over_message(const player& p) {
	if (p.is_dead()) {
		std::cout << "Game over! You died :(" << std::endl;
	} else {
		std::cout << "Great job! You won!" << std::endl;
	}
}

void play(std::vector<event*>& game_board, player& p) {
	while (!game_over(game_board, p)) {
		// Clear terminal text (may only work on *nix systems, like the ENGR
		// servers)
		std::cout << "\x1B[2J\x1B[H";

		// Print the board and options
		display_game_board(game_board, p);
		char option = prompt_option(game_board, p);

		// Move the player in direction specified
		move_player(p, option);

		// Trigger encounter if the player is on an event
		trigger_encounter(game_board, p);
	}

	print_game_over_message(p);
}
