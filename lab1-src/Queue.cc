#include <stdlib.h>
#include "Queue.h"

//
// Publicly available method to add an element to the queue
//
void Queue::enqueue(int val) {
	append(val);
}

int Queue::dequeue() {
	remove(_head->_value);
}

Queue::Queue() { }

Queue::~Queue() { }
