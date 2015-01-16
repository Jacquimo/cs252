#include "Queue.h"

//
// Publicly available method to add an element to the queue
//
void Queue::enqueue(int val) {
	append(val);
}

int Queue::dequeue(int val) {
	Node* node = _head;
	_head = _head->_next;
	int ret = node->._value;
	free(node);
	return ret;
}

Queue::Queue() {

}

Queue::~Queue() {

}
