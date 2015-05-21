/*
 * Wrapper to fuzz the myfunc function defined in a library
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myheader.h"

int main(int argc, char **argv){
	
	int nArguments = 2; 		/* Number of Arguments for myfunc */
	char ** arguments = NULL;	/* Arguments to give to myfunc function */
        FILE* fp;			/* Stream of the input file where are written arguments to extract */

	fp = fopen(argv[2],"rb"); 	
	/* CALL FROM TERMINAL : mywrapper -f /path/input/input.txt
	 * So, here, argv[2] = /path/input/input.txt */
	/* CALL BY AFL-FUZZ : /path/afl-fuzz -i /path/input -o /path/output/ -- /path/mywrapper -f @@ */
	if(fp==NULL)
		exit(1);
	
	/* Each argument of myfunc, is written in each line of the input.txt file, 
	 * and will be written in the arguments array :
	 arguments[0] = 1rst line , arguments[1] = 2nd line, etc. */
	arguments = malloc(nArguments*sizeof(char*));
	if ( extractArgumentsFromInputFile(arguments, nArguments, fp) != nArguments)
		exit(1);

	/* Getting arguments values to give them to the myfunc function. 
	 * Prototype of myfunc : int myfunc (int a, char* s)*/
	int a = (int) strtod(arguments[0],NULL);
	char* s = arguments[1];
	/* myfunc is WRAPPED and IS NOW CALLING */
	myfunc(a, s);
	
	fclose(fp);
	freeArrayOfMallocBuffers(arguments,nArguments);
	return 0;
}


int extractArgumentsFromInputFile(char** arguments, int nArguments, FILE* fp) {

	int i = 0;
	char* tmpBuffer = NULL;         
	size_t sizeBuffer = 0;                  

	while ( (getline(&tmpBuffer, &sizeBuffer, fp) != -1) && i<nArguments ) {
			*(arguments+i) = tmpBuffer;
			removeCarriageReturn(*(arguments+i));
			i+=1;
			tmpBuffer = NULL;
	}

	rewind(fp); // To reset the cursor in the file
	return i;
}

void freeArrayOfMallocBuffers(char** arguments, int nArguments) {
	int i = 0;
	for(i=0; i<nArguments ; i+=1) {
		free(*(arguments+i));
	}
}

void removeCarriageReturn(char* string) {
	char cr = '\n';
	char* chp = strchr(string,cr);
	while (chp!=NULL)
	{
		*chp = '\0';
		chp=strchr(chp+1,cr);
	}
}
