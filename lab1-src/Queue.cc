#include <stdlib.h>
#include "Queue.h"

//
// Publicly available method to add an element to the queue
//
void Queue::enqueue(int val) {
	append(val);
}

int Queue::dequeue() {
	int ret = _head->_value;
	remove(ret);
	return ret;
}

Queue::Queue() { }

Queue::~Queue() { }
