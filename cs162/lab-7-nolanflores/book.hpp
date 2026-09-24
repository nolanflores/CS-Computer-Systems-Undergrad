#ifndef BOOK_HPP
#define BOOK_HPP

#include "page.hpp"

class book {
private:
	std::string name;
	std::string author;
	page* pages = nullptr;
	int num_pages = 0;
public:
	book(const std::string& name, const std::string& author, int num_pages);

	// Getter for name
	std::string get_name() const;

	// Getter for author
	std::string get_author() const;

	// Return the number of pages in the book
	int size() const;

	// Setter for page at given index. Prints an
	// error if the index is out of bounds (throwing
	// an exception would be far better, but we haven't
	// covered exceptions)
	void set_page(int index, const page& page_to_set);

	// Getter for page at given index. Prints an
	// error and returns an empty page if the index is out
	// of bounds (throwing an exception would be far better,
	// but we haven't covered exceptions)
	page get_page(int index) const;

	// TODO Part 3: Big 3
	book(const book& b);

	void operator=(const book& b);

	~book();
};

#endif
