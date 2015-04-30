#include <stdio.h>
#include <string.h>

#include "argv-fuzz-inl.h" // PATCH

int displayArrayOfStrings (char ** array, int length) ;

int main (int argc, char ** argv) {

	AFL_INIT_SET0("prog_name_MANUALLY"); // PATCH
	// AFL_INIT_ARGV();

	printf("\n***** %d arguments parsed from the stdin input *****\n",argc);
	displayArrayOfStrings (argv,argc);
	printf("***************************************************\n\n");

	return 0;
}

/* ---------------------------------------------------------------------------------- */
/* int displayArrayOfStrings (char ** array, int length) */
/* ---------------------------------------------------------------------------------- */

int displayArrayOfStrings (char ** array, int length) {

	if (array==NULL || length<=0) {
		printf("displayArrayOfStrings : There is no array to display !");
		return 0;
	}

	int i = 0;
	for(i=0;i<length; i=i+1) {
		printf(",%s,\n",*(array+i));
	}
	
	return 0;
}
