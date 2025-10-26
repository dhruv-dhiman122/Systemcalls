#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <signal.h>
#include <sys/inotify.h>
//-------------- After this line there must not be any more inclusion --------------------------//

//------------------- Area for macro or for operations before compiler kicks in -----------------------------------//

#define exit_success 0
#define exit_failure 1
#define TOO_FEW_ARGUMENTS 1
#define EXT_ERR_INIT_INOTIFY 2
#define EXT_ADD_WATCH 3
#define EXT_ERR_BASE_PATH_NULL 4
//---------------------------- Area for global variables or namespaces (if any) ----------------------------------//

int IeventQueue = -1;
int IeventStatus = -1;

//------------------ After this line the code is there written any function that is made by the user ----------------------------------------//

// ---------------------- space for main function only --------------------------------
int main(int argc, char** argv) {
		char *basePath = NULL;
		char *token = NULL;
		char buffer[4096];
		int readLength;
		const uint32_t watchMask = IN_CREATE | IN_DELETE | IN_ACCESS | IN_CLOSE_WRITE | IN_MODIFY | IN_MOVE_SELF;

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

		if(basePath == NULL) {
				fprintf(stderr, "Error getting base path");
				exit(EXT_ERR_BASE_PATH_NULL);
		}
		
		IeventQueue = inotify_init();
		if(IeventQueue == -1) {
				fprintf(stderr, "Error initialising inotify instance!\n");
				exit(EXT_ERR_INIT_INOTIFY);
		}

		IeventStatus = inotify_add_watch(IeventQueue, argv[1], watchMask);
		
		if(IeventStatus == -1) {
				fprintf(stderr, "Error adding file to watch instance!\n");
				exit(EXT_ADD_WATCH);
		}

		while(true) // because the system calls run behind the sense continue 
		{
				printf("Waiting for ievent.....\n");

				readLength = read(IeventQueue, buffer, sizeof(buffer));
				
		}

		free(basePath);
		exit(exit_success);
}
