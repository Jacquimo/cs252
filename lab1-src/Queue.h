#ifndef EXCLUDE
#include "List.h"
#endif

class Queue : public List {
public:
	void enqueue(int val);
	int dequeue();
	Queue();
	~Queue();
};
