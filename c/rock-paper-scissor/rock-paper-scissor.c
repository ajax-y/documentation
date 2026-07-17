/*
    Rock Paper Scissor was written by Ajay E at 02/07/2026
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int option, nextoption, userChoice, computerChoice;
    option = 0; //for loop bypass
    //For generate a random number which is the computerChoice
    srand(time(NULL));
    while (1==1){
        if (option !=1){
            // Wecome message
            printf("\tRock Paper Scissor\n");
            printf("##################################\n\n");
            printf("[1] Play Game\n");
            printf("[2] Exit\n\n");
            printf("Enter your option: ");
            scanf("%d", &option);
        }
        // Condition to exit from the game or play the game
        if (option >2 || option <1){
            printf("Please enter a valid option.");
            option = 0; //Reset to show the wecome message again
        }
        // For exit from the program
        else if(option == 2){
            printf("Thank You! Come again.");
            break;
        }
        // For valid option
        else{
            // Game interface
            printf("\tRock Paper Scissor\n");
            printf("##################################\n\n");
            printf("[1] Rock\n");
            printf("[2] Paper\n");
            printf("[3] Scissor\n\n");
            printf("Enter your option: ");
            // Getting user choice
            scanf("%d", &userChoice);
            // Generating computer choice
            computerChoice = (rand()%3) + 1;

            // Comparing the userChoice and computerChoice
            if (userChoice >3 || userChoice <1){
                // For a non valid inputs
                printf("Enter a valid option.");
            }
            else{
                // Reveal the choices to the player
                printf("\nYou chose: %s", (userChoice == 1) ? "Rock" : (userChoice == 2) ? "Paper" : "Scissor");
                printf("\nComputer chose: %s\n", (computerChoice == 1) ? "Rock" : (computerChoice == 2) ? "Paper" : "Scissor");
                //For a valid inputs
                if (userChoice == computerChoice){
                    // Tie game
                    printf("\n\t[The game is TIE]\n");
                }
                else if((userChoice == 1 && computerChoice == 3) || (userChoice == 2 && computerChoice == 1) || (userChoice == 3 && computerChoice == 2)){
                    // For user winning
                    printf("\n\t[You WON the game]\n");
                }
                else{
                    // FOr computer win or user lose
                    printf("\n\t[You LOSE the game]\n");
                }
                // Play again menu
                printf("\n\tRock Paper Scissor\n");
                printf("##################################\n\n");
                printf("[1] Play again\n");
                printf("[2] Exit\n");
                printf("Enter your option: ");
                scanf("%d", &nextoption);
                if (nextoption >2 || nextoption <1){
                    printf("Enter a valid option.");
                    option =0; // Reset to show the welcome message again
                }
                else if(nextoption == 2){
                    printf("Thank You! Come Again.");
                    break;
                }
                else {
                    option =1;
                    printf("\n");
                }
            }
        }
    }
}
