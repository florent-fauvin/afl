/*
 * Wrapper to fuzz a myfunc function defined in a library
 *
 * The wrapper has to be VERY RELIABLE, because it must not crash during the fuzzing !
 * It is the myfunc function which is fuzzed, not the wrapper !
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myheader.h"

#define N_ARGS 2

int main(int argc, char **argv){

	char* arguments[N_ARGS];	/* Arguments to give to myfunc function */
        FILE* fp;			/* Stream of the input file where are written arguments to extract */


	fp = fopen(argv[2],"rb");
	if(fp==NULL)
		debugExit("main : The input file cannot be open.\n");
	/* CALL FROM TERMINAL : mywrapper -f /path/input/input.txt
	 * So, here, argv[2] = /path/input/input.txt */
	/* CALL BY AFL-FUZZ : /path/afl-fuzz -i /path/input -o /path/output/ -- /path/mywrapper -f @@ */


	if ( extractArgumentsFromInputFile(arguments, N_ARGS, fp) < N_ARGS)
		debugExit("main : Not enough arguments in the input file.\n");	
	/* Each argument of myfunc, is written in each line of the input.txt file, 
	 * and will be written in the arguments array :
	 * arguments[0] = 1rst line , arguments[1] = 2nd line, etc. */;


	/* Prototype of myfunc : int myfunc (int a, char* s)*/
	int a = (int) strtod(arguments[0],NULL);
	char* s = arguments[1];
	/* myfunc is WRAPPED and IS NOW CALLING */
	myfunc(a, s);
	
	fclose(fp);
	freeArrayOfMallocBuffers(arguments,N_ARGS);
	return 0;
}

/* -------------------------------------- ROUTINES -------------------------------------------- */

int extractArgumentsFromInputFile(char** arguments, int n_args, FILE* fp) {

	int i = 0;
	char* tmpBuffer = NULL;         
	size_t sizeBuffer = 0;                  

	while ( (getline(&tmpBuffer, &sizeBuffer, fp) != -1) && i<n_args ) {
			removeCarriageReturn(tmpBuffer);
			*(arguments+i) = tmpBuffer;
			i+=1;
			tmpBuffer = NULL;
	}

	rewind(fp); // To reset the cursor in the file
	return i;
}

void freeArrayOfMallocBuffers(char** arguments, int n_args) {
	int i = 0;
	for(i=0; i<n_args ; i+=1) {
		free(*(arguments+i));
	}
}

void removeCarriageReturn(char* string) {
	char cr = '\n';
	char* chp = strrchr(string,cr);
	if(chp!=NULL)
		*chp = '\0';
}

void debugExit(char* msg) {
	printf(msg);
	exit(1);
}
