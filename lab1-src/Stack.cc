#include "Stack.h"

void Stack::push(int val) {
	prepend(val);
}

int Stack::pop() {
	int ret = _head->_value;
	remove(ret);
	return ret;
}

Stack::Stack() { }
Stack::~Stack() { }
