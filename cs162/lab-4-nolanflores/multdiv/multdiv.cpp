#include "multdiv.hpp"
#include <iostream>


multdiv_entry** create_table(int row, int col){
    multdiv_entry** tables = new multdiv_entry*[row];
    for(int r = 0; r < row; r++){
        tables[r] = new multdiv_entry[col];
        for(int c = 0; c < col; c++){
            tables[r][c].mult = (c+1) * (r+1);
            tables[r][c].div = (100 * (c+1) / (r+1))/100.0;
        }
    }
    return tables;
}

void print_table(multdiv_entry** tables, int row, int col){
    std::cout << "Multiplication Table:" << std::endl;
    for(int r = 0; r < row; r++){
        for(int c = 0; c < col; c++){
            std::cout << tables[r][c].mult << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << "\nDivision Table:" << std::endl;
    for(int r = 0; r < row; r++){
        for(int c = 0; c < col; c++){
            std::cout << tables[r][c].div << "\t";
        }
        std::cout << std::endl;
    }
}


void delete_table(multdiv_entry** tables, int row){
    for(int r = 0; r < row; r++){
        delete[] tables[r];
    }
    delete[] tables;
}