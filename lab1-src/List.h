//an item in the list
typedef struct ListNode {
  int _value;
  ListNode * _next;
} Node;

class List {
public:
  //Head of list
  ListNode * _head;
  Node* tail;
  
  void insertSorted( int val ) ;
  void append (int val);
  void prepend (int val);  
  int lookup( int _value );
  int remove( int val );
  void print();
  List();
  ~List();
};


