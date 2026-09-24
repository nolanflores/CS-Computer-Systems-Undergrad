#ifndef PAGE_HPP
#define PAGE_HPP

#include <string>

class page {
private:
	std::string content;
public:
	// Pages have empty content by default since strings
	// are empty by default
	page() = default;

	// Nondefault constructor to construct a page with specific
	// content
	page(std::string content);

	// Returns the page's content as a string (i.e., returns
	// this->content; this is a getter).
	std::string to_string() const;

	// Updates the page's content to match the given string
	// (i.e., sets this->content = content; this is a setter)
	void update_from_string(std::string content);
};

#endif
