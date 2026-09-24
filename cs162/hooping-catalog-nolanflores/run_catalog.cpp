#include "catalog.h"
#include <iostream>

int main() {
	//open the file
	std::string file_name = prompt_file_name();
	std::ifstream file;
	file.open(file_name);
	if (!file.is_open()) {//check if file exists
		std::cout << file_name << " could not be opened." << std::endl;
		return -1;//file doesn't exist
	}

	//create and parse data into teams and players
	int num_teams;
	file >> num_teams;
	team* teams = create_teams(num_teams);
	for(int i = 0; i < num_teams; i++){
		populate_team_data(teams[i], file);
		teams[i].p = create_players(teams[i].num_players);
		for(int j = 0; j < teams[i].num_players; j++){
			populate_player_data(teams[i].p[j], file);
			teams[i].total_ppg += teams[i].p[j].ppg;//couldn't think of a way to do this out of main
		}
	}
	file.close();

	while(true){//this whole situation is gross
		int option = prompt_options();//get desired action
		if(option == 4){
			break;//user wants to quit
		}
		int print_option = prompt_output();
		if(option == 1){
			if(print_option == 1)
				search_team_by_name_cout(teams,num_teams);//terminal
			else
				search_team_by_name_file(teams,num_teams);//file
		}else if(option == 2){
			if(print_option == 1)
				search_top_scorers_cout(teams,num_teams);//terminal
			else
				search_top_scorers_file(teams,num_teams);//file
		}else if(option == 3){
			if(option == 1)
				search_by_nation_cout(teams,num_teams);//terminal
			else
				search_by_nation_file(teams,num_teams);//file
		}
	}

	delete_info(teams, num_teams);//free dynamic memory
}
