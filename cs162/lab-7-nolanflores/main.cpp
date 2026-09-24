#include <iostream>

#include "book.hpp"
#include "printing.hpp"
#include "textbook.hpp"

int main() {
	// DO NOT MODIFY THE BELOW CODE

	// The below content is attributed to Dr. Seuss from his famous
	// children's book, "The Cat in the Hat".
	page p1("The sun did not shine, it was too wet to play, so we sat in the house all that cold, cold wet day.");
	page p2("I sat there with Sally. We sat there, we two [...]");
	book the_cat_in_the_hat("The Cat in the hat", "Dr. Seuss", 2);
	the_cat_in_the_hat.set_page(0, p1);
	the_cat_in_the_hat.set_page(1, p2);

	// Print the book's content via print_book() from printing.hpp
	print_book(the_cat_in_the_hat);

	// Create a copy of the book via copy constructor
	book copy = the_cat_in_the_hat;

	// Create another copy via assignment operator overload
	book another_copy("Some book", "Some author", 100);
	another_copy = the_cat_in_the_hat; // Use AOO to copy
	
	std::cout << std::endl << std::endl;

	// TODO Part 2: Create a textbook and print its data
	p1 = page("The fundamental theorem of calculus is a theorem that links the concept of...");
	p2 = page("An integral is the continuous analog of a sum, which is used to calculate areas, volumes, and their generalizations");
	textbook intro_to_calc("Introduction to Calculus", "John Calculus", 2, 2);
	intro_to_calc.set_coauthor(0,"Nolan Flores");
	intro_to_calc.set_coauthor(1,"Alex Guyer");
	intro_to_calc.set_page(0,p1);
	intro_to_calc.set_page(1,p2);

	//Print the textbook
	print_textbook(intro_to_calc);

	// Create a copy of the textbook via copy constructor
	textbook copy2 = intro_to_calc;

	// Create another copy via assignment operator overload
	textbook another_copy2("Some book", "Some author", 100, 100);
	another_copy2 = intro_to_calc; // Use AOO to copy
}
