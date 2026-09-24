#include "textbook.hpp"
#include <iostream>

textbook::textbook(const std::string& name, const std::string& author, int num_pages, int num_coauthors) : 
        book(name,author,num_pages),
        num_coauthors(num_coauthors){
    if(this->num_coauthors > 0){
        this->coauthors = new std::string[this->num_coauthors];
    }else{
        this->coauthors = nullptr;
    }
}

int textbook::get_num_coauthors() const{
    return this->num_coauthors;
}

std::string textbook::get_coauthor(int index) const{
    if (index < 0 || index >= this->num_coauthors) {
		std::cout << "Error! index out of bounds in textbook::get_coauthor!" << std::endl;
		return "";
	}
	return this->coauthors[index];
}

void textbook::set_coauthor(int index, const std::string& coauthor){
    if (index < 0 || index >= this->num_coauthors) {
		std::cout << "Error! index out of bounds in textbook::set_coauthor!" << std::endl;
		return;
	}
	this->coauthors[index] = coauthor;
}

textbook::textbook(const textbook& t) :
        book(t),
        num_coauthors(t.num_coauthors){
    if(this->num_coauthors > 0){
        this->coauthors = new std::string[this->num_coauthors];
        for(int i = 0; i < this->num_coauthors; i++){
            this->coauthors[i] = t.get_coauthor(i);
        }
    }else{
        this->coauthors = nullptr;
    }
}

void textbook::operator=(const textbook& t){
    if(this == &t){
        return;
    }
    book::operator=(t);
    this->num_coauthors = t.num_coauthors;
    if(this->coauthors != nullptr){
        delete[] this->coauthors;
    }
    if(this->num_coauthors > 0){
		this->coauthors = new std::string[this->num_coauthors];
		for(int i = 0; i < this->num_coauthors; i++){
			this->coauthors[i] = t.get_coauthor(i);
		}
	}else{
		this->coauthors = nullptr;
	}
}

textbook::~textbook(){
    if(this->coauthors != nullptr){
        delete[] this->coauthors;
    }
}