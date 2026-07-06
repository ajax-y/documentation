# Bank Management System

This program is written to recreate the small bank application like. It has a option to create account or login to the existing account and can check the balance, deposit the amount and withdraw the amount form the account. All the data are stored in the file named database.csv and we can retrive the data from the file.

### Library

In this program we used three library namely, ```stdio``` , ```stdlib``` and ```string```. Every library has it's own use in the program.

### Structure

I created a structure named bankAccount. At first I want to create this project based upon the structure later I developed by using the file. But still I use the structure in some place in the program.

### Function

I created and used three functions in the program namely, ```createAccount```, ```login```, ```accountDashboard```. Each has its own functionality.
1. **createAccount: ** This function mainly used to create the new bank account. If the account already exists it throws the error message.
2. **login: ** This function is mainly used to login to the existing account and check whether the given account number and pin is correct or not.
3. **accountDashboard: ** This function is used after the user login to the account. By using this function the user can see their balance, withdraw the money, deposit the money.

### Welcome

When the program starts executing it need to say what it does and what are the input we need to give to it. For that purpose I showed the welcome message at the staring.

```
    Bank Management System
###############################

[1] Create Account
[2] Login
[3] Exit

Enter your option: 
```

When the user enter option 1 it ask for your name, and pin you need to use for your bank account, and Date of birth for the generation of the account number. By all this data it runs the function named createAccount and creates the account for the user

When the user enter option 2 it ask for the account number and pin for the account. By using it runs the function named login and check the account is exists or not and the pin is valid or not.

When the user enter option 3. The program exit.

When the user enter the option which is greater than 3 and less than 1 and it throws the error.

### Account Dashboard

When the user enter the option 2 for login to the account. If the account is logged in, the program displays some of the options,

```
Login Successfull

    Bank Management System
--- User Dashboard ---

[1] Check balance
[2] Withdrawal
[3] Deposit
[4] Exit

Enter your option: 
```

When the user enter the option 1, the program check the account and displays the balance in the account.

When the user enter the option 2, the program it ask the amount to withdraw the money from the account. If the account not contains the amount it throws the error.

When the user enter the option 3, the program it ask the amount to deposit to the account.

When the user enter the option 4, the program exit.

### Info

I think there is many error and mistakes in the program but I don't know. I am sure that you guys can easily able to find the mistakes please point it out. And one thing I don't know why I still has the structure in the program.

### Code

```c
/*
    The program is written by Ajay E at 03/07/2026
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structer to handle the values
struct bankAccount {
    char name[25];
    long long accountNumber;
    char pin[5];
    double balance;
};

// Declaration of the functions
void createAccount(char user_name[], char PIN[], int d, int m, int y);
int login(long long acNumber, char PIN[]);
void accountDashboard(long long acNumber);

// Function to create the account
void createAccount(char user_name[], char PIN[], int d, int m, int y){
    struct bankAccount new_user;
    FILE *file; // For accessing the database file named database.csv
    char acNumber[25];

    strcpy(new_user.name, user_name);
    strcpy(new_user.pin, PIN);

    // Creating the account number
    sprintf(acNumber, "%02d%02d%s%02d", d, m, PIN, y);
    new_user.accountNumber = atoll(acNumber);

    // Opening the file to append the new user
    file = fopen("database.csv", "a");
    if (file == NULL){
        printf("Error while opening database file for writing!\n");
        return;
    }
    
    // Writing the new user's details to the database.csv file
    fprintf(file, "%s,%lld,%s,%.2f\n", new_user.name, new_user.accountNumber, new_user.pin, 0.0);
    fclose(file);

    printf("Your account is created successfully.\n");
    printf("Your Account Number is %lld", new_user.accountNumber);
}

// Function for login the account
int login(long long acNumber, char PIN[]){
    char temp_name[25], temp_pin[5];
    long long temp_acc;
    double temp_balance;
    FILE *file; // For accessing the database file named database.csv
    
    // Opening the database.csv to check if the user already exists
    file = fopen("database.csv", "r");
    if (file == NULL){
        printf("Please enter a valid details, account is not found.\n");
        return 0;
    }

    // Check if the accounNumber and the PIN is correct or not
    while (fscanf(file, "%[^,],%lld,%[^,],%lf\n", temp_name, &temp_acc, temp_pin, &temp_balance) != EOF){
        if (temp_acc == acNumber && strcmp(temp_pin, PIN) == 0){
            fclose(file);
            accountDashboard(acNumber);
            return 1;
        }
 
    }
    return 0;
}

// Function to show what are the thing we can do after login to the account
void accountDashboard(long long acNumber){
    int dashboardChoice;
    char temp_name[25], temp_pin[5];
    long long temp_acc;
    double temp_balance, dAmount, wAmount;
    FILE *file; // For opening the database named database.csv
    FILE *new_file;
    FILE *old_file;
    while (1){

        Welcome message
        printf("\n\tLogin successfull\n");
        printf("\tBank Management Systen\n\n");
        printf("---User Dashboard---\n");
        printf("[1] Check Balance\n");
        printf("[2] Withdrawal\n");
        printf("[3] Deposit\n");
        printf("[4] Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &dashboardChoice);
        file = fopen("database.csv", "r");
        if (file == NULL){
            printf("Database is not found.\n");
            return;
        }
        switch (dashboardChoice){
            case 1:

                // For checking the balance of the account
                while (fscanf(file, "%[^,],%lld,%[^,],%lf\n", temp_name, &temp_acc, temp_pin, &temp_balance) != EOF){
                    if (temp_acc == acNumber){
                        printf("---User Dashboard---\n");
                        printf("Your balance is %.2f", temp_balance);
                    }
                }
                fclose(file);
                break;
            case 2:
                
                // For withdrawing the money from the account
                fclose(file);
                printf("\nEnter amount to withdraw: ");
                scanf("%lf", &wAmount);
                if (wAmount<0){
                    printf("\nPlease enter a valid amount.");
                }
                old_file = fopen("database.csv", "r");
                new_file = fopen("temp.csv", "w");
                while (fscanf(old_file, "%[^,],%lld,%[^,],%lf\n", temp_name, &temp_acc, temp_pin, &temp_balance) != EOF) {
                    if (temp_acc == acNumber){
                        if (temp_balance >= wAmount){
                            temp_balance-=wAmount;
                        }
                    }
                    fprintf(new_file, "%s,%lld,%s,%.2f\n", temp_name, temp_acc, temp_pin, temp_balance);
                }
                fclose(new_file);
                fclose(old_file);
                remove("database.csv");
                rename("temp.csv", "database.csv");
                break;
            case 3:

                // For deposit the amount to the account
                fclose(file);
                printf("\nEnte amount to deposit: ");
                scanf("%lf",&dAmount);
                if (dAmount < 0){
                    printf("\nPlease enter a valid amount.");
                }
                old_file = fopen("database.csv","r");
                new_file = fopen("temp.csv","w");
                while (fscanf(old_file, "%[^,],%lld,%[^,],%lf\n", temp_name, &temp_acc, temp_pin, &temp_balance) != EOF) {
                    if (temp_acc == acNumber){
                        temp_balance+=dAmount;
                    }
                    fprintf(new_file, "%s,%lld,%s,%.2f\n", temp_name, temp_acc, temp_pin, temp_balance);
                }
                fclose(new_file);
                fclose(old_file);
                remove("database.csv");
                rename("temp.csv", "database.csv");
                break;
            case 4:
                
                // For exiting from the program
                return;
            default:

                // For invalid options
                printf("\nEnter a valid option.");
        }
    }
}


// Main function, start of the program
int main(){
    int welcomeChoice, d, m, y;
    char user_name[25], PIN[5];
    long long acNumber;
    while(1){
        // Welcome message
        printf("\tBank Management System\n");
        printf("############################################\n\n");
        printf("[1] Create Account\n");
        printf("[2] Login\n");
        printf("[3] Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&welcomeChoice);

        switch(welcomeChoice){
            case 1:

                // For creating the new bank account
                printf("\nCreating your Bank Account");
                printf("\nEnter your name: ");
                scanf("%25s", &user_name);
                printf("\nEnter your 4 digit PIN: ");
                scanf("%s", &PIN);
                printf("\nPlease Enter you DOB as DD MM YY as space separated: ");
                if (scanf("%d %d %d", &d, &m, &y)!=3){
                    printf("\nPlease enter as the formate");
                    return 1;
                }
                createAccount(user_name, PIN, d, m, y); // Function to create the account
                break;
            case 2:
                
                // For login to the account
                printf("\nLogging to your Bank Account");
                printf("\nEnter your Account Number: ");
                scanf("%lld", &acNumber);
                printf("Enter your PIN: ");
                scanf("%s", &PIN);
                login(acNumber, PIN); // Function to login to the account
                break;
            case 3:
                
                // For exit from the program
                return 0;
            default:

                // For invalid option
                printf("\nPlease enter a valid option: ");
        }
    }
}
```