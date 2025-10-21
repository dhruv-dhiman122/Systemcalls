#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

//-------------- After this line there must not be any more inclusion --------------------------//

//------------------- Area for macro or for operations before compiler kicks in -----------------------------------//

#define exit_success 0
#define exit_failure 1

//---------------------------- Area for global variables or namespaces (if any) ----------------------------------//

//------------------ After this line the code is there written any function that is made by the user ----------------------------------------//

// ---------------------- space for main function only --------------------------------
int main(int argc,char** argv) {
		char *basePath = NULL;

		if(argc < 2) {
				fprintf(stderr,"There is a error, the argument are less than 2. You atleast want one argument");
				exit(exit_failure);
		}

		basePath = (char*)malloc(sizeof(char)*strlen(argv[1])+1);

		exit(exit_success);
}
