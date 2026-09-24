#ifndef NODE_HPP
#define NODE_HPP

template<typename T>
struct node {
public:
	T val;				// the value that this node stores
	node<T>* next = nullptr;	// a pointer to the next node in the list
};

#endif
