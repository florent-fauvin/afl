/*
 * Wrapper to fuzz the "myfunc" function in the "mylib" library
 * Prototype of myfunc : int myfunc (int a, char* s);
 */

#include <stdio.h>
#include "myheader.h"

void main(int argc, char **argv){

        FILE* fp = fopen(argv[2],"r"); 	
	/* mywrapper -f /path/input/input.txt */
	/* FUZZING : /path/afl-fuzz -i /path/input -o /path/output/ -- /path/mywrapper -f @@ */

	int a;
	char* s; 
	
	// Reading "a" and "s" from input.txt

	myfunc(a, s);
	/* myfunc is WRAPPED */

}
