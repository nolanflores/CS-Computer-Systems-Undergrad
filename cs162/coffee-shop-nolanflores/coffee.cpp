#include "coffee.h"
#include <string>

coffee::coffee(){}

coffee::coffee(std::string name, double small, double medium, double large){
    this->name = name;
    this->small_cost = small;
    this->medium_cost = medium;
    this->large_cost = large;
}

void coffee::set_name(std::string name){
    this->name = name;
}

void coffee::set_small_cost(double cost){
    this->small_cost = cost;
}

void coffee::set_medium_cost(double cost){
    this->medium_cost = cost;
}

void coffee::set_large_cost(double cost){
    this->large_cost = cost;
}

std::string coffee::get_name() const{
    return this->name;
}

double coffee::get_small_cost() const{
    return this->small_cost;
}

double coffee::get_medium_cost() const{
    return this->medium_cost;
}

double coffee::get_large_cost() const{
    return this->large_cost;
}