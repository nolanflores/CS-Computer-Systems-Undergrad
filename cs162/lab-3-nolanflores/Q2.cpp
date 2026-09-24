/*CS 162 - Lab 3 - Q.2*/

#include <iostream>

int foo(int* a, int& b, int c){
	/*Set a to 2 times its original value*/
	*a *= 2;
	/*Set b to half of its original value*/
	b /= 2;
	/*Assign a + b to c*/
	c = *a + b;
	/*Return c*/
	return c;
}

int main(){
	/*Declare three integers x, y, and z, and initialize them to 7, 8, 9 respectively*/
	int x = 7, y = 8, z = 9;
	/*Print the values of x, y and z*/
	std::cout << "x = " << x << std::endl;
	std::cout << "y = " << y << std::endl;
	std::cout << "z = " << z << std::endl;
	/*Call foo() appropriately, passing x, y, and z as arguments by pointer, reference, and value*/
	int f = foo(&x,y,z);
	/*Print the value returned by foo*/
	std::cout << "foo = " << f << std::endl;
	/*Print the values of x, y and z again*/
	std::cout << "x = " << x << std::endl;
	std::cout << "y = " << y << std::endl;
	std::cout << "z = " << z << std::endl;
	/*Is the return value different than the value of z?  Why? 
	
		the return value does not equal z, because z is passed by value.
		A new variable, c, is created with the same value as z and modified.
		But c and z do not share the same memory adress
	*/
}
