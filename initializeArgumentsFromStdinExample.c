#include "initialize_arguments_stdin.h"
#include "initialize_arguments_stdin.c"

int main (int argc, char ** argv) {

/* To parse stdin input and affect arguments */
	initialize_main(&argc,&argv," "); // See the description of the function

/* For Debugging --> */
	printf("\n***** %d arguments parsed from the stdin input *****\n",argc);
	displayArrayOfStrings (argv,argc);
	printf("***************************************************\n\n");
/* <-- */

}


