#include <iostream>
#include <string>

void foo(int x);

int main() {
	std::string name = "Nolan Flores";
	std::cout << "My name is: " << name << std::endl;
	foo(2);
	foo(4);
	foo(2 + 4);
	foo(2 - 4);
	foo(2 * 4);
	foo(2 / 4);
}


void foo(int x) {
	std::cout << "The function foo was passed the number: " << x << std::endl;
}
