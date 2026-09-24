#include "multdiv.hpp"
#include <iostream>


int main(){
    int row, col;
    std::cout << "Enter an integer greater than 0 for row: ";
    std::cin >> row;
    std::cout << "Enter an integer greater than 0 for col: ";
    std::cin >> col;
    multdiv_entry** table = create_table(row,col);
    print_table(table,row,col);
    delete_table(table,row);
    return 0;
}