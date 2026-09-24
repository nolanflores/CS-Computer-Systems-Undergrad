#include "order.h"

order::order(){}

order::order(int num, std::string name, char size, int quantity){
    this->order_number = num;
    this->coffee_name = name;
    this->coffee_size = size;
    this->quantity = quantity;
}

int order::get_order_number() const{
    return this->order_number;
}

std::string order::get_coffee_name() const{
    return this->coffee_name;
}

char order::get_coffee_size() const{
    return this->coffee_size;
}

int order::get_quantity() const{
    return this->quantity;
}