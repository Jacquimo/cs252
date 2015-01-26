#include <sys/types.h>
#include <stdlib.h>

/*
 * Implement the following string procedures.
 *
 * Type "man strstr" to find what each of the functions should do.
 *
 * For example, mystrcpy should do the same as strcpy.
 *
 * IMPORTANT: DO NOT use predefined string functions.
 */

char *mystrcpy(char * s1, const char * s2)
{
	int i = -1;

	do {
		++i;
		*(s1 + i) = *(s2 + i);
	} while (*(s2 + i));

	return s1;
}

size_t mystrlen(const char *s)
{
	int i = 0;
	while (*(s + i))
		++i;
	return i;
}

char *mystrdup(const char *s1)
{
	int len = mystrlen(s1);
	char* sr = malloc(sizeof(char) * len + 1);
	mystrcpy(sr, s1);
	return sr;
}

char *mystrcat(char * s1, const char * s2)
{
	// find the null terminator of the destination string
	int i = 0;
	while (*(s1 + i))
		++i;

	// append the source string onto the destination string
	int j = -1;
	do {
		++j;
		*(s1 + i + j) = *(s2 + j);
	} while (*(s2 + j));

	return s1;
}

char *mystrstr(char * s1, const char * s2)
{
	//return strstr(s1, s2);

	if (s1 == NULL || *s1 == '\0')
		return NULL;

	if (*s2 == '\0')
		return s1;

	
	for (int i = 0; *(s1 + i); ++i)
		if (*(s1 + i) == *s2) {
			int j = 0;
			while (*(s1 + i + j) == *(s2 + j) && *(s1 + i + j) && *(s2 + j))
				++j;

			if (*(s2 + j) == '\0')
				return s1 + i;

			if (*(s1 + i + j) == '\0')
				return NULL;

			i = i + j;
		}

	return NULL;
}

int mystrcmp(const char *s1, const char *s2) {
	/*int i = 0;
	while (*(s1 + i) == *(s2 + i)) {
		if (*(s1 + i) == '\0')
			break;
		if (*(s2 + i) == '\0')
			break;
		++i;
	}

	return *(s1 + i) - *(s2 + i);*/

	int i = 0;
	while(s1[i] && s2[i] && s1[i] == s2[i])
		++i;

	return (s1[i] - s2[i]) < 0 ? -1 : (s1[i] - s2[i]) == 0 ? 0 : 1;
}

