#include <stdio.h>
#include <stdlib.h>

int main(){

    char *prompt = "(Nora) $ ";
    char *command;
    size_t bufsize = 0;
    // Printing the prompt
    printf("%s",prompt);
    // Getting the input entered by the user
    getline(&command, &bufsize, stdin);
    // Print what we got from the user
    printf("%s\n", command);

    free(command);
    return 0;
}