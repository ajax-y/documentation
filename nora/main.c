#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    char *prompt = "(Nora) $ ";
    char *command = NULL;
    size_t bufsize = 0;
    while(1){
        // Printing the prompt
        printf("%s",prompt);
        // Force to print the prompt before getting any input
        fflush(NULL);
        // Getting the input entered by the user and if the user press Ctrl + D to tell end of the file the program need to exit
        if(getline(&command, &bufsize, stdin) == -1){
            break;
        }
        // Removing the new line from the string
        command[strcspn(command, "\n")] = '\0';

        if(command != NULL){
            if (strcmp(command, "exit") == 0){
                break;
            }else{
                printf("Command not found: %s\n", command);
            }
        }
    }

    free(command);
    return 0;
}