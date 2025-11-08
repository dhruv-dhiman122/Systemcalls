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
#define ENTR_FILE_NAME_SIZE 120

//========================================== Space for user defined function ===============================================//

inline void FileError() {
    //do something
    //Aim; to be called when there is error during the process for reading and writing into the file
}


inline void CopyFile(int first_file, int second_file) { // first_file and second_file is a file descriptor
    //do something
    //Aim; to be called when the user what to read from one file into other

}

inline void WriteFile(int first_file, int second_file) {
    //do something
    //Aim; to read from the file to the console(screen of the user)
}

//=========================================== space for main function ======================================================//

int main() {
    int user_choose;
    printf("What do you want to do over with this code\n");
    printf("1 for copying the file into other file, 2 for writing the file onto the screen\n"); // option for the user
    scanf("%d",&user_choose); // the user chooses to either read or write
    
    switch(user_choose) {
        case 1:
            char file1[ENTR_FILE_NAME_SIZE];
            char file2[ENTR_FILE_NAME_SIZE];
            printf("Enter the first file name with its type (example:testfile.md)\n");
            scanf("%s", file1);
            printf("\n");
            printf("Enter the seocnd file name with its type (example: testfile.md)");
            scanf("%s", file2);
            CopyFile((int)file1, (int)file2);
            break;
        case 2:
            char write_file1[ENTR_FILE_NAME_SIZE];
            char write_file2[ENTR_FILE_NAME_SIZE];
            printf("Enter the first file name with its type (example:testfile.md)\n");
            scanf("%s", file1);
            printf("\n");
            printf("Enter the seocnd file name with its type (example: testfile.md)");
            scanf("%s", file2);
            WriteFile((int)write_file1, (int)write_file2);
            break;
        default:
            printf("there is no opertation like that, plz enter a correct one\n");
            break;    
    }
    exit(EXT_SUCCESS);
}
