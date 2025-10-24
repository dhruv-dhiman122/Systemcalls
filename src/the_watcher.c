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
#define TOO_FEW_ARGUMENTS 1
//---------------------------- Area for global variables or namespaces (if any) ----------------------------------//

//------------------ After this line the code is there written any function that is made by the user ----------------------------------------//

// ---------------------- space for main function only --------------------------------
int main(int argc, char** argv) {
		char *basePath = NULL;
		char *token = NULL;
    
		if (argc < 2) {
				fprintf(stderr, "USAGE: the_watcher path\n");
				exit(TOO_FEW_ARGUMENTS);
		}

		// Copy the input string properly
		basePath = (char*)malloc(strlen(argv[1]) + 1);
    
		if (basePath == NULL) {
				perror("malloc failed");
				exit(exit_failure);
		}
		strcpy(basePath, argv[1]);

		// Tokenize to get the last component
		token = strtok(basePath, "/");
		char *lastToken = token;
		
		while (token != NULL) {
				lastToken = token;  // Keep track of the last token
				token = strtok(NULL, "/");
		}
    
		if (lastToken != NULL) {
				printf("%s\n", lastToken);
		} 
		else {
				printf("\n");
		}
		
		while(true) // because the system calls run behind the sense continue 
		{
		
		}

		free(basePath);
		exit(exit_success);
}
