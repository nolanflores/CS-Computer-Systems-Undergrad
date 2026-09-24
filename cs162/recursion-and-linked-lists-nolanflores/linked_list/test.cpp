/*
 * Author: Nolan Flores
 * Oregon State University
 * College of Engineering
 * Description: Test script for the implementation of the linked_list<int> class
 */

#include <iostream>

#include "linked_list.hpp"

/*********************************************************************
 ** Function: pause()
 ** Description: pauses program until the user presses enter
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 ********************************************************************/
void pause() {
        std::cout << "\n\nPress <enter> to continue...";
        std::cin.clear();
        std::cin.ignore(256, '\n');
}

/*********************************************************************
 ** Function: main()
 ** Description: tests linked list functionality
 ** Parameters: int, char const *
 ** Pre-Conditions: none
 ** Post-Conditions: none
 ********************************************************************/
int main(int argc, char const *argv[]) {

	// constuct default list
	linked_list<int> l;
	std::cout << "\n\nList successfully created!!\n\n";

	// test length of default (empty) list
	std::cout << "**********Test 1***********\n";
	std::cout << "Before adding nodes...\n";
	std::cout << "Testing get_length()\n";
	std::cout << "Expected: 0\n";
	std::cout << "Actual  : " << l.get_length() << "\n";
	if (l.get_length() == 0)
		std::cout << "Test 1 PASSED\n\n";
	else
		std::cout << "Test 1 FAILED\n\n";
	pause();

	// test push_front
	std::cout << "**********Test 2***********\n";
	std::cout << "Adding nodes...\n";
	std::cout << "Test 2.1: Testing push_front()\n";
	l.push_front(5);
	l.push_front(100);
	l.push_front(0);
	l.push_front(-8);
	l.push_front(16);
	std::cout << "Expected: 16 -8 0 100 5\n";
	std::cout << "Actual  :"; 
	l.print();
	std::cout << "Expected length: 5\n";
	std::cout << "Actual length  : " << l.get_length() << "\n";
	std::cout << "Test 2.1 completed.\n";
	pause();

	// test pop_front
	std::cout << "Removing nodes...\n";
	std::cout << "Test 2.2: Testing pop_front()\n";
	l.pop_front();
	l.pop_front();
	l.pop_front();
	std::cout << "Print list...\n";
	std::cout << "Expected: 100 5\n";
	std::cout << "Actual  :"; 
	l.print();
	std::cout << "Expected length: 2\n";
	std::cout << "Actual length  : " << l.get_length() << "\n";
	pause();

	// continue testing pop_front
	std::cout << "Continue removing...\n";
	l.pop_front();
	l.pop_front();
	l.pop_front(); //no more nodes, shouldn't remove anything 
	std::cout << "Print list...\n";
	std::cout << "Expected: \n";
	std::cout << "Actual  :"; 
	l.print();
	std::cout << "Expected length: 0\n";
	std::cout << "Actual length  : " << l.get_length() << "\n";
	std::cout << "Test 2.2 completed.\n";
	pause();

	// test push_back
	std::cout << "Adding nodes...\n";
	std::cout << "Test 2.3: Testing push_back()\n";
	l.push_back(5);
	l.push_back(1);
	l.push_back(2);
	l.push_back(7);
	l.push_back(7919);
	std::cout << "Expected: 5 1 2 7 7919\n";
	std::cout << "Actual  :"; 
	l.print();
	std::cout << "Expected length: 5\n";
	std::cout << "Actual length  : " << l.get_length() << "\n";
	std::cout << "Test 2.3 completed.\n";
	pause();

	// test pop_back
	std::cout << "Removing nodes...\n";
	std::cout << "Test 2.4: Testing pop_back()\n";
	l.pop_back();
	l.pop_back();
	std::cout << "Print list...\n";
	std::cout << "Expected: 5 1 2\n";
	std::cout << "Actual  :"; 
	l.print();
	std::cout << "Expected length: 3\n";
	std::cout << "Actual length  : " << l.get_length() << "\n";
	pause();

	// continue testing pop_back
	std::cout << "Continue removing...\n";
	l.pop_back();
	l.pop_back();
	l.pop_back();
	l.pop_back(); //no more nodes, shouldn't remove anything 
	std::cout << "Print list...\n";
	std::cout << "Expected: \n";
	std::cout << "Actual  :"; 
	l.print();
	std::cout << "Expected length: 0\n";
	std::cout << "Actual length  : " << l.get_length() << "\n";
	std::cout << "Test 2.4 completed.\n";
	pause();

	// insert nodes with push_front and push_back
	std::cout << "Adding nodes...\n";
	l.push_front(5);
	l.push_front(100);
	l.push_front(0);
	l.push_front(-8);
	l.push_front(16);
	l.push_back(5);
	l.push_back(1);
	l.push_back(2);
	l.push_back(7);
	l.push_back(7919);

	// test insert
	std::cout << "Test 2.5: Testing insert()\n";
	l.insert(11, 0);   // insert 11 at the front of the list
	l.insert(20, 100); // 100 is not a valid index, therefore 20 is not inserted
	l.insert(50, l.get_length()); // insert 50 at the end of the list
	l.insert(9, 5); // insert 9 at index 5 
	std::cout << "Expected: 11 16 -8 0 100 9 5 5 1 2 7 7919 50\n";
	std::cout << "Actual  :"; 
	l.print();
	std::cout << "Expected length: 13\n";
	std::cout << "Actual length  : " << l.get_length() << "\n";
	std::cout << "Test 2.5 completed.\n";
	pause();

	// test remove
	std::cout << "Removing nodes...\n";
	std::cout << "Test 2.6: Testing remove()\n";
	l.remove(9);   // remove the node with index 9 (value 2) of the list
	l.remove(100); // 100 is not a valid index, therefore no node is removed
	l.remove(l.get_length() - 1); // remove the last node (value 50) in the list
	l.remove(0); // remove the first node (11) in the list 
	std::cout << "Expected: 16 -8 0 100 9 5 5 1 7 7919\n";
	std::cout << "Actual  :"; 
	l.print();
	std::cout << "Expected length: 10\n";
	std::cout << "Actual length  : " << l.get_length() << "\n";
	std::cout << "Test 2.6 completed.\n";
	pause();

	// test sort_ascending
	std::cout << "**********Test 3***********\n";
	std::cout << "Sorting...\n";
	std::cout << "Test 3.1: Testing sort_ascending()\n";
	l.sort_ascending();
	std::cout << "Expected: -8 0 1 5 5 7 9 16 100 7919\n";
	std::cout << "Actual  :"; 
	l.print();
	std::cout << "Test 3.1 completed.\n";
	pause();

	// test sort_descending
	std::cout << "Test 3.2: Testing sort_descending()\n";
	l.sort_descending();
	std::cout << "Expected: 7919 100 16 9 7 5 5 1 0 -8\n";
	std::cout << "Actual  :"; 
	l.print();
	std::cout << "Test 3.2 completed.\n";
	pause();

	// test clear
	std::cout << "**********Test 4***********\n";
	std::cout << "Tesing clear()\n";
	l.clear();
	std::cout << "Expected length: 0\n";
	std::cout << "Actual length  : " << l.get_length() << "\n";
	if (l.get_length() == 0)
		std::cout << "Test 4 PASSED\n";
	else
		std::cout << "Test 4 FAILED\n";

	std::cout << "Run valgrind to check memory leaks/errors\n";

	return 0;
}
