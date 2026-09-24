#include <fstream>
#include <iostream>

#include "baseball_player.hpp"

int main() {
	std::string file_name = prompt_for_file_name();
	std::ifstream file;
	file.open(file_name);
	if (!file.is_open()) {
		std::cout << file_name << " could not be opened" << std::endl;
		return -1;
	}

	int size;
	file >> size;

	// Allocate array
	baseball_player* players = create_players(size);
	
	// Populate array data
	for (int i = 0; i < size; i++) {
		populate_player_data(players[i], file);
	}

	// Print array data
	for (int i = 0; i < size; i++) {
		print_player(players[i]);
	}

	// Delete array data
	delete_player_info(players);
}
