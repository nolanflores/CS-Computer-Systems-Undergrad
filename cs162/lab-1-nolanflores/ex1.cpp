#include <iostream>

void function (int x[], int n) {//this is a bubble sort
	int i, t, j = n, s = 1;//n is the size of the array
	while (s) {//run until no changes are made to the array
		s = 0;//0 indicates no change
		for (i = 1; i < j; i++) {//loop from start to last unsorted index j
			if (x[i] < x[i - 1]) {//front index is bigger
				t = x[i];
				x[i] = x[i - 1];//swap the indexs
				x[i - 1] = t;
				s = 1;//1 indicates a change has been made
			}
		}
		j--;//each iteration, one more index at the end is sorted
	}
}
 
int main () {
	int x[] = {15, 56, 12, -21, 1, 659, 3, 83, 51, 3, 135, 0};
	int n = sizeof(x) / sizeof(x[0]);//size of the array
	int i;
	for (i = 0; i < n; i++) {//loop through and print the array
		std::cout << x[i] << " ";
	}
	std::cout << std::endl;
	
	function(x, n);//sort the array, x is passed by reference
	
	for (i = 0; i < n; i++) {//loop through and print the sorted array
		std::cout << x[i] << " ";
	}
	std::cout << std::endl;
	
	return 0;
}
