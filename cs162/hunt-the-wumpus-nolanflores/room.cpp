#include "room.hpp"
#include <iostream>

void Room::set_event(Event* e){
    if(this->room_event != nullptr){
        delete this->room_event;
    }
    this->room_event = e;
}

Event* Room::get_event() const{
    return this->room_event;
}

Room::~Room(){
    if(this->room_event != nullptr){
        delete this->room_event;
        this->room_event = nullptr;
    }
}