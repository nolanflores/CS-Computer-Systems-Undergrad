/*
 * Author: Nolan Flores
 * Program description: Simulates the NBA three point contest, each shot has a 50% chance of making
*/

#include <iostream>
#include <cstdlib>
#include <ctime>


/*
 * Function: promptNumPlayers
 * Description: prompts the user for an int greater than 0, loops until a valid num is entered
 * Returns (int): number of players
*/
int promptNumPlayers(){
	while(true){
		std::cout << "\nEnter the number of players: ";
		int num;
		std::cin >> num;
		std::cout << std::endl;
		if(num > 0)
			return num;
		std::cout << "Invalid input, try again." << std::endl;
	}
}


/*
 * Function: promptMoneyRack
 * Description: prompts user for an integer between 1 and 5, loops until a valid number is entered
 * Returns (int): the inputed number minus 1 to correspond to the index of the money rack
*/
int promptMoneyRack(){
	while(true){
		std::cout << "Where do you want the money-ball rack? Enter 1-5: ";
		int rack;
		std::cin >> rack;
		std::cout << std::endl;
		if(1 <= rack && 5 >= rack)
			return rack-1;
		std::cout << "Invalid input, try again." << std::endl;
	}
}


/*
 * Function: shootHoops
 * Description: simulates the shooting of balls, filling a array of 27 ints with the corresponding scores
 * 		0 for missed shots, 1 for made shots, 2 for made moneyballs, 3 for the starry shots
 * 		the first 25 of the array are the regular and money balls, the last 2 are the starry balls
 * Parameters:
 * 		shots[27] (int): an array passed by reference containing the scores
 * 		moneyRack (int): the index for the money rack
*/
void shootHoops(int shots[27], int moneyRack){
	for(int i = 0; i < 25; i++){
		if(i/5 == moneyRack || i%5 == 4){
			shots[i] = 2 * (rand()%2);
		}else{
			shots[i] = rand()%2;
		}
	}
	shots[25] = 3*(rand()%2);
	shots[26] = 3*(rand()%2);
}


/*
 * Function: scoreToChar
 * Description: helper function that gives a symbol to be printed corresponding to a score
 * Parameters:
 * 		score (int): the score to be translated
 * Returns (char): the symbol corresponding to the score
*/
char scoreToChar(int score){
	if(score == 1){
		return 'O';
	}else if(score == 2){
		return 'M';
	}else if(score == 3){
		return 'S';
	}
	return '_';
}


/*
 * Function: scoreShots
 * Description: loops through an array of scores, printing them out to the console, and calculates the score
 * Parameters:
 * 		shots[27] (int): array of scores, where the first 25 are balls and money balls, while 26 and 27 are stary balls
 * Returns (int): the calculated score
*/
int scoreShots(int shots[27]){
	int score = 0;
	for(int rack = 0; rack < 5; rack++){
		if(rack == 2){
			std::cout << "Starry: " << scoreToChar(shots[25]) << "\t  | " << shots[25] << " pts" << std::endl;
			score += shots[25];
		}else if(rack == 4){
			std::cout << "Starry: " << scoreToChar(shots[26]) << "\t  | " << shots[26] << " pts" << std::endl;
			score += shots[26];
		}
		std::cout << "Rack " << rack+1 << ": ";
		int rackscore = 0;
		for(int ball = 0; ball < 5; ball++){
			int i = (rack*5)+ball;
			std::cout << scoreToChar(shots[i]) << " ";
			rackscore += shots[i];
		}
		std::cout << "| " << rackscore << " pts" << std::endl; 
		score += rackscore;
	}
	std::cout << "\nTotal: " << score << std::endl << std::endl;
	return score;
}


/*
 * Function: promptReplay
 * Description: prompts the user for 1 or 0 to replay or quit. loops until a valid number is entered
 * Returns (bool): true if 1, false if 0
*/
bool promptReplay(){
	while(true){
		std::cout << "Do you want to play again? (1-yes, 0-no): ";
		int replay;
		std::cin >> replay;
		if(replay == 1 || replay == 0)
			return replay;
		std::cout << "\nSorry, that’s not a valid input." << std::endl;
	}
}


/*
 * Function: printWinner
 * Description: loops through a dynamic array and prints out the winning player
 * Parameters:
 * 		scores (int*): a dynamic array containing all of the scores
 * 		numPlayers (int): the number of players/scores in the array
*/
void printWinner(int* scores, int numPlayers){
	bool tie = false;
	int winner, winningScore = 0;
	for(int i = 0; i < numPlayers; i++){
		if(winningScore < scores[i]){
			tie = false;
			winner = i+1;
			winningScore = scores[i];
		}else if(winningScore == scores[i]){
			tie = true;
		}
	}
	if(tie){
		std::cout << "It's a tie!!" << std::endl;
	}else{
		std::cout << "Player " << winner << " is the winner!!" << std::endl << std::endl;
	}
}



int main() {
	srand(time(nullptr));//seed random
	std::cout << "Welcome to the basketball shooting contest!" << std::endl;
	do{
		int numPlayers = promptNumPlayers();
		int* scores = new int[numPlayers];//dynamic array
		for(int i = 0; i < numPlayers; i++){
			std::cout << "Player " << i+1 << ":" << std::endl;
			int moneyRack = promptMoneyRack();
			int shots[27];
			shootHoops(shots, moneyRack);
			scores[i] = scoreShots(shots);
		}
		printWinner(scores, numPlayers);
		delete[] scores;//free the array from memory
	}while(promptReplay());
}
