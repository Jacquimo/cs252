//
// Implement the List class
//

#include <stdio.h>
#include "List.h"
#include <stdlib.h>

Node* createNode(int);
Node* createNode(int, Node*);

//
// Inserts a new element with value "val" in
// ascending order.
//
void
List::insertSorted( int val )
{
	Node* insert = createNode(val);
	// Check starting conditions and check for nulls
	if (_head == NULL || insert->_value < _head->_value) {
		prepend(val);
		free(insert);
		return;
	}

	Node* first = _head;
	Node* next = first->_next;
	
	// This assumes that the list is already in sorted order
	while (next != NULL) {
		if (insert->_value < next->_value) {
			insert->_next = next;
			first->_next = insert;
			return;
		}

		first = next;
		next = first->_next;
	}

	// If we have gone through all of the elements, just add this to the end
	append(val);
	free(insert); // need this line, as append will allocate its own memory
}

//
// Inserts a new element with value "val" at
// the end of the list.
//
void
List::append( int val )
{
	Node* insert = createNode(val);

	if (_head == NULL) {
		_head = insert;
		tail = insert;
		return;
	}
	// Because of the above statement, "tail" will never be NULL 
	tail->_next = insert;
	tail = insert;
}

//
// Inserts a new element with value "val" at
// the beginning of the list.
//
void
List::prepend( int val )
{
	Node* insert = createNode(val, _head);
	_head = insert;
	if (tail == NULL)
		tail = insert;
}

// Removes an element with value "val" from List
// Returns 0 if succeeds or -1 if it fails
int 
List::remove( int val )
{
	if (_head == NULL)
		return -1;
	
	// Check if _head is the node
	if (_head->_value == val) {
		Node* rem = _head;
		_head = _head->_next;
		free(rem);
		return 0;
	}

	Node* first = _head;
	Node* next = first->_next;

	// Loop through until "next" becomes the tail element
	while (next->_next != NULL) {
		if (next->_value == val) {
			Node* rem = next;
			first->_next = next->_next;
			free(rem);
			return 0;
		}

		first = next;
		next = first->_next;
	}

	// Check the tail element
	if (tail->_value == val) {
		Node* rem = tail;
		tail = first;
		free(rem);
		tail->_next = NULL;
		return 0;
	}

	return -1;
}

// Prints The elements in the list. 
void
List::print()
{
	Node* node = _head;
	printf("[");
	while (node != NULL) {
		printf("%d, ", node->_value);
		node = node->_next;
	}
	printf("]\n");
}

//
// Returns 0 if "value" is in the list or -1 otherwise.
//
int
List::lookup(int val)
{
	Node* first = _head;
	while (first != NULL) {
		if (first->_value == val)
			return 0;
		first = first->_next;
	}

	return -1;
}

//
// List constructor
//
List::List()
{
	_head = NULL;
	tail = NULL;
}

//
// List destructor: delete all list elements, if any.
//
List::~List()
{
	Node* node = _head;
	while (node != NULL) {
		Node* temp = node->_next;
		free(node);
		node = temp;
	}
}

Node* createNode(int val) {
	return createNode(val, NULL);
}

Node* createNode(int val, Node* child) {
	Node* insert = (Node*)malloc(sizeof(Node));
	insert->_value = val;
	insert->_next = child;

	return insert;
}

