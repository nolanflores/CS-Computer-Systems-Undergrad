#include "page.hpp"

page::page(std::string content) : content(content) {}

std::string page::to_string() const {
	return this->content;
}

void page::update_from_string(std::string content) {
	this->content = content;
}
