#ifndef INITIALIZE_ARGUMENTS_STDIN
#define INITIALIZE_ARGUMENTS_STDIN

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_LENGTH 99999

int countArguments (char ** stringp, char * delim);
int displayArrayOfStrings (char ** array, int length);
int initialize_main(int * argc, char *** argv, char * delim);
void removeEndCharacters(char * string);

#endif
