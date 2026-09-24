#include <iostream>

void populate_multiplication_table(int table[12][12]) {
    for(int row = 0; row < 12; row++){
        for(int col = 0; col < 12; col++){
            table[row][col] = (row+1)*(col+1);
        }
    }
}

void print_multiplication_table(int table[12][12]){
    for(int row = 0; row < 12; row++){
        for(int col = 0; col < 12; col++){
            std::cout << table[row][col] << "\t";
        }
        std::cout << std::endl;
    }
}

int main(){
    int multiplication_table[12][12];
    populate_multiplication_table(multiplication_table);
    print_multiplication_table(multiplication_table);
    
    return 0;
}