#include <iostream>

#include "book.hpp"

book::book(const std::string& name, const std::string& author, int num_pages) :
		name(name),
		author(author),
		num_pages(num_pages) {
	if (num_pages > 0) {
		this->pages = new page[num_pages];
	} else {
		this->pages = nullptr;
	}
}

std::string book::get_name() const {
	return this->name;
}

std::string book::get_author() const {
	return this->author;
}

int book::size() const {
	return this->num_pages;
}

void book::set_page(int index, const page& page_to_set) {
	if (index < 0 || index >= this->num_pages) {
		std::cout << "Error! index out of bounds in book::set_page!" <<
			std::endl;
		return;
	}

	this->pages[index] = page_to_set;
}

page book::get_page(int index) const {
	if (index < 0 || index >= this->num_pages) {
		std::cout << "Error! index out of bounds in book::get_page!" <<
			std::endl;
		
		page empty_page;
		return empty_page;
	}

	return this->pages[index];
}

// TODO Part 3: Big 3
book::book(const book& b) :
		name(b.name),
		author(b.author),
		num_pages(b.num_pages){
	if(this->num_pages > 0){
		this->pages = new page[num_pages];
		for(int i = 0; i < this->num_pages; i++){
			this->pages[i] = b.get_page(i);
		}
	}else{
		this->pages = nullptr;
	}
}

void book::operator=(const book& b){
	if(this == &b){
		return;
	}
	if(this->pages != nullptr){
		delete[] this->pages;
	}
	this->name = b.name;
	this->author = b.author;
	this->num_pages = b.num_pages;
	if(this->num_pages > 0){
		this->pages = new page[this->num_pages];
		for(int i = 0; i < this->num_pages; i++){
			this->pages[i] = b.get_page(i);
		}
	}else{
		this->pages = nullptr;
	}
}

book::~book(){
	if(this->pages != nullptr){
		delete[] this->pages;
	}
}