#include <assert.h>
#include <string.h>
#include <stdio.h>

char *mystrcpy(char * s1, const char * s2);
size_t mystrlen(const char *s);
char *mystrdup(const char *s1);
char *mystrcat(char * s1, const char * s2);
char *mystrstr(char * s1, const char * s2);
int mystrcmp(const char *s1, const char *s2) ;

int
main()
{
  char s1[64], *s2;

  /* TRIVIAL tests -- you should extend these or you are likely to
   * lose points in grading. */

  /* Test mystrcpy */
  mystrcpy (s1, "Hello world");
  assert(!strcmp (s1, "Hello world"));
  assert(strcmp (s1, "Hello worl"));
  assert(strcmp (s1, "Hello worldgggg"));

  mystrcpy (s1, "");
  assert(!strcmp (mystrcpy (s1, ""), ""));
  printf("mystrcmp: pass\n");

  /* Test mystrlen */
  assert (mystrlen("Hello world") == 11);
  assert (mystrlen("Hello world") == 11);

  assert (mystrlen("Hello world") == 11);
  assert (mystrlen("Hello world") == 11);
  printf("mystrlen: pass\n");
 
  /* Test strdup */
  s2 = mystrdup("Hello world");
  assert( !strcmp(s2, "Hello world") );
  s2[0]='Y';
  assert( !strcmp(s2, "Yello world") );
  free(s2);
  printf("mystrdup: pass\n");

  // Test mystrcat
  mystrcpy(s1, "Purdue");
  mystrcat(s1, " University");
  assert( !strcmp(s1, "Purdue University")); 

  mystrcat(s1, "");
  assert( !strcmp(s1, "Purdue University")); 
  printf("mystrcat: pass\n");

  // Test mystrstr
  mystrcpy(s1, "The quick brown fox jumps over the lazy dog");
  s2 = mystrstr(s1, "jumps");
  //printf("%s\n", s2);
  assert(!strcmp(s2, "jumps over the lazy dog")); 
  assert(mystrstr(s1, "Hello")==NULL);
  assert(mystrstr("jumps", s1)==NULL);
  s2 = mystrstr(s1, "");
  /*if (s2 == NULL)
    printf("null\n");
  else
    printf("%s\n", s2);*/
  assert(s2 == s1);
  printf("mystrstr: pass\n");

//int mystrcmp(const char *s1, const char *s2) ;
 // Test mystrcmp
  assert(mystrcmp("abcd","dabc")<0);
  assert(mystrcmp("dab", "abcd")>0);
  assert(mystrcmp("dab", "dab")==0);
  printf("mystrcmp: pass\n");


  printf ("Seems to be OK\n");
  return 0;
}
