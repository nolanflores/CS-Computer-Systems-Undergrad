/*
 * Author: Nolan Flores
 * Oregon State University
 * College of Engineering
 * Description: Hunt the Wumpus is a terminal based Dungeon Crawler.
 * 		You navigate a cave with a size of your choosing, navigating
 * 		around dangerous Stalactites and confusing Super Bats to
 * 		travel up and down ladders to collect arrows and gold and
 * 		make your escape. Or use the Arrows to shoot the deadly Wumpus.
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include "game.hpp"

/*
 * Function: get_width
 * Description: Prompts the user for the game board width (# of columns)
 * Returns (int): Valid width supplied by user
 */
int get_width() {
	int width;
	bool first = true;
	do {
		if (!first) {
			std::cout << std::endl << "Invalid width!" << std::endl <<std::endl;
		}
		first = false;
		std::cout << "Enter the game board width between 4 and 30: ";
		std::cin >> width;
	} while(width < 4 || width > 30);
	return width;
}

/*
 * Function: get_height
 * Description: Prompts the user for the game board height (# of columns)
 * Returns (int): Valid height supplied by user
 */
int get_height() {
	int height;
	bool first = true;
	do {
		if (!first) {
			std::cout << std::endl << "Invalid height!" << std::endl <<
				std::endl;
		}
		first = false;
		std::cout << "Enter the game board height between 4 and 30: ";
		std::cin >> height;
	} while(height < 4 || height > 30);
	return height;
}

/*
 * Function: get_depth
 * Description: Prompts the user for the game board depth (# of layers)
 * Returns (int): Valid depth supplied by user
 */
int get_depth() {
	int depth;
	bool first = true;
	do {
		if (!first) {
			std::cout << std::endl << "Invalid depth!" << std::endl <<
				std::endl;
		}
		first = false;
		std::cout << "Enter the game board depth between 1 and 30: ";
		std::cin >> depth;
	} while(depth < 1 || depth > 30);
	return depth;
}

/*
 * Function: get_debug
 * Description: Prompts the user whether they want to play in debug mode
 * Returns (bool): True if the user wants to play in debug mode. False
 * 		otherwise.
 */
bool get_debug() {
	int debug_input;
	bool first = true;
	do {
		if (!first) {
			std::cout << std::endl << "Invalid input!" << std::endl <<
				std::endl;
		}
		first = false;
		std::cout << "Would you like to play in debug mode? (1-yes, 0-no): ";
		std::cin >> debug_input;
	} while(debug_input != 0 && debug_input != 1);
	return debug_input == 1;
}

int main()
{
	// Set the random seed
	srand(time(nullptr));
	
	// Ask user for width and height of game board
	int width = get_width();
	int height = get_height();
	int depth = get_depth();

	// Ask user whether they want debug mode
	bool debug = get_debug();

	//initialize ncurses
	initscr();
	noecho();

	// Construct game object
	Game g(width, height, depth, debug);

	//Play game
	bool win = g.play_game();

	//end ncurses
	endwin();

	if(win){
		std::cout << "You Won!" << std::endl;
	}else{
		std::cout << "You Lost :(" << std::endl;
	}

	return 0;
}
