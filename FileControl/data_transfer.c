/*
 *The aim of this folder is to learn about systemcalls like fcntl and get better at it
 * 📢📢📢📢
 * NOTE TO OTHER:
 *      if you fell that you can help me imporve my code, then plz make a pull request
 *      and let me know by commit what you did and add. And commit the knowledge in the code you commited. thank you for visting btw
 *      ENJOY!!! MY CODE
 * */


#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

//========================================= Space for macro and golbal variable ============================================//

#define EXT_SUCCESS 0
#define EXT_FAILURE 1
#define BUFFER_SIZE 1024
#define SMALL_BUFFER_SIZE 20

//========================================== Space for user defined function ===============================================//

inline void FileError() {
    //do something
    //Aim; to be called when there is error during the process for reading and writing into the file
}


inline void ReadFile(int first_file, int second_file) {
    //do something
    //Aim; to be called when the user what to read from one file into other
}

inline void WriteFile(int first_file, int second_file) {
    //do something
    //Aim; to read from the file to the console(screen of the user)
}

//=========================================== space for main function ======================================================//

int main() {

    exit(EXT_SUCCESS);
}
