#include <iostream>
#include <string>

void get_sentence(std::string &s) {
	std::cout << "Enter a sentence: ";
	getline(std::cin, s);
}

int main() {
	std::string sentence;

	get_sentence(sentence);
	std::cout << sentence << std::endl;

	return 0;
}
