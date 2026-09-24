#include <iostream>

#include "baseball_player.hpp"

baseball_player* create_players(int size) {
	return new baseball_player[size];
}

void print_player(const baseball_player& player) {
	std::cout << player.first_name << " " <<
		player.last_name << " has a batting average of " <<
		player.batting_average << std::endl;
}

std::string prompt_for_file_name() {
	std::cout << "Enter the name of the data file: ";
	std::string file_name;
	std::cin >> file_name;
	return file_name;
}

void populate_player_data(baseball_player& player, std::ifstream& file) {
	file >> player.first_name;
	file >> player.last_name;
	file >> player.batting_average;
}

void delete_player_info(baseball_player* players) {
	delete [] players;
}
