#include "person.hpp"
#include <iostream>
// TODO You may need to define the appropriate constructors and destructor here



person::person(){
    this->num_pets = 0;
    this->pets = nullptr;
}


person::person(int num_pets){
    this->num_pets = num_pets;
    this->pets = new dog[num_pets];
}

person::~person(){
    if(0 < this->num_pets){
        delete[] this->pets;
    }
}