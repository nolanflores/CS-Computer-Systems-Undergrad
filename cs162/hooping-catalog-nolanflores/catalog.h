#include <string>
#include <fstream>
#include <iostream>

// DO NOT MODIFY THIS STRUCT TYPE DEFINITION
struct team {
    std::string name; // Name of the team
    std::string owner; // Owner of the team
    int market_value; // Market value of the team
    int num_players; // Number of players in the team
	// Pointer to base address of array that holds all players
    struct player* p;
    float total_ppg; // Total points per game
};

// DO NOT MODIFY THIS STRUCT TYPE DEFINITION
struct player {
    std::string name; // Name of the player
    int age; // Age of the player
    std::string nation; // Nationality of the player
    float ppg; // Points per game of the player
    float fg; // Field goal percentage
};


/*
 * THIS IS A REQUIRED FUNCTION. DO NOT MODIFY ITS PROTOTYPE. YOU MUST
 * 		IMPLEMENT IT IN `catalog.cpp`.
 * Name: create_teams
 * Description: This function will dynamically allocate an array of teams
 * Parameters:
 * 		size (int): Size of the array to allocate
 * Returns: Pointer storing the base address of the allocated team array
 * Post-conditions: A team array of requested size is dynamically allocated
 * 		The responsibility of freeing this dynamic memory falls on the function
 * 		caller.
 */
team* create_teams(int size);


/*
 * THIS IS A REQUIRED FUNCTION. DO NOT MODIFY ITS PROTOTYPE. YOU MUST
 * 		IMPLEMENT IT IN `catalog.cpp`.
 * Name: populate_team_data
 * Description: This function will fill a single team struct with information
 * 		that is read in from the file
 * Parameters:
 * 		t (team&): Reference to the team struct to be filled with
 * 			information. NOTE: An alternative way to design this function
 *			would be to make it construct a team and return it rather
 *			than accepting one by reference and modifying it. Actually,
 *			that'd be a better idea, but use this prototype anyways as an
 *			opportunity to practice pass-by-reference.
 * 		file (std::ifstream&): Reference to the input file stream from which to
 * 			retrieve information for filling the team struct
 * Post-conditions: The given team struct is populated with the next
 * 		information from the input file. This will also modify the input file's
 * 		state so that subsequent reads operate on whatever data comes after
 * 		the data read to populate the team struct.
 */
void populate_team_data(team& t, std::ifstream& file);


/*
 * THIS IS A REQUIRED FUNCTION. DO NOT MODIFY ITS PROTOTYPE. YOU MUST
 * 		IMPLEMENT IT IN `catalog.cpp`.
 * Name: create_players
 * Description: This function will dynamically allocate an array of players
 * Parameters:
 * 		size (int): Size of the array to allocate
 * Returns: Pointer storing the base address of the allocated player array
 * Post-conditions: A player array of requested size is dynamically allocated
 * 		The responsibility of freeing this dynamic memory falls on the function
 * 		caller.
 */
player* create_players(int size);


/*
 * THIS IS A REQUIRED FUNCTION. DO NOT MODIFY ITS PROTOTYPE. YOU MUST
 * 		IMPLEMENT IT IN `catalog.cpp`.
 * Name: populate_player_data
 * Description: This function will fill a single player struct with
 * 		information that is read in from the file
 * Parameters:
 * 		p (player&): Reference to the player struct to be filled with
 * 			information. NOTE: An alternative way to design this function
 *			would be to make it construct a player and return it rather
 *			than accepting one by reference and modifying it. Actually,
 *			that'd be a better idea, but use this prototype anyways as an
 *			opportunity to practice pass-by-reference.
 * 		file (std::ifstream&): Reference to the input file stream from which to
 * 			retrieve information for filling the player struct
 * Post-conditions: The given player struct is populated with the next
 * 		information from the input file. This will also modify the input file's
 * 		state so that subsequent reads operate on whatever data comes after
 * 		the data read to populate the player struct.
 */
void populate_player_data(player& p, std::ifstream& file);


/*
 * THIS IS A REQUIRED FUNCTION. DO NOT MODIFY ITS PROTOTYPE. YOU MUST
 * 		IMPLEMENT IT IN `catalog.cpp`.
 * Name: delete_info
 * Description: This function will delete all of the dynamically allocated
 * 		memory
 * Parameters:
 * 		teams (team*): Pointer to the base address of the team array
 * 		size (int): The number of teams
 * Pre-conditions: The team array at the provided pointer is valid and hasn't
 * 		been freed yet
 * Post-conditions: The team array, along with all players inside, is freed
 */
void delete_info(team* teams, int size);




/*
 * Name: prompt_file_name
 * Description: gets the user inputed name of the text file containing the stats
 * Returns (std::string): the name of the file
*/
std::string prompt_file_name();


/*
 * Name: prompt_options
 * Description: prints out options 1 through 4 and gets user choice between
 *      the four actions.
 *  returns (int): integer 1 through 4 indicating what choice is desired
 *      1: Search by team name
 *      2: Print top scorers of each team
 *      3: Search players by nationality
 *      4: Quit
*/
int prompt_options();


/*
 * Name: prompt_output
 * Description: prints options and gets user choice between printing the output to the console
 *      or writing the output to a file.
 *  returns (int): 1 or 2. 1: print to the console, 2: print to file
*/
int prompt_output();


/*
 * Name: search_team_by_name_file
 * Description: prompts the user for the name of a team, parses through an array of teams,
 *      and prints out the information and statistics of all of the players belonging
 *      to the team matching the input to the terminal
 * Paramters:
 *      teams (team*): pointer to the base adress of the team array
 *      num_teams (int): the number of teams in the team array
*/
void search_team_by_name_cout(team* teams, int num_teams);


/*
 * Name: search_team_by_name_cout
 * Description: prompts the user for the name of a team and name of a desired output file,
 *      parses through an array of teams, and writes the information and statistics of all
 *      of the players belonging to the team matching the name inputed to the desired file.
 * Paramters:
 *      teams (team*): pointer to the base adress of the team array
 *      num_teams (int): the number of teams in the team array
*/
void search_team_by_name_file(team* teams, int num_teams);


/*
 * Name: search_top_scorers_cout
 * Description: parses through an array of teams, and prints the information of the top
 *      scoring player of each team to the terminal
 * Paramters:
 *      teams (team*): pointer to the base adress of the team array
 *      num_teams (int): the number of teams in the team array
*/
void search_top_scorers_cout(team* teams, int num_teams);


/*
 * Name: search_top_scorers_file
 * Description: prompts the user for the name of the desired output file,
 *      parses through an array of teams, and writes the information of the top
 *      scoring player of each team to the desired file
 * Paramters:
 *      teams (team*): pointer to the base adress of the team array
 *      num_teams (int): the number of teams in the team array
*/
void search_top_scorers_file(team* teams, int num_teams);


/*
 * Name: search_by_nation_cout
 * Description: prompts the user for a nationality, parses through an array of teams,
 *      and prints out every player, of all teams, of that nationality to the terminal
 * Paramters:
 *      teams (team*): pointer to the base adress of the team array
 *      num_teams (int): the number of teams in the team array
*/
void search_by_nation_cout(team* teams, int num_teams);


/*
 * Name: search_by_nation_file
 * Description: prompts the user for a nationality and name of the desired output file,
 *      parses through an array of teams, and writes every player, of all teams,
 *      of that nationality to the desired output file
 * Paramters:
 *      teams (team*): pointer to the base adress of the team array
 *      num_teams (int): the number of teams in the team array
*/
void search_by_nation_file(team* teams, int num_teams);