#include <iostream>


/* Takes an int argument representing the size of the array,
 * and returns the base address of the dynamically allocated
 * array
*/
int* create_array1(int size){
    int* array = new int[size];
    return array;
}


/* Takes a reference to an int pointer, and an int argument
 * representing the size of the array. Stores the base address
 * of the dynamically allocated array in the int pointer
 * that’s supplied via the reference parameter
*/
void create_array2(int *& array, int size){
    array = new int[size];
}


/* Takes a pointer to an int pointer, and an int argument
 * representing the size of the array. Stores the base address
 * of the dynamically allocated array in the int pointer
 * that’s supplied via the pointer parameter (i.e., stores the
 * base address in the int pointer that the int double-pointer
 * parameter points to)
*/
void create_array3 (int** array, int size){
    *array = new int[size];
}


int main(){
    int size;
    std::cout << "Enter a size: ";
    std::cin >> size;

    int* array1 = create_array1(size);

    int* array2 = nullptr;
    create_array2(array2,size);

    int* array3 = nullptr;
    create_array3(&array3,size);

    delete[] array1;
    delete[] array2;
    delete[] array3;
    return 0;
}