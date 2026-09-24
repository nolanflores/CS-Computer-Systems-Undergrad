#include "shop.h"
#include "coffee.h"
#include <iostream>

shop::shop(){
    this->num_orders = 0;
    this->orders = nullptr;
}

shop::shop(const shop& s){
    this->phone = s.phone;
    this->address = s.address;
    this->revenue = s.revenue;
    this->num_orders = s.num_orders;
    this->orders = new order[this->num_orders];
    for(int i = 0; i < this->num_orders; i++){
        this->orders[i] = s.orders[i];
    }
}

void shop::operator=(const shop& s){
    if(this == &s){
        return;
    }
    if(this->orders != nullptr){
        delete[] this->orders;
    }
    this->phone = s.phone;
    this->address = s.address;
    this->revenue = s.revenue;
    this->num_orders = s.num_orders;
    this->orders = new order[this->num_orders];
    for(int i = 0; i < this->num_orders; i++){
        this->orders[i] = s.orders[i];
    }
}

shop::~shop(){
    if(this->orders != nullptr){
        delete[] this->orders;
    }
}

void shop::add_coffee_to_menu(const coffee& c){
    this->m.add_coffee(c);
}

void shop::add_order(const order& o){
    order* new_orders = new order[this->num_orders+1];
    for(int i = 0; i < this->num_orders; i++){
        new_orders[i] = this->orders[i];
    }
    new_orders[this->num_orders++] = o;
    delete[] this->orders;
    this->orders = new_orders;
}

void shop::populate_from_file(std::ifstream& file){
    std::getline(file, this->phone);
    std::getline(file, this->address);
}

menu& shop::get_menu(){
    return this->m;
}

void shop::print_shop_info() const{
    std::cout << "\nAddress: " << this->address << std::endl;
    std::cout << "Phone: " << this->phone << std::endl;
    std::cout << "\nHere is out menu:" << std::endl;
    this->m.print_coffee_prices();
    std::cout << "\nOrder info:" << std::endl;
    if(this->orders != nullptr){
        for(int i = 0; i < this->num_orders; i++){
            std::cout << this->orders[i].get_order_number();
            std::cout << " " << this->orders[i].get_coffee_name();
            std::cout << " " << this->orders[i].get_coffee_size();
            std::cout << " " << this->orders[i].get_quantity() << std::endl;
        }
    }else{
        std::cout << "(No orders to display)" << std::endl;
    }
}

void shop::make_order(){
    int index, quantity;
    do{//this could probably go in another function, but that would over complicate this
        std::cout << "Which of the drinks above from our menu would you like to order? Enter 1-" << m.get_num_coffees() << ": ";
        std::cin >> index;
        if(index < 1 || index > m.get_num_coffees()){
            std::cout << "Not a valid choice." << std::endl;
        }
    }while(index < 1 || index > m.get_num_coffees());
    coffee c = m.get_coffees()[index-1];
    char size;
    do{
        std::cout << "Enter the size: s-small, m-medium, l-large: ";
        std::cin >> size;
    }while(size != 's' && size != 'm' && size != 'l');
    std::cout << "Enter the quantity: ";
    std::cin >> quantity;
    if(size == 's'){
        this->revenue += quantity * c.get_small_cost();
    }else if(size == 'm'){
        this->revenue += quantity * c.get_medium_cost();
    }else{
        this->revenue += quantity * c.get_large_cost();
    }
    order o(this->num_orders+1,c.get_name(),size,quantity);
    add_order(o);
}