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