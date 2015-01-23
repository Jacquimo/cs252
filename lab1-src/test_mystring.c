#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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
  assert(strlen(s1) == 11);
  assert(!strcmp (s1, "Hello world"));
  assert(strcmp (s1, "Hello worl"));
  assert(strcmp (s1, "Hello worldgggg"));
  assert(strcmp(s1, ""));
  assert(strcmp (s1, "ello world"));
  assert(strcmp (s1, "ello worl"));

  mystrcpy (s1, "");
  assert(strlen(s1) == 0);
  assert(!strcmp (mystrcpy (s1, ""), ""));
  assert(strlen(s1) == 0);
  printf("mystrcmp: pass\n");

  /* Test mystrlen */
  assert (mystrlen("Hello world") == 11);
  assert (mystrlen("CS252 Systems Programming") == strlen("CS252 Systems Programming"));
  assert (mystrlen("\b") == strlen("\b"));
  assert (mystrlen("") == strlen(""));
  printf("mystrlen: pass\n");
 
  /* Test strdup */
  s2 = mystrdup("Hello world");
  assert( !strcmp(s2, "Hello world") );
  assert(strlen(s2) == 11);
  assert(strlen(s2) == mystrlen(s2));

  s2[0]='Y';
  assert( !strcmp(s2, "Yello world") );
  assert(strlen(s2) == 11);
  assert(strlen(s2) == mystrlen(s2));

  s2[10] = '\0';
  assert( !strcmp(s2, "Yello worl") );
  assert(strlen(s2) == 10);
  assert(strlen(s2) == mystrlen(s2));

  free(s2);
  s2 = mystrdup("");
  assert(!strcmp(s2, ""));
  assert(mystrcmp(s2, "") == strcmp(s2, ""));
  assert(strlen(s2) == 0);
  assert(mystrlen(s2) == strlen(s2));

  free(s2);
  printf("mystrdup: pass\n");

  // Test mystrcat
  mystrcpy(s1, "Purdue");
  assert(mystrlen(s1) == strlen(s1));
  mystrcat(s1, " University");
  assert(mystrlen(s1) == strlen(s1));
  assert( !strcmp(s1, "Purdue University"));

  mystrcat(s1, "");
  assert(mystrlen(s1) == strlen(s1));
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
