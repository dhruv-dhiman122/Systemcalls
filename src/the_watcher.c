#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

//--------------- After this line there must not be any more inclusion --------------------------//

//------------------- Area for macro or for operations before compiler kicks in -----------------------------------//

#define exit_success 0
#define exit_failure 1

//---------------------------- Area for global variables or namespaces (if any) ----------------------------------//

//------------------ After this line the code is there written any function that is made by the user ----------------------------------------//

// ---------------------- space for main function only --------------------------------
int main() {

		exit(exit_success);
}
