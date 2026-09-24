/*CS162 - Lab 3 - Q1*/

#include <iostream>

void fooA(int* iptr){
	/*Print the value pointed to by iptr*/
	std::cout << *iptr << std::endl;
	/*Print the address stored in iptr*/
	std::cout << iptr << std::endl;
	/*Print the address of iptr itself*/
	std::cout << &iptr << std::endl;
}

int main(){
	/*declare an integer x and initialize it with value 0*/
	int x = 0;
	/*print the address of x*/
	std::cout << x << std::endl;
	/*Call fooA() with the address of x*/
	fooA(&x);
	/*print the value of x*/
	std::cout << x << std::endl;
	return 0;
}
