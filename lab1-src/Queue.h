#include "List.h"

class Queue : List {
	void enqueue(Node* node);
	void dequeue(Node* node);

public:
	void enqueue(int val);
	void dequeue(int val);
	Queue();
	~Queue();
};
