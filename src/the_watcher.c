//============================= space for including files ============================//
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <signal.h>
#include <sys/inotify.h>

//============================ Space for macro ===================================//

#define exit_success 0
#define exit_failure 1
#define TOO_FEW_ARGUMENTS 1
#define EXT_ERR_INIT_INOTIFY 2
#define EXT_ADD_WATCH 3
#define EXT_ERR_BASE_PATH_NULL 4
#define EXT_ERR_READ_INOTFY 5
#define EXT_ERR_INIT_LIBNOTIFY 6

//================================== space for golbal variables ===============================//

int IeventQueue = -1;
int IeventStatus = -1;
char *Programtitle = "the_watcher";

//============================ space for other function made by the user ================================//

void singal_handler(int signal) {
		int closeStatus = -1;
		printf("Signal received, cleaning up.....");	
		closeStatus = inotify_rm_watch(IeventQueue, IeventStatus);
		exit(exit_success);
}

//======================== space for main function ==================================//

int main(int argc, char** argv) {
		bool libnotifyInitStatus = false;
		char *basePath = NULL;
		char *token = NULL;
		char *notificationMessage = NULL;
		char buffer[4096];
		int readLength;
		struct inotify_event *watchEvent;
		const uint32_t watchMask = IN_CREATE | IN_DELETE | IN_ACCESS | IN_CLOSE_WRITE | IN_MODIFY | IN_MOVE_SELF;

		if (argc < 2) {
				fprintf(stderr, "USAGE: the_watcher path\n");
				exit(TOO_FEW_ARGUMENTS);
		}

		// Extract last token from path (for display purposes only)
		char *pathCopy = strdup(argv[1]);
		if (pathCopy == NULL) {
				perror("strdup failed");
				exit(exit_failure);
		}
    
		token = strtok(pathCopy, "/");
		char *lastToken = token;
    
		while (token != NULL) {
				lastToken = token;
				token = strtok(NULL, "/");
		}
    
		if (lastToken != NULL) {
				printf("Watching: %s\n", lastToken);
		}
		free(pathCopy);
		libnotifyInitStatus = notify_init(Programtitle);
		if(!libnotifyInitStatus) {
				fprintf(stderr, "Error in initializing libnotify\n");
				exit(EXT_ERR_INIT_LIBNOTIFY);
		}
		// Initialize inotify
		IeventQueue = inotify_init();
		if (IeventQueue == -1) {
				perror("Error initialising inotify instance");
				exit(EXT_ERR_INIT_INOTIFY);
		}

		// Add watch - use original argv[1], not the corrupted basePath
		IeventStatus = inotify_add_watch(IeventQueue, argv[1], watchMask);
    
		if (IeventStatus == -1) {
				perror("Error adding file to watch instance");
				close(IeventQueue);
				exit(EXT_ADD_WATCH);
		}

		printf("Starting to watch: %s\n", argv[1]);

		while (true) {
				readLength = read(IeventQueue, buffer, sizeof(buffer));
				if (readLength == -1) {
						perror("Error reading from inotify instance");
						close(IeventQueue);
						exit(EXT_ERR_READ_INOTFY);
				}

				char *bufferPointer = buffer;
				while (bufferPointer < buffer + readLength) {
						watchEvent = (struct inotify_event *)bufferPointer;
            
						// Determine event type
						notificationMessage = "Unknown event";
						if (watchEvent->mask & IN_CREATE) {
								notificationMessage = "File created";
						} else if (watchEvent->mask & IN_DELETE) {
								notificationMessage = "File deleted";
						} else if (watchEvent->mask & IN_ACCESS) {
								notificationMessage = "File accessed";
						} else if (watchEvent->mask & IN_MODIFY) {
								notificationMessage = "File modified";
						} else if (watchEvent->mask & IN_CLOSE_WRITE) {
								notificationMessage = "File written and closed";
						} else if (watchEvent->mask & IN_MOVE_SELF) {
								notificationMessage = "File moved";
						}

						// Print the event information
						if (watchEvent->len) {
								printf("%s: %s\n", notificationMessage, watchEvent->name);
						} else {
								printf("%s\n", notificationMessage);
						}

						// Move to next event
						bufferPointer += sizeof(struct inotify_event) + watchEvent->len;

						int notifyHandle = notify_notification_new(basePath, notificationMessage, "dialog-information");
						if(notifyHandle == NULL) {
								fprintf(stderr, "notification handle was null!\n");
								continue;
						}
						notifiy_notification(notifyHandle, NULL);
				}
		}

		// Cleanup (this code is unreachable in the infinite loop)
		close(IeventQueue);
		exit(exit_success);
}
