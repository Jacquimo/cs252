#include <stdio.h>
#include <stdlib.h>

extern int etext, edata, end;

void print_segment_locations();
void report(const char *var, const char *section);

int a = 5; 
int b; 
static int c; 

class class1 { 
  static int m1; 
}; 

int main() { 
  print_segment_locations();
  int d;
  static int e = 0;
  static int f = 1;
  int array[10];
  char *ptr1 = new char[100];
  char *ptr2 = (char *)malloc(10 * sizeof(char));
  return 0;
}

#define MEM_UNKNOWN "unknown"
#define MEM_STACK "stack"
#define MEM_HEAP "heap"
#define MEM_DATA "data"
#define MEM_BSS "bss"
#define MEM_TEXT "text"

void report_results() {
  report("a", MEM_UNKNOWN);
  report("b", MEM_UNKNOWN);
  report("c", MEM_UNKNOWN);
  report("m1", MEM_UNKNOWN);
  report("d", MEM_UNKNOWN);
  report("e", MEM_UNKNOWN);
  report("f", MEM_UNKNOWN);
  report("array", MEM_UNKNOWN);
  report("ptr1", MEM_UNKNOWN);
  report("ptr2", MEM_UNKNOWN);

}

void report(const char *var, const char *section) {
  printf("%s: %s\n", var, section);
}


void print_segment_locations() {
  printf("End address of text is %10p\n", &etext);
  printf("End address of edata is %10p\n", &edata);
  printf("BSS address is %10p\n", &end);
}
