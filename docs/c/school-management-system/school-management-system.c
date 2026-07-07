/*
    This program is written by Ajay E at 07/07/2026
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store the students data
struct schoolDatabase {
    char name[50];
    long mobile;
    char gender;
    char dob[11];
};

// Global variable

struct schoolDatabase *student = NULL;
int total_student = 1000;
int studentCount = 0;
int maleCount = 0;
int femaleCount = 0;

//Function Declaration
void initializeDatabase();
void addStudent(char *studentName, char gender, char *dob, long mobile);
void updateStudent();
void findStudent();
void countStudent();
void cleanupDatabase();

// Function to initialize the database
void initializeDatabase(){
    student = (struct schoolDatabase *)malloc(total_student * sizeof(struct schoolDatabase));
    if (student == NULL){
        printf("Memory Allocation Failed.");
        exit(1);
    }
}

// Function to add the new student
void addStudent(char *studentName, char gender, char *dob, long mobile){
    if (studentCount >= total_student){
        printf("The database is full.");
        return;
    }

    snprintf(student[studentCount].name, sizeof(student[studentCount].name), "%s", studentName);
    snprintf(student[studentCount].dob, sizeof(student[studentCount].dob), "%s", dob);
    student[studentCount].gender = gender;
    student[studentCount].mobile = mobile;
    if (student[studentCount].gender == 'M'){
        maleCount +=1;
    }else{
        femaleCount +=1;
    }
    studentCount +=1;
    printf("Student Details added successfully");
    return;
}

// Function to update student's details
void updateStudent(){
    int option, found = 0;
    char studentName[50], dob[11], changeName[50];
    char gender;
    long mobile;

    if (studentCount == 0){
        printf("The database is empty");
        exit(1);
    }

    //Update menu
    printf("\nSchool Management System\n");
    printf("#########################\n\n");
    printf("--- Student detail's update ---\n");
    printf("[1] For name change\n");
    printf("[2] For gender change\n");
    printf("[3] For dob change\n");
    printf("[4] For mobile change\n");
    printf("[5] Exit\n");
    printf("Enter your option: ");
    scanf("%d", &option);
    // FIX: Clear the buffer right here before fgets tries to read the name!
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 
    if (option == 5) {
        return;
    }
    printf("Enter the student name you want to change: ");
    fgets(studentName, sizeof(studentName), stdin);
    studentName[strcspn(studentName, "\n")] = '\0';

    //Check if the student is in the database
    for (int i = 0; i<studentCount; i++){
        if (strcmp(student[i].name, studentName) == 0){
            switch (option){
                case 1:
                    printf("Enter a name to change: ");
                    fgets(changeName, sizeof(changeName), stdin);
                    changeName[strcspn(changeName, "\n")] = '\0';
                    snprintf(student[i].name, sizeof(student[i].name), "%s", changeName);
                    printf("\nName changed successfully.");
                    found = 1;
                    break;
                case 2:
                    printf("Enter gender to change (M/F): ");
                    scanf(" %c", &gender);
                    // Fix: Update global totals dynamically before changing the struct value
                    if (student[i].gender != gender) {
                        if (student[i].gender == 'M') {
                            maleCount--;
                        } else {
                            femaleCount--;
                        }
                        
                        if (gender == 'M') {
                            maleCount++;
                        } else {
                            femaleCount++;
                        }
                    }
                    
                    student[i].gender = gender;
                    printf("\nGender changed successfully.");
                    found = 1;
                    break;
                case 3:
                    printf("Enter a dob to change dd/mm/yyyy: ");
                    fgets(dob, sizeof(dob), stdin);
                    dob[strcspn(dob, "\n")] = '\0';
                    snprintf(student[i].dob, sizeof(student[i].dob), "%s", dob);
                    printf("\nDob Changed successfully.");
                    found = 1;
                    break;
                case 4:
                    printf("Enter mobile number to change: ");
                    scanf("%ld", &mobile);
                    student[i].mobile = mobile;
                    printf("Mobile number changed successfully.");
                    found = 1;
                    break;
                default:
                    printf("Enter a valid option");
            }
            break;
        }
    }
    if (!found){
        printf("Student is not found in the database");
    }
}

// Function to find the student

void findStudent(){
    char studentName[50];
    int found = 0;
    printf("Enter a name to find: ");
    fgets(studentName, sizeof(studentName), stdin);
    studentName[strcspn(studentName, "\n")] = '\0';
    
    for (int i = 0 ; i < studentCount; i++){
        if (strcmp(student[i].name, studentName) == 0){
            printf("Name: %s\n", student[i].name);
            printf("DOB: %s\n", student[i].dob);
            printf("Gender: %c\n", student[i].gender);
            printf("Mobile: %ld\n", student[i].mobile);
            found = 1;
            break;
        }
    }
    if (!found){
        printf("\nStudent details is not found in the database");
    }
}

// Function to count students in the school
void countStudent(){
        printf("\nTotal student in the school is %d", studentCount);
        printf("\nMale: %d", maleCount);
        printf("\nFemale: %d", femaleCount);
        return;
}

// Function to cleanup the database

void cleanupDatabase(){
    if (student != NULL){
        free(student);
        student = NULL;
    }
}

int main(){
    int option;
    char studentName[50], dob[11];
    char gender;
    long mobile;

    // Initializing the database;
    initializeDatabase();


    while (1){
        // Welcome message
        printf("\nSchool Management System\n");
        printf("#########################\n\n");
        printf("[1] Add Student\n");
        printf("[2] Update Student\n");
        printf("[3] Find Student\n");
        printf("[4] Count Student\n");
        printf("[5] Exit\n\n");
        printf("Enter your option: ");
        scanf("%d", &option);

        // Add this here too to protect the studentName fgets() below it
        int c;
        while ((c = getchar()) != '\n' && c != EOF); 
        switch (option){
            case 1:
                printf("\nEnter the student name: ");
                fgets(studentName, sizeof(studentName), stdin);
                studentName[strcspn(studentName, "\n")] = '\0';
                printf("Enter the student gender(M/F): ");
                scanf(" %c", &gender);
                // FIX 1: Clear buffer here so the next fgets() doesn't get skipped!
                while ((c = getchar()) != '\n' && c != EOF); 
                printf("Enter the student dob as dd/mm/yyyy: " );
                fgets(dob, sizeof(dob), stdin);
                dob[strcspn(dob, "\n")] = '\0';
                // FIX 2: Clear buffer here so the main menu loop option works cleanly next time!
                while ((c = getchar()) != '\n' && c != EOF); 
                printf("Enter student mobile: ");
                scanf("%ld", &mobile);

                // Calling the function named addStudent;
                addStudent(studentName, gender, dob, mobile);
                break;

            case 2:
                updateStudent();
                break;
            
            case 3:
                findStudent();
                break;
            case 4:
                countStudent();
                break;
            case 5:
                cleanupDatabase();
                exit(0);
            default:
                printf("Invalid Option try again.");
        }
    }
}