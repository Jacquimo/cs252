#include "Queue.h"

//
// Publicly available method to add an element to the queue
//
void Queue::enqueue(int val) {
	enqueue(createNode(val));
}

//
// Private method that adds a node to the underlying List structure
//
void Queue::enqueue(Node* node) {
	append(node);
}
