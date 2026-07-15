# Nora (custom shell)

Hey guys I am learning the C programming by building the things, for that I am gonna build the custom shell by learning and doing. I don't gonna use any AI tools for writing the code, even for asking doubt. I gonna research and build it by myself. First task is to print the prompt ```$``` or some other custom prompt what you want. First of all we need to know what is mean y prompt.
[![GitHub Repository Card](https://vercel.app)](https://github.com/ajax-y/nora)


## What is Prompt?
A prompt is the letter or a symbol displayed in the (Command Line Interface)CLI or in Shell to tell the user that shell is ready to accept the input.

Our first goal is to print our custom prompt, now lets do it.

## Setup
First of all I created a **directory** named ```nora``` and created two files in it, namely ```main.c``` and ```README.md```. ```main.c``` is used to write our code, ```README.md``` is used to document my process of creating this shell, actually your guys are now reading that ```README.md```. After creating the files I opened in the text editor, you can choose any text editors I am using **VSCode**. After opening the file I include the basic header files in the program namely ```stdio``` and ```stdlib`​``.

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
