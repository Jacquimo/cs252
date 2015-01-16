#include "List.h"

class Queue : List {
	void enqueue(Node* node);
	Node* dequeue(Node* node);

public:
	void enqueue(int val);
	int dequeue(int val);
	Queue();
	~Queue();
};
