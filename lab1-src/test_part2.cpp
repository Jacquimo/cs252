#include <stdio.h>
#include <stdlib.h>

extern int etext, edata, end;

void print_segment_locations();
void report(const char *var, const char *section);
char* getMemSection(void*);

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

  return 0;
}

#define MEM_UNKNOWN "unknown"
#define MEM_STACK "stack"
#define MEM_HEAP "heap"
#define MEM_DATA "data"
#define MEM_BSS "bss"
#define MEM_TEXT "text"

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

char* getMemSection(void* ptr) {
  if (ptr < &etext)
    return MEM_TEXT;
  else if (ptr < &edata)
    return MEM_DATA;
  else if (ptr < &end)
    return MEM_BSS;
  else {
    char* test = (char*)malloc(sizeof(char));
    char* ret;
    if (ptr <= test)
      ret = MEM_HEAP;
    else
      ret = MEM_STACK;
    free(test);
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
