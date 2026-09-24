#include "catalog.h"
#include <iostream>
#include <string>
#include <fstream>

team* create_teams(int size) {
	return new team[size];
}

void populate_team_data(team& t, std::ifstream& file) {
	file >> t.name;
	file >> t.owner;
	file >> t.market_value;
	file >> t.num_players;
	t.total_ppg = 0;//couldn't think of a cleaner way than to do this in the main
}

player* create_players(int size) {
	return new player[size];
}

void populate_player_data(player& p, std::ifstream& file) {
	file >> p.name;
	file >> p.age;
	file >> p.nation;
	file >> p.ppg;
	file >> p.fg;
}

void delete_info(team* teams, int size) {
	for(int i = 0; i < size; i++){
		delete[] teams[i].p;//free player arrays
	}
	delete[] teams;//free team array
	teams = nullptr;
}


std::string prompt_file_name(){
	std::cout << "Enter the team info file name: ";
    std::string file_name;
    std::getline(std::cin, file_name);//use getline for all user inputs
    return file_name;
}


int prompt_options(){
	while(true){
		std::cout << std::endl;
		std::cout << "Which option would you like to choose?" << std::endl;
		std::cout << "1. Search team by its name" << std::endl;
		std::cout << "2. Display the top scorer of each team" << std::endl;
		std::cout << "3. Search players by nationality" << std::endl;
		std::cout << "4. Quit" << std::endl;
		std::cout << "Your Choice: ";
		std::string option;
		std::getline(std::cin,option);
		int num_option = std::stoi(option);
		if(num_option >= 1 && num_option <= 4)
			return num_option;
		std::cout << "\nNot a valid input." << std::endl;
	}
}


int prompt_output(){
	while(true){
		std::cout << std::endl;
		std::cout << "How would you like the information displayed?" << std::endl;
		std::cout << "1. Print to screen" << std::endl;
		std::cout << "2. Print to file" << std::endl;
		std::cout << "Your Choice: ";
		std::string option;
		std::getline(std::cin,option);
		if(option == "1" || option == "2")
			return std::stoi(option);
		std::cout << "\nNot a valid input." << std::endl;
	}
}

//there are two functions associated with each action, 1 for the terminal, 1 for files

void search_team_by_name_cout(team* teams, int num_teams){
	std::cout << std::endl;
	std::cout << "Enter the team's name: ";
	std::string team_name;
	std::getline(std::cin, team_name);
	for(int i = 0; i < num_teams; i++){//iterate through teams
		if(teams[i].name == team_name){//team name matches input
			std::cout << team_name << std::endl;
			std::cout << "Owner: " << teams[i].owner << std::endl;
			std::cout << "Market Value: $" << teams[i].market_value << std::endl;
			std::cout << teams[i].total_ppg << " points per game" << std::endl;// the tabs are an attempt at formatting
			std::cout << "Player\t\t\tAge\tPPG\tFG%\tNationality" << std::endl;// I'm not sure they'll work in demo
			for(int j = 0; j < teams[i].num_players; j++){//iterate through players
				std::cout << teams[i].p[j].name;
				std::cout << "\t\t" << teams[i].p[j].age;
				std::cout << "\t" << teams[i].p[j].ppg;
				std::cout << "\t" << teams[i].p[j].fg;
				std::cout << "\t" << teams[i].p[j].nation << std::endl;
			}
			return;//desired team has been found
		}
	}
	std::cout << "\nCouldn't find " + team_name + "." << std::endl;//desired team isn't in the array
}



void search_team_by_name_file(team* teams, int num_teams){
	std::cout << std::endl;
	std::cout << "Please Provide the desired filename: ";//file opening could probably be moved into another file
	std::string filename;								 //I'm not sure how, though.
	std::getline(std::cin, filename);
	std::ofstream output;
	output.open(filename, std::ios::app);
	std::cout << "Enter the team's name: ";
	std::string team_name;
	std::getline(std::cin, team_name);
	for(int i = 0; i < num_teams; i++){//iterate through teams
		if(teams[i].name == team_name){//team name matches input
			output << team_name << std::endl;
			output << "Owner: " << teams[i].owner << std::endl;
			output << "Market Value: $" << teams[i].market_value << std::endl;
			output << teams[i].total_ppg << " points per game" << std::endl;
			output << "Player\t\t\tAge\tPPG\tFG%\tNationality" << std::endl;
			for(int j = 0; j < teams[i].num_players; j++){
				output << teams[i].p[j].name;
				output << "\t\t" << teams[i].p[j].age;
				output << "\t" << teams[i].p[j].ppg;
				output << "\t" << teams[i].p[j].fg;
				output << "\t" << teams[i].p[j].nation << std::endl;
			}
			return;//desired team found
		}
	}
	std::cout << "\nCouldn't find " + team_name + "." << std::endl;//desired team isn't in the array
	output.close();
}



void search_top_scorers_cout(team* teams, int num_teams){
	std::cout << std::endl;
	for(int i = 0; i < num_teams; i++){//iterate through teams
		player p = teams[i].p[0];
		for(int j = 0; j < teams[i].num_players; j++){//iterate through players
			if(teams[i].p[j].ppg > p.ppg){
				p = teams[i].p[j];
			}
		}
		std::cout << teams[i].name << ": " << p.name << " " << p.ppg << std::endl;//print top scorer
	}
}


void search_top_scorers_file(team* teams, int num_teams){
	std::cout << std::endl;
	std::cout << "Please Provide the desired filename: ";
	std::string filename;
	std::getline(std::cin, filename);
	std::ofstream output;
	output.open(filename, std::ios::app);
	for(int i = 0; i < num_teams; i++){//iterate through teams
		player p = teams[i].p[0];
		for(int j = 0; j < teams[i].num_players; j++){//iterate through players
			if(teams[i].p[j].ppg > p.ppg){
				p = teams[i].p[j];
			}
		}
		output << teams[i].name << ": " << p.name << " " << p.ppg << std::endl;//write top scorer to file
	}
	output.close();
}

void search_by_nation_cout(team* teams, int num_teams){
	std::cout << std::endl;
	std::cout << "Enter the player's nationality: ";
	std::string nation;
	std::getline(std::cin,nation);
	bool no_nation = true;
	for(int i = 0; i < num_teams; i++){//iterate through teams
		for(int j = 0; j < teams[i].num_players; j++){//iterate through players
			if(nation == teams[i].p[j].nation){
				no_nation = false;
				std::cout << teams[i].p[j].name << " " << teams[i].p[j].age << std::endl;//print player
			}
		}
	}
	if(no_nation)
		std::cout << "\nNo players from \"" << nation << "\" found." << std::endl;//no players of inputed nationality
}


void search_by_nation_file(team* teams, int num_teams){
	std::cout << std::endl;
	std::cout << "Please Provide the desired filename: ";
	std::string filename;
	std::getline(std::cin, filename);
	std::ofstream output;
	output.open(filename, std::ios::app);
	std::cout << "Enter the player's nationality: ";
	std::string nation;
	std::getline(std::cin,nation);
	bool no_nation = true;
	for(int i = 0; i < num_teams; i++){//iterate through
		for(int j = 0; j < teams[i].num_players; j++){//iterate through players
			if(nation == teams[i].p[j].nation){
				no_nation = false;
				output << teams[i].p[j].name << " " << teams[i].p[j].age << std::endl;
			}
		}
	}
	if(no_nation)
		std::cout << "\nNo players from \"" << nation << "\" found." << std::endl;//no players of inputed nationality
	output.close();
}