# Nora (custom shell)

Hey guys I am learning the C programming by building the things, for that I am gonna build the custom shell by learning and doing. I don't gonna use any AI tools for writing the code, even for asking doubt. I gonna research and build it by myself. First task is to print the prompt ```$``` or some other custom prompt what you want. First of all we need to know what is mean y prompt.

## What is Prompt?
A prompt is the letter or a symbol displayed in the (Command Line Interface)CLI or in Shell to tell the user that shell is ready to accept the input.

Our first goal is to print our custom prompt, now lets do it.

## Setup
First of all I created a **directory** named ```nora``` and created two files in it, namely ```main.c``` and ```README.md```. ```main.c``` is used to write our code, ```README.md``` is used to document my process of creating this shell, actually your guys are now reading that ```README.md```. After creating the files I opened in the text editor, you can choose any text editors I am using **VSCode**. After opening the file I include the basic header files in the program namely ```stdio``` and ```stdlib```.

```c
#include <stdio.h>
#include <stdlib.h>

int main(){

    return 0;
}
```

## Prompt
We know what is mean by prompt, it just a symbol or text which the CLI or Shell display. We know how to print the string in the C programming, we know right? 

```c
    char *prompt = "(Nora) $ ";
    printf("%s", prompt);
```
We just included these two lines of code in the program to display the prompt.

```c
#include <stdio.h>
#include <stdlib.h>

int main(){
    // Initializing our prompt
    char *prompt = "(Nora) $ ";
    // Printing our prompt
    printf("%s", prompt);
    
    return 0;
}
```

Now the program print ```(Nora) $ ``` and exit. It is actually we want. Now we want to accept the input from the user after printing the prompt.

## Get Input
Now after printing the prompt the user can enter anything, so now we need to accept the input from the user. User can enter anything like text or para, so we need to accept the string including space. For that purpose we gonna use the function named ```getline()```. It want three arguments, first one is variable name, second is size, third is ```stdin```.

```c
    getline(&command, &bufsize, stdin);
```
This is included in the program

```c
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

    free(command);
    return 0;
}
```

We get the input from the user and free up the space occupied by the variable using the ```free()```. I used ```&command``` and ```&bufsize``` in the getline, cause I pass the value by reference.

## Print out what the user typed

After getting the input from the user now we just print it to show the user that the program accept the input successfully. For that we just use printf statement.

```c
printf("%s", command);
```
After we include this in the program we got this,

```c
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
```

Now it print what you enter after the prompt.

## Infinite Loop
We know that in shell the prompt keeps showing until we give the exit command, for that purpose we gonna use infinite while loop

```c
while(1){
    // Logic here
}
```

The code after we include the infinite while loop.

```c
#include <stdio.h>
#include <stdlib.h>

int main(){

    char *prompt = "(Nora) $ ";
    char *command;
    size_t bufsize = 0;
    while(1){
        // Printing the prompt
        printf("%s",prompt);
        // Getting the input entered by the user
        getline(&command, &bufsize, stdin);
        // Print what we got from the user
        printf("%s\n", command);
    }
    
    free(command);
    return 0;
}
```

We included the infinite loop, now we need to exit from the shell when we type the command ```exit``` for that I gonna use ```if condition```.

## Condition for Exit

When user enter the command ```exit``` the need to exit, for that purpose we gonna check if the given string is ```exit```.

```c
if(strcmp(command, "exit")){
    exit(0);
}
```

The code after we include the condition for exit. Before I gonna remove the printf statement and also include the ```fflush(NULL)``` to remove the buffer. Also I removed the newline from the input string

Code after we include the above things,

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Included to compare the string\

int main(){
    char *prompt = "(Nora) $ ";
    char *command = NULL;
    size_t bufsize = 0;

    while(1){
        // Printing the prompt
        printf("%s", prompt);
        // Flush the buffer
        fflush(NULL);
        //To get the input from the user and check if the user press Ctrl + D
        if (getline(&command, &bufsize, stdin) == -1){
            break;
        }
        // Remove the newline from the input string
        command[strcspn(command, "\n")] = '\0';

        if (command != NULL){
            // Condition to exit from the program
            if (strcmp(command, "exit") == 0){
                break;
            }
        }
    }

    free(command);
    return 0;
}
```
Also you guys can notice that I initialize the variable command to NULL for the conditions which I used before the exit.

## Unknown Command
Now we need to display the message for the unknown command for that purpose we gonna use else block

```c
else{
    printf("Command not found: %s", command);
}
```

Code after this,
```c
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
                printf("Command not found: %s", command);
            }
        }
    }

    free(command);
    return 0;
}
```

## echo builtin

```echo``` is a builtin command which display the whatever the text followed by the command ```echo```. For this we need to work differently. When we get the input from the user we need check if the first four letters are ```echo``` if true we need to print all the thing followed by the command.

For that purpose I use the ```strncmp```.

```c
if (strncmp(command, "echo ", 5) == 0){
    printf("%s\n", command + 5);
}
```

Program after we include this,

```c
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
            if (strcmp(command, "exit") == 0){ // Condition to exit
                break;
            }else if(strncmp(command, "echo ", 5) == 0){ // Condition to check if the command is echo
                printf("%s\n", command + 5);
            }
            else{ // Condition for the invalid commands
                printf("Command not found: %s\n", command);
            }
        }
    }

    free(command);
    return 0;
}
```

## type builtin

The ```type``` is a builtin command which tells if the command is built-in or unknown command. For the purpose we need to tokenize the input string from the user, so we could do many things. For tokenizing the string we gonna use ```strtok```. 

```c
char *token = strtok(command, " ");
int i = 0;
while (token != NULL){
    args[i] = token;
    token = strtok(NULL, " ";
    i++
}
agrs[i] = NULL;
```

This is the main thing to tokenize the input string from the user. Then we need a condition for the type command.

```c
if(strcmp(args[0], "type") == 0){ // Condition for type command
    if(strcmp(args[1], "exit") == 0){
        printf("Built-in command: %s\n",args[1]);
    }else if(strcmp(args[1], "echo") == 0){
        printf("Built-in command: %s\n",args[1]);
    }else if(args[1] == NULL){
        printf("Command not provided\n");
    }else{
        printf("Unknow command: %s\n", args[1]);
    }
}
```

After the main program will looks like this,

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    char *prompt = "(Nora) $ ";
    char *command = NULL;
    size_t bufsize = 0;
    while(1){
        // Start with space for 16 token
        int capacity = 16;
        char **args = malloc(capacity * sizeof(char *));
        if (args == NULL){
            printf("Memory Allocation Failed: malloc()");
            exit(0);
        }
        // Printing the prompt
        printf("%s",prompt);
        // Force to print the prompt before getting any input
        fflush(stdout);
        // Getting the input entered by the user and if the user press Ctrl + D to tell end of the file the program need to exit
        if(getline(&command, &bufsize, stdin) == -1){
            break;
        }
        // Removing the new line from the string
        command[strcspn(command, "\n")] = '\0';
        // Tokenizing the input string from the user
        char *token = strtok(command, " ");

        int i = 0;
        while (token != NULL){
            if (i >= capacity - 1){
                capacity *=2;
                args = realloc(args, capacity * sizeof(char *));
                if (args == NULL){
                    printf("Memory Allocation Failed: realloc()");
                    exit(0);
                }
            }
            args[i] = token;
            token = strtok(NULL, " ");
            i++;
        }
        args[i] = NULL;

        if(args[0] != NULL){
            if (strcmp(args[0], "exit") == 0){ // Condition to exit
                free(args);
                break;
            }else if(strcmp(args[0], "echo") == 0){ // Condition to check if the command is echo
                for (int j = 1; args[j] != NULL; j++){
                    printf("%s", args[j]);

                    if (args[j+1] != NULL){
                        printf(" ");
                    }
                }
                printf("\n");
            }else if(strcmp(args[0], "type") == 0){ // Condition for type command
                if(strcmp(args[1], "exit") == 0){
                    printf("Built-in command: %s\n",args[1]);
                }else if(strcmp(args[1], "echo") == 0){
                    printf("Built-in command: %s\n",args[1]);
                }else if(args[1] == NULL){
                    printf("Command not provided\n");
                }else{
                    printf("Unknow command: %s\n", args[1]);
                }
            }
            else{ // Condition for the invalid commands
                printf("Command not found: %s\n", args[0]);
            }
        }
    }

    free(command);
    return 0;
}
```

## Change in the project files

So now I gonna make three different files to hold our code, headers are at some file and functions are at another file and main logic are at another file.

For that purpose I created a three files namely ```main.c```, ```nora.c``` and last ```nora.h```. ```nora.h``` contains all the header files and function declaration whereas ```nora.c``` contains all the functions and all the logic are in ```main.c```.

Code in each files.
1. nora.h

```c
#ifndef NORA_H
#define NORA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void nora_echo(char **args);
void nora_type(char **args);

#endif
```

2. nora.c

```c
#include "nora.h"

void nora_echo(char **args){ // Function for the echo command
    int i = 1;
    while (args[i] != NULL){
        printf("%s", args[i]);
        
        if (args[i+1] != NULL){
            printf(" ");
        }
        i++;
    }
    printf("\n");
    return;
}

void nora_type(char **args){ // Function for the type command
    if (args[1] != NULL && args[2] == NULL){
        if (strcmp(args[1], "echo") == 0){ // Condition for echo
            printf("Built-in Command: %s\n", args[1]);
        }else if(strcmp(args[1], "exit") == 0){ // Condition for exit
            printf("Built-in Command: %s\n", args[1]);
        }else if(strcmp(args[1], "type") == 0){ // Condition for type
            printf("Built-in Command: %s\n", args[1]);
        }else{ // Condition for the command not found
            printf("Command Not Found: %s\n", args[1]);
        }
    }else if (args[1] == NULL){ // Condtion for the command not provided
        printf("Command is not provided\n");
    }else{ // Condition for the extra arguments
        printf("The type command just need one argument\n");
    }
    return;
}
```
3. main.c

```c
#include "nora.h"

int main(){
    // Initializing the prompt
    char *prompt = "Nora $ ";
    char *command = NULL;
    size_t bufsize = 0;
    // REPL loop
    while (1){
        // Default we gonna use size for 16 tokens
        int capacity = 16;
        char **args = malloc(capacity * sizeof(char *));
        // Check if the memory allocation success
        if (args == NULL){
            printf("Memory Allocation Failed: malloc()");
            exit(0);
        }
        // Printing the prompt
        printf("%s", prompt);
        // Force to print the prompt before getting any input
        fflush(stdout);
        // Getting the input string
        if (getline(&command, &bufsize, stdin) == -1){
            free(args);
            free(command);
            exit(0);
        }
        // Removing the newline from the input string
        command[strcspn(command, "\n")] = '\0';
        // Tokenizing the input string
        char *token = strtok(command, " ");
        int i = 0;
        while (token != NULL){
            if (i >= capacity - 1){
                capacity *=2;
                args = realloc(args, capacity * sizeof(char *));
                if (args == NULL){
                    printf("Memory Allocation Failed: realloc()");
                    free(args);
                    free(command);
                    exit(0);
                }
            }
            args[i] = token;
            token = strtok(NULL, " ");
            i++;
        }
        args[i] = NULL;

        // For commands
        if (args[0] != NULL){
            if (strcmp(args[0], "exit") == 0){ // Condition to exit from the shell
                free(args);
                free(command);
                exit(0);
            }else if(strcmp(args[0], "echo") == 0){
                nora_echo(args);
            }else if(strcmp(args[0], "type") == 0){
                nora_type(args);
            }else{
                printf("Command Not Found: %s", args[0]);
            }
        }
        free(args);
    }
    free(command);
    return 0;
}
```