#include <iostream>

#include "printing.hpp"

void print_page(const page& page_to_print) {
	std::cout << page_to_print.to_string() << std::endl;
}

void print_book(const book& book_to_print) {
	// Print book's name and author
	std::cout << book_to_print.get_name() << ", by " <<
		book_to_print.get_author() << std::endl;

	// If book is empty, return immediately, printing nothing else
	if (book_to_print.size() == 0) {
		return;
	}

	// Print content prefix for first page
	std::cout << "_________________________" << std::endl;
	for (int i = 0; i < book_to_print.size(); i++) {
		// Print rest of content header (page number)
		std::cout << "Page " << (i + 1) << std::endl;
		std::cout << "_________________________" << std::endl;

		// Print the page's content
		print_page(book_to_print.get_page(i));

		// If there's another page up next, print its content prefix
		if (i < book_to_print.size() - 1) {
			std::cout << std::endl;
			std::cout << "_________________________" << std::endl;
		}
	}
}

// TODO Part 2: Define print_textbook
void print_textbook(const textbook& book_to_print){
	// Print book's name and author
	std::cout << book_to_print.get_name() << ", by " <<
		book_to_print.get_author() << std::endl;
	
	//print book's coauthors
	std::cout << "Coauthored by ";
	for(int i = 0; i < book_to_print.get_num_coauthors(); i++){
		std::cout << book_to_print.get_coauthor(i);
		if(i < book_to_print.get_num_coauthors()-1){
			std::cout << ", ";
		}
	}
	std::cout << std::endl;

	// Print content prefix for first page
	std::cout << "_________________________" << std::endl;
	for (int i = 0; i < book_to_print.size(); i++) {
		// Print rest of content header (page number)
		std::cout << "Page " << (i + 1) << std::endl;
		std::cout << "_________________________" << std::endl;

		// Print the page's content
		print_page(book_to_print.get_page(i));

		// If there's another page up next, print its content prefix
		if (i < book_to_print.size() - 1) {
			std::cout << std::endl;
			std::cout << "_________________________" << std::endl;
		}
	}
}