// This is for Lab 2 Part 2: Array exercise

#include <iostream>

// Function to populate the array elements
void populate_array(int array[], int size){
	for(int i = 0; i < size; i++){
		array[i] = (rand()%100)+1;
	}
}

// Hint: create another function (or three) to compute the statistics
void print_statistics(int array[], int size){
	int sum = 0, max = 0, min = 100;
	for(int i = 0; i < size; i++){
		sum += array[i];
		if(array[i] < min){
			min = array[i];
		}else if(array[i] > max){
			max = array[i];
		}
	}
	std::cout << "The sum is: " << sum << std::endl;
	std::cout << "The max is: " << max << std::endl;
	std::cout << "The min is: " << min << std::endl;
}

int prompt_array_size(){
	while(true){
		std::cout << "Enter a size between 5 and 50: ";
		int size;
		std::cin >> size;
		if(size >= 5 && size <= 50)
			return size;
		std::cout << "Not a valid size, try again." << std::endl;
	}
}

bool prompt_repeat(){
	while(true){
		std::cout << "Would you like to try again? (1 for yes, 0 for no): ";
		int response;
		std::cin >> response;
		if(response == 1 || response == 0)
			return response;
		std::cout << "Not a valid input, try again." << std::endl;
	}
}

int main()
{
	srand(time(nullptr));
	do{
		int size = prompt_array_size();
		int *array = new int[size];
		populate_array(array,size);
		print_statistics(array,size);
		delete[] array;
	}while(prompt_repeat());
	return 0;
}
