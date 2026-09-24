#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

/*
 * Name: populate_table
 * Description: Populates a 10x10 coin toss table with trues (heads)
 * 		and falses (tails)
 * Parameters:
 * 		table (bool[][10]): Statically allocated 10x10 array of booleans
 * 			to represent coin toss results (true for heads, false for tails)
 * Post-conditions: table is populated with coin toss results
 */
void populate_table(bool table[][10]) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			bool coin_toss = (rand() % 2) == 1;
			table[i][j] = coin_toss;
		}
	}
}

/*
 * Name: print_table
 * Description: Prints a 10x10 coin toss table
 * Parameters:
 * 		table (bool[][10]): Statically allocated 10x10 array of booleans
 * 			to represent coin toss results (true for heads, false for tails)
 */
void print_table(bool table[][10]) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (table[i][j]) {
				// Heads; print H, followed by a tab
				std::cout << "H\t";
			} else {
				// Tails; print T, followed by a tab
				std::cout << "T\t";
			}
		}
		// End of the row. Print a new line
		std::cout << std::endl;
	}
}

int main()
{
	// Seed the PRNG with current time
	srand(time(nullptr));

	// Create array
	bool coin_toss_table[10][10];

	// Populate it
	populate_table(coin_toss_table);

	// Print it
	print_table(coin_toss_table);

	return 0;
}
