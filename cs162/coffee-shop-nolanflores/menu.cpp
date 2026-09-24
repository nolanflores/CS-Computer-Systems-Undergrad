#include "menu.h"

#include <fstream>
#include <iostream>
#include <string>

menu::menu(){
    this->num_coffees = 0;
    this->coffees = nullptr;
}

menu::menu(const menu& m){
    this->num_coffees = m.num_coffees;
    this->coffees = new coffee[this->num_coffees];
    for(int i = 0; i < this->num_coffees; i++){
        this->coffees[i] = m.coffees[i];
    }
}

void menu::operator=(const menu& m){
    if(this == &m){
        return;
    }
    if(this->coffees != nullptr){
        delete[] this->coffees;
    }
    this->num_coffees = m.num_coffees;
    this->coffees = new coffee[this->num_coffees];
    for(int i = 0; i < this->num_coffees; i++){
        this->coffees[i] = m.coffees[i];
    }
}

menu::~menu(){
    if(this->coffees != nullptr){
        delete[] this->coffees;
    }
}

void menu::populate_from_file(std::ifstream& file){
    if(this->coffees != nullptr){
        delete[] this->coffees;
    }
    file >> this->num_coffees;
    this->coffees = new coffee[this->num_coffees];
    for(int i = 0; i < this->num_coffees; i++){
        std::string name;
        double small, medium, large;
        file >> name >> small >> medium >> large;
        this->coffees[i].set_name(name);
        this->coffees[i].set_small_cost(small);
        this->coffees[i].set_medium_cost(medium);
        this->coffees[i].set_large_cost(large);
    }
}

void menu::write_to_file(std::ofstream& file){
    file << this->num_coffees << std::endl;
    for(int i = 0; i < this->num_coffees; i++){
        coffee c = this->coffees[i];
        file << c.get_name() << " ";
        file << c.get_small_cost() << " ";
        file << c.get_medium_cost() << " ";
        file << c.get_large_cost() << std::endl; 
    }
}

void menu::print_coffee_prices() const{
    for(int i = 0; i < this->num_coffees; i++){
        coffee c = this->coffees[i];
        std::cout << i+1 << ". " << c.get_name() << std::endl;
        std::cout << "\tSmall - " << c.get_small_cost() << std::endl;
        std::cout << "\tMedium - " << c.get_medium_cost() << std::endl;
        std::cout << "\tLarge - " << c.get_large_cost() << std::endl;
    }
}

void menu::add_coffee(const coffee &c){
    coffee* new_coffees = new coffee[this->num_coffees+1];
    for(int i = 0; i < this->num_coffees; i++){
        new_coffees[i] = this->coffees[i];//shallow copy
    }
    new_coffees[this->num_coffees++] = c;
    delete[] this->coffees;
    this->coffees = new_coffees;
}

void menu::print_coffees() const{
    for(int i = 0; i < this->num_coffees; i++){
        std::cout << i+1 << ". " << this->coffees[i].get_name() << std::endl;
    }
}

void menu::remove_coffee(){// I would rather die than spend the time splitting this function
    if(this->num_coffees <= 0 || this->coffees == nullptr){
        std::cout << "There are no coffees on the menu." << std::endl;
        return;
    }
    int index;
    do{//this could probably go in another function, but that would over complicate this
        std::cout << "Which of the drinks above from our menu would you like to remove? Enter 1-" << this->num_coffees << ": ";
        std::cin >> index;
        if(index < 1 || index > this->num_coffees){
            std::cout << "Not a valid choice." << std::endl;
        }
    }while(index < 1 || index > this->num_coffees);
    coffee* new_coffees = new coffee[this->num_coffees-1];
    for(int i = 0; i < index-1; i++){
        new_coffees[i] = this->coffees[i];
    }
    for(int i = index; i < this->num_coffees; i++){
        new_coffees[i-1] = this->coffees[i];
    }
    delete[] this->coffees;
    this->coffees = new_coffees;
    this->num_coffees--;
}

void menu::search_by_name(const std::string name) const{
    std::cout << "\nResults:" << std::endl;
    for(int i = 0; i < this->num_coffees; i++){
        if(this->coffees[i].get_name() == name){
            std::cout << "1. " << name << std::endl;
            std::cout << "Small: " << this->coffees[i].get_small_cost() << std::endl;
            std::cout << "Medium: " << this->coffees[i].get_medium_cost() << std::endl;
            std::cout << "Large: " << this->coffees[i].get_large_cost() << std::endl;
            return;
        }
    }
    std::cout << "No coffee with the name \"" << name << "\" was found." << std::endl;
}

void menu::search_by_price(const double price) const{
    std::cout << std::endl;
    int count = 1;
    for(int i = 0; i < this->num_coffees; i++){
        coffee c = this->coffees[i];
        if(c.get_small_cost() <= price || c.get_medium_cost() <= price || c.get_large_cost() <= price){
            std::cout << count++ << ". " << c.get_name() << std::endl;
            if(c.get_small_cost() <= price)
                std::cout << "\tSmall - " << c.get_small_cost() << std::endl;
            if(c.get_medium_cost() <= price)
                std::cout << "\tMedium - " << c.get_medium_cost() << std::endl;
            if(c.get_large_cost() <= price)
                std::cout << "\tLarge - " << c.get_large_cost() << std::endl;
        }
    }
    std::cout << std::endl;
}

int menu::get_num_coffees() const{
    return this->num_coffees;
}

coffee* menu::get_coffees() const{
    return this->coffees;
}