/*
    This program is written by Ajay E at 10/07/2026
*/

#include <stdio.h>
#include <string.h>

// Function declaration
void encryption();
void decryption();

// Function to encrypt the given text
void encryption(){
    char ch, string[1024], encrypt[1024];
    int key, c;
    //To clear the newline buffer
    while ((c = getchar()) != '\n' && c != EOF);
    printf("\nEnter a sentence: ");
    fgets(string, sizeof(string), stdin);
    string[strcspn(string, "\n")] = '\0';
    printf("Enter a key: ");
    scanf("%d", &key);
    int i;
    for (i = 0; string[i] != '\0'; i++){
        ch = string[i];
        //For lower case
        if (ch>= 'a' && ch <= 'z'){
            ch = (ch - 'a' + key)%26 + 'a';
            encrypt[i] = ch;
        }
        //For upper case
        else if (ch>= 'A' && ch <= 'Z'){
            ch = (ch - 'A' + key)%26 + 'A';
            encrypt[i] = ch;
        }
        //Other than lower and uppercase
        else{
            encrypt[i] = string[i];
        }
    }
    encrypt[i] = '\0'; //Null terminator to tell the end of the string
    printf("The encrypted text is: %s", encrypt);
    printf("\nThe key is: %d", key);
    return;
}

//Function to decrypt the encrypted text
void decryption(){
    char ch, string[1024], decrypt[1024];
    int key, c;
    //For clearing the newline buffer
    while ((c = getchar()) != '\n' && c != EOF);
    printf("\nEnter a sentence: ");
    fgets(string, sizeof(string), stdin);
    string[strcspn(string, "\n")] = '\0';
    printf("Enter a key: ");
    scanf("%d", &key);
    int i;
    for (i = 0; string[i] != '\0'; i++){
        ch = string[i];
        //For lower case letters
        if (ch>= 'a' && ch<= 'z'){
            ch = (ch - 'a' - key + 26)%26 + 'a';
            decrypt[i] = ch;
        }
        //For upper case letters
        else if (ch>='A' && ch<='Z'){
            ch = (ch - 'A' - key + 26)%26 + 'A';
            decrypt[i] = ch;
        }
        //Letters other than lower case and upper case
        else {
            decrypt[i] = string[i];
        }
    }
    decrypt[i] = '\0';//Null terminator to tell this is the end of the string

    printf("The decrypted tex is: %s", decrypt);
    return;
}

int main(){
    int choice;
    // Welcome message
    while (1){
        printf("\n--- CAESAR CHIPER ---\n\n");
        printf("[1] Encryption\n");
        printf("[2] Decryption\n");
        printf("[3] Exit\n");
        printf("Enter your option: ");
        scanf("%d", &choice);

        switch (choice){
            //Case for encryption
            case 1:
                encryption();
                break;
            //Case for decryption
            case 2:
                decryption();
                break;
            //Case for exit
            case 3:
                return 0;
        }
    }
}