#include "initialize_arguments_stdin.h"

/* ---------------------------------------------------------------------------------- */
/* int initialize_main(int * argc, char *** argv, char * delim)  */
/* ---------------------------------------------------------------------------------- */

int initialize_main(int * argc, char *** argv, char * delim) {

	char stringToParse [ MAX_LENGTH ];

	if (fgets(stringToParse, sizeof(stringToParse), stdin) == NULL) {
		printf("initialize_main : There is no string to parse !");
		return 0;
	}

	if (stringToParse==NULL) {
		printf("initialize_main : There is no string to parse !");
		return 0;
	}

	removeEndCharacters(stringToParse);
	// Replace '\r' and '\n' by '\0'. Only the first line of the file will be parsed.

	char * string = strdup(stringToParse);

	int nbrArguments = countArguments (&string, delim) + 1 ; // Later : *argc = nbrArguments;
	if (nbrArguments<=1) {
		printf("initialize_main : There is no arguments ! ");
		return 0;
	}

	char ** tab = malloc(nbrArguments*sizeof(char*)); // Later : *argv = tab;

	int i = 0;
	*(tab + i) = "padding***CommandWichLaunchedThisExecutable***";
	i = i+1; // i==1

	char * stringTemp = strsep(&string, delim);
	while (stringTemp!=NULL)
	{	
		if (*stringTemp != '\0') {
			*(tab + i) = strdup(stringTemp);
			i=i+1;
		}

		stringTemp = strsep(&string, delim);
	}

	if(i==1) {
		printf("initialize_main : There is no arguments ! ");
		return 0;
	}

	*argc = nbrArguments;
	*argv = tab;

	free(string);

	return 0;

}

/* ---------------------------------------------------------------------------------- */
/* int countArguments (char ** stringp, char * delim) 
 * initialize_main(&argc,&argv," "); => Each space character splits an argument
 * initialize_main(&argc,&argv,"\0"); => All the first line is the argument 
 */
/* ---------------------------------------------------------------------------------- */

int countArguments (char ** stringp, char * delim) {

	if (stringp==NULL || delim==NULL) {
		return -1;
	}

	int i = 0;

	char * string = strdup(*stringp);
	char * stringTemp = strsep(&string, delim);

	while (stringTemp!=NULL)
	{	
		if (*stringTemp != '\0' && *stringTemp != '\n' && *stringTemp != '\r')
			i=i+1;

		stringTemp = strsep(&string, delim);
	}

	free(string);

	return i;
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

/* ---------------------------------------------------------------------------------- */
/* removeEndCharacters(char * string) */
/* ---------------------------------------------------------------------------------- */

void removeEndCharacters(char * string) {

	if (string==NULL) {
		return;
	}

	char endCharacters[] = {'\r', '\n'};

	int i = 0 ;
	char c ;

	for(i=0; i<sizeof(endCharacters);i=i+1) {

		c = endCharacters[i];

		char * pch = strchr(string,c);

		while (pch!=NULL)
		{
			*pch = '\0';
			pch=strchr(pch+1,c);
		}

	}
}
