#ifndef EXCLUDE
#include "List.h"
#endif

class Stack : public List {
public:
	void push(int val);
	int pop();
	Stack();
	~Stack();
};
