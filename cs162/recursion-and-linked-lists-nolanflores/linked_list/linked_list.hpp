#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include "node.hpp"
#include <iostream>

template<typename T>
class linked_list {
private:
	int length = 0;			// the number of nodes contained in the list.
	node<T>* head = nullptr;	// a pointer to the first node in the list.
public:
	// Empty default constructor
	linked_list() = default;

	// Copy constructor
	linked_list(const linked_list<T>& other){
		this->length = other.length;
		node<T>* other_current = other.head;
		node<T>** current = &this->head;
		while(other_current != nullptr){
			*current = new node<T>;
			(*current)->val = other_current->val;
			current = &(*current)->next;
			other_current = other_current->next;
		}
	}


	// Assignment operator overload
	void operator=(const linked_list<T>& other){
		if(this == &other){
			return;
		}
		node<T>* other_current = other.head;
		node<T>** current = &this->head;
		while(other_current != nullptr){
			if(*current == nullptr){
				*current = new node<T>;
			}
			(*current)->val = other_current->val;
			other_current = other_current->next;
			current = &(*current)->next;
		}
		node<T>* temp = *current;
		*current = nullptr;
		while(temp != nullptr){
			node<T>* next_temp = temp->next;
			delete temp;
			temp = next_temp;
			
		}
		this->length = other.length;
	}

	// Destructor
	~linked_list(){
		this->clear();
	}

	/*********************************************************************
	 ** Function: get_length()
	 ** Description: Returns length of list.
	 ** Returns (int): Length of list (# of nodes).
	 ********************************************************************/
	int get_length(){
		return this->length;
	}

	/*********************************************************************
	 ** Function: print()
	 ** Description: Prints all values in the list.
	 ********************************************************************/
	void print(){
		node<T>* current = this->head;
		while(current != nullptr){
			std::cout << " " << current->val;
			current = current->next;
		}
		std::cout << std::endl;
	}

	/*********************************************************************
	 ** Function: clear()
	 ** Description: Removes all nodes from list (and deletes them from the
	 ** 	heap).
	 ** Post-Conditions: length = 0, head = nullptr.
	 ********************************************************************/
	void clear(){
		node<T>* current = this->head;
		while(current != nullptr){
			node<T>* temp = current;
			current = current->next;
			delete temp;
		}
		this->head = nullptr;
		this->length = 0;
	}

	/*********************************************************************
	 ** Function: push_front()
	 ** Description: Inserts a new value at the front (beginning) of the list
	 		in a new node.
	 ** Parameters: int - value being added to list.
	 ********************************************************************/
	void push_front(T value){
		node<T>* new_head = new node<T>;
		new_head->val = value;
		new_head->next = this->head;
		this->head = new_head;
		this->length++;
	}

	/*********************************************************************
	 ** Function: push_back()
	 ** Description: Insert a new value at the back (end) of the list in a
	 		new node.
	 ** Parameters: int - value being added to list.
	 ********************************************************************/
	void push_back(T value){
		this->insert(value, this->length);
	}

	/*********************************************************************
	 ** Function: insert()
	 ** Description: insert a new value at a specified index.
	 ** Parameters: int value - value being added to list.
	                int index - index of where element is being added.
	 ** Post-Conditions: given value inserted at given index in a new node, and
	 		all subsequent elements shifted over to make room for it. Length
			should be one greater than before.
	 ********************************************************************/
	void insert(T value, int index){
		if(index == 0){
			this->push_front(value);
		}else{
			node<T>* current = this->head;
			for(int i = 0; i < index-1; i++){
				if(current == nullptr){
					return;
				}
				current = current->next;
			}
			node<T>* temp = current->next;
			current->next = new node<T>;
			current->next->val = value;
			current->next->next = temp;
			this->length++;
		}
	}

	/*********************************************************************
	 ** Function: pop_front()
	 ** Description: Remove node at the front (beginning) of the list.
	 ** Post-Conditions: Node at the front of the list is removed from the
	 		list and deleted from the heap
	 ********************************************************************/
	void pop_front(){
		if(this->head != nullptr){
			node<T>* temp = this->head;
			this->head = this->head->next;
			delete temp;
			this->length--;
		}
	}

	/*********************************************************************
	 ** Function: pop_back()
	 ** Description: Remove node at the back (end) of the list.
	 ** Post-Conditions: Node at the back of the list is removed from the
	 		list and deleted from the heap
	 ********************************************************************/
	void pop_back(){
		this->remove(this->length-1);
	}

	/*********************************************************************
	 ** Function: remove()
	 ** Description: Remove node at the given index.
	 ** Parameters: int - index of where node is being removed.
	 ** Post-Conditions: Node at given index is removed. Subsequent nodes
	 		are shifted over to accommodate. Length of list should be one
			less than before.
	 ********************************************************************/
	void remove(int index){
		if(index == 0){
			this->pop_front();
		}else{
			node<T>* current = this->head;
			for(int i = 0; i < index-1; i++){
				if(current == nullptr){
					return;
				}
				current = current->next;
			}
			if(current != nullptr && current->next != nullptr){
				node<T>* temp = current->next;
				current->next = current->next->next;
				delete temp;
				this->length--;
			}
		}
	}

	/*********************************************************************
	 ** Function: sort_ascending()
	 ** Description: Sorts list in ascending order.
	 ** Post-Conditions: List's nodes are rearranged to be sorted in
	 		ascending order of their respective values.
	 ********************************************************************/
	void sort_ascending(){
		this->head = this->merge_sort(this->head, this->length);
	}

	/*********************************************************************
	 ** Function: sort_descending()
	 ** Description: Sorts list in descending order.
	 ** Post-Conditions: List's nodes are rearranged to be sorted in
	 		descending order of their respective values.
	 ********************************************************************/
	void sort_descending(){
		this->head = this->recursive_selection_sort(this->head);
	}

private:
	/*********************************************************************
	 ** Function: merge_sort()
	 ** Description: Splits a linked list into two halves, sorts each half
	 		in ascending order, then merges the two sorted halves back together.
	 ** Parameters: node<T>* - pointer to the head of the list to be sorted.
	 ** Returns: node<T>* - pointer to the head of the sorted list.
	 ********************************************************************/
	node<T>* merge_sort(node<T>* head, int len){
		int mid = len/2;
		if(mid == 0){
			return head;
		}
		node<T>* first = head;
		node<T>* second = head;
		for(int i = 0; i < mid-1; i++){
			second = second->next;
		}
		node<T>* temp = second;//set the tail of the first half to nullptr
		second = second->next;
		temp->next = nullptr;
		first = this->merge_sort(first, mid);
		second = this->merge_sort(second, len-mid);
		return this->merge(first, second);
	}

	/*********************************************************************
	 ** Function: merge()
	 ** Description: Merges two sorted lists into one ascending list.
	 ** Parameters: node<T>* - pointer to the head of the first list.
	                node<T>* - pointer to the head of the second list.
	 ** Returns: node<T>* - pointer to the head of the merged list.
	 ********************************************************************/
	node<T>* merge(node<T>* first, node<T>* second){
		node<T>* head = nullptr;
		node<T>** current = &head;
		while(first != nullptr && second != nullptr){
			if(first->val < second->val){
				*current = first;
				first = first->next;
			}else{
				*current = second;
				second = second->next;
			}
			current = &(*current)->next;
		}
		while(first != nullptr){
			*current = first;
			first = first->next;
			current = &(*current)->next;
		}
		while(second != nullptr){
			*current = second;
			second = second->next;
			current = &(*current)->next;
		}
		return head;
	}

	node<T>* recursive_selection_sort(node<T>* head){
		if(head == nullptr || head->next == nullptr){
			return head;
		}
		node<T>* max = head;
		node<T>* prev = nullptr;
		node<T>* current = head;
		while(current->next != nullptr){
			if(current->next->val > max->val){
				max = current->next;
				prev = current;
			}
			current = current->next;
		}
		if(prev != nullptr){
			prev->next = head;
			node<T>* temp = max->next;
			max->next = head->next;
			head->next = temp;
			head = max;
		}
		head->next = this->recursive_selection_sort(head->next);
		return head;
	}
};

#endif
