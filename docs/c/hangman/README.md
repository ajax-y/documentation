# Hangman

The idea of the program is very simple. First there need to be a list of words **wordBank** the computer choose the random word from it. Then display the first letter only and followed by the underscores. Then it ask for the guess If we type the letter it check whether it is correct or wrong. If it correct then display the guessed letter followed by the underscores. If we enter wrong letter it reduce your lives. At last it print either you won or lose the game with the word.

### Library
In this program I used four library namely, ```stdio```, ```stdlib```, ```string```, ```time```. As usual ```stdio``` is used for the input and output operations, ```stdlib``` and ```times``` is used to generate the random number and ```string``` used for some string operations like **strcmp**.

### wordBank

I have declared a array named **wordBank** with size of **10 X 10** and initialized with some random word. With that I have declared the variables which need to be used in the program.

### Display menu

First when the user enter the game it need to display a welcome message or something. For that I used my own given below,

```
        Hangman
#########################

[1] Play Game
[2] Exit

Enter your option: 
```

When the user enter 1 it need to go to the game, if he enter 2 it need to exit from the game.

###  Random

When the user pick to play game, the computer pick the random word from the **wordBank** and store it to a variable. Then we need to find the length of the word to diplay exactly the number of underscores. We display the word with first letter followed by the underscore. 

### Guess

It ask the user to enter a guess also say to enter **?** for reveal ine word. If the user enter **?** it reveal the current character and reduce one live. If word enter a letter, it checks whether the letter is correct or not. If it correct then it display the discovered words followed by underscores. If it was wrong it reduce one life and say wrong guess.

### Result

If the user discover the whole word, the program print the winning message with the word. If the lives drops to 0. Then the program print the lose message with the word.

### Play again

With that winning message or lose message the program ask the user to play again or exit from the game.

```
        Hangman
#########################

[1] Play Again
[2] Exit

Enter your option: 
```

### Info

I just used a 10 words in the word bank. If need more we can use the ```*.csv``` file for the more words. For now I just build a simple and working game.

### Code
```c
/*
    Hangman is written by Ajay E at 02/07/2026
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int option;
    int roundPlayed = 0;
    char guess; // For the guessing character
    // List of words where computer choose from it.
    char wordBank [10][10] = {"smell", "color", "sense", "belong", "point", "reply", "behave", "health", "happy", "smash"};
    // For picking a random word from the wordBank
    srand(time(NULL));

    while (1==1){
        printf("\tHangman\n");
        printf("##########################\n\n");
        if (roundPlayed == 0){
            printf("[1] Play Game\n");
        }
        else{
            printf("[1] Play Again\n");
        }
        printf("[2] Exit\n");
        printf("Enter your option: ");
        scanf("%d", &option);

        if (option >2 || option <1){
            printf("Please Enter a valid option.\n");
        }
        else if (option == 2){
            printf("Thank You! Come Again.\n");
            break;
        }
        else {
            int lives = 3;
            int randomChoice = (rand()%10);
            // Copy the random word to the secretWord
            char *secretWord = wordBank[randomChoice];
            // TO get the length of the secret word
            int wordLength = strlen(secretWord);
            char displayWord[10];
            // Fill the displayWord with the underscore to the length of the secret word.
            for (int i = 0; i < wordLength; i++){
                displayWord[i] = '_';
            }
            // Tell a program that sting end.
            displayWord[wordLength] = '\0';
            // To reveal the first letter of the secret word
            displayWord[0] = secretWord[0];
            while (lives >0 && strcmp(secretWord, displayWord) != 0){
                printf("\t\tLives: %d\n", lives);
                printf("\t%s\n", displayWord);
                printf("Enter your guess(If you want to reveal the letter just type ?): ");
                scanf(" %c", &guess); //Getting the guess from user
                if (guess == '?'){
                    lives-=1;
                    // Revealing the letter.
                    for (int i =0; i < wordLength; i++){
                        if (displayWord[i]=='_'){
                            displayWord[i] = secretWord[i];
                            break;
                        }
                    }
                }
                else{
                    int foundMatch = 0; // Assuming they guess the character as wrong at initial
                    for (int i =0; i < wordLength; i++){
                        if (secretWord[i]==guess){
                            displayWord[i] = guess;
                            foundMatch = 1;
                        }
                    }

                    if (foundMatch == 0){
                        printf("Wrong guess!\n");
                        lives-=1;
                    }
                }

            }
            if (lives == 0){
                printf("You Lose the game. The word is %s\n", secretWord);
            }
            else{
                printf("You Won the game. The word is %s\n", secretWord);
            }
        }
        roundPlayed +=1;
    }
}
```