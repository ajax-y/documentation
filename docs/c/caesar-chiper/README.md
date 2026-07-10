# Caesar Chiper

This program used to encrypt and decrypt the text based upon the character shift. It's completely based upon the ASCII values. The concept is very simple, we need to ask the text from the user and, also key from the user. Based upon the key we shift only the alphabets, we don't gonna touch the numbers, space, special symbols.

### Library

In this program I used two library namely ```stdio``` and, ```string```. ```stdio``` used for the input and output operations. From ```string``` I used ```strcspn()``` in this program.

### Function Declaration

In this program I just used two functions namely ```encryption()``` and ```decryption()```. 

1. ```encryption()```: is used to get the normal text from the user and, also a key. Then it iterate through the text and shift it based upon the key. It not shift the numbers, space, symbols. Then display both encrypted text and, also the key.

2. ```decryption()```: is used to get the encrypted message from the user and, also the key. Then it shift the characters to their original form. It not shift the numbers, space, and symbols.

### Welcome

When the program starts the welcome message is displayed show the user what the program does. 

```
--- Caesar Chiper ---

[1] Encryption
[2] Decryption
[3] Exit
Enter your option: 

```

It shows the user that it encrypt and decrypt the message.

### Encryption

When the user choose option 1, it ask the user for the text and the key.

```
Enter a sentence:
Enter a key:
```

And it store the text to a variable, then it iterate through the string and check if the character is lowercase or uppercase or not. If it lower case it do the character shift by this ```ch = (ch - 'a' + key)%26 + 'a'``` and if it uppercase it do the character shift by ```ch = (ch - 'A' + key)%26 + 'A'``` and at last it diplay the encrypted text and the key.

### Decryption

When the user choose option 2, it ask the user for the text and the key.

```
Enter a sentence: 
Enter a key:
```

And it store the text to a variable, the it iterate through the string and check the character is lowercase or uppercase or not. If it lowercase it shift the character based on this ```ch = (ch - 'a' - key + 26)%26 + 'a'``` and for upper case ```ch = (ch - 'A' - key + 26)%26 + 'A'```. At last it diplay the  the decrypted message.

### Info

In the program there is new line buffer I did many attempt to solve it but later ask gemini for the solution.

### Code

```c
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
```