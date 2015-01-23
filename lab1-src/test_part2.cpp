#include <stdio.h>
#include <stdlib.h>

#define MEM_UNKNOWN "unknown"
#define MEM_STACK "stack"
#define MEM_HEAP "heap"
#define MEM_DATA "data"
#define MEM_BSS "bss"
#define MEM_TEXT "text"

extern int etext, edata, end;

void print_segment_locations();
void report(const char *var, const char *section);
const char* getMemSection(void*);

int a = 5; 
int b; 
static int c; 

class class1 { 
public:
  static int m1;
};

int class1::m1;

int main() { 
  print_segment_locations();
  int d;
  static int e = 0;
  static int f = 1;
  int array[10];
  char *ptr1 = new char[100];
  char *ptr2 = (char *)malloc(10 * sizeof(char));
  
  report("a", getMemSection(&a));
  report("b", getMemSection(&b));
  report("c", getMemSection(&c));
  report("m1", getMemSection(&(class1::m1)));
  report("d", getMemSection(&d));
  report("e", getMemSection(&e));
  report("f", getMemSection(&f));
  report("array", getMemSection(&array));
  report("ptr1", getMemSection(ptr1));
  report("ptr2", getMemSection(ptr2));
  report("MEM_DATA", getMemSection((void*)&(MEM_DATA)));
  report("MEM_TEXT", getMemSection((void*)&(MEM_TEXT)));

  return 0;
}


/*void report_results() {
  report("a", getMemSection(&a));
  report("b", getMemSection(&b));
  report("c", getMemSection(&c));
  report("m1", getMemSection(&m1));
  report("d", getMemSection(&d));
  report("e", getMemSection(&e));
  report("f", getMemSection(&f));
  report("array", getMemSection(&array));
  report("ptr1", getMemSection(ptr1));
  report("ptr2", getMemSection(ptr2));

}*/

const char* getMemSection(void* ptr) {
  // The following variable was declared so that the last data item placed on the stack is known.
  // The variable 'a' should be the last item placed on the stack frame for this function call.

  // Therefore, we can determine the boundary of the stack and know the memory ranges for
  // the stack and the heap by checking the location of 'ptr' against the location of 'a'.
  int a = 5;
  if (ptr < &etext)
    return MEM_TEXT;
  else if (ptr < &edata)
    return MEM_DATA;
  else if (ptr < &end)
    return MEM_BSS;
  else {
    const char* ret;
    if (ptr < &a)
      ret = MEM_HEAP;
    else
      ret = MEM_STACK;
    return ret;
  }
}

void report(const char *var, const char *section) {
  printf("%s: %s\n", var, section);
}


void print_segment_locations() {
  printf("End address of text is %10p\n", &etext);
  printf("End address of edata is %10p\n", &edata);
  printf("BSS address is %10p\n", &end);
}
