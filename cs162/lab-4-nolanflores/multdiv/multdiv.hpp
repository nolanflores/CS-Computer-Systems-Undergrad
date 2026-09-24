#ifndef MULTDIV_HPP
#define MULTDIV_HPP

/*
 * stores products and quotients at an index of a 2d array
*/
struct multdiv_entry{
    int mult;
    float div;
};

/*
 * Creates 2d array of multdivs
*/
multdiv_entry** create_table(int row, int col);


/*
 * prints out 2d array of multdivs
*/
void print_table(multdiv_entry** tables, int row, int col);


/*
 * Frees dynamic 2d array from memory
*/
void delete_table(multdiv_entry** tables, int row);


#endif