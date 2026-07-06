# Simple Calculator

The main idea is to create a program which we can use to **add**, **subtract**, **multiply**, **divide**, and **modulus** the two numbers which was given as a input by the user. It's a very basic program, there is no advance level thing in this. Just a normal and basic program is this.

### Library

In this program we just want ```stdio``` library. Because we need to get the input from user and show them the output. For the input and output we need to include the ```stdio``` library.

### Welcome

When the user runs the program, they wants to know what this program does and what are the inputs we need to give to the program. For that purpose I designed the welcome message which was given below,

```
[1] Addition
[2] Subtraction
[3] Multiplication
[4] Division
[5] Modulus
[6] Exit

Enter your option: 
```

So now user can understand what the program does and what they need to enter. When they enter what operation they need to do we get that input by ```scanf``` and store it in the variable named **option**.

### Addition

When the user enters option 1, the addition is carried out. After entering the option 1 the program asks the user to enter two numbers.

```
Enter number 1: 
Enter number 2:
```

They need to enter numbers based on that the operation is carried out and the output is displayed.

### Subtraction

When the user enters option 2, the subtraction is carried out.
After entering the option 2 the program asks the user to enter two numbers.

```
Enter number 1:
Enter number 2:
```

They need to enter numbers based on that the operation is carried out and the output is displayed.

### Multiplication

When the user enters option 3, the multiplication is carried out. After entering the option 3 the program asks the user to enter two numbers.

```
Enter number 1:
Enter number 2:
```

They need to enter numbers based on that the operation is carried out and the output is displayed.

### Division

When the user enters option 4, the division is carried out. After entering the option 4 the program asks the user to enter two numbers.

```
Enter number 1:
Enter number 2:
```

They need to enter numbers based on that the operation is carried out and the output is displayed. If the user enter number 2 as zero(0), the program shows error.

```
division by zero is not possible
```

### Modulus

When the user enters the option 5, the modulus is carried out.
After entering the option 5 the program asks the user to enter two numbers.

```
Enter number 1:
Enter number 2:
```

They need to enter numbers based on that the operation is carried out and the output is displayed. If the user enter number 2 as zero(0), the program shows error.

```
Modulus by zero is not possible
```

### Exit

When the user enters the option 6, the user exit from the program.

### Errors

When the user enters the option greater than 6 and less than 1, the program shows error and goes to the welcome page.

```
Invalid option

[1] Addition
[2] Subtration
[3] Multiplication
[4] Division
[5] Modulus
[6] Exit

Enter your option: 
```

### Info

I made the operation(addition, subtraction, ...) in switch case. But we also can do that in if statements. If you guys ask why I use switch case, the answer is I don't know. I just do that, don't know why.

### Feedback
Guys I a just a beginner, if you see any mistakes in either in program or in the documentation please feel free to point out it. Let's learn together.

### Code 
```c
/*
	This program is written by Ajay E at 02/07/2026
*/
#include <stdio.h>

int main() {
	int option, num1, num2;
	while (1==1) {
		// Welcome message
		printf("[1] Addition\n[2] Subtraction\n[3] Multiplication\n[4] Division\n[5] Modulus\n[6] Exit\nEnter a number to do that operation: ");
		scanf("%d", &option);
		// For exit
		if (option == 6){
			break;
		}
		// For invalid option
		else if (option <1 || option >6){
			printf("Invalid option.\n");
			continue;
		}
		// For valid option
		else {
			printf("Enter number 1: ");
			scanf("%d", &num1);
			printf("Enter number 2: ");
			scanf("%d", &num2);
			
			switch (option) {
				case 1:
					// Addition
					printf("%d\n", num1+num2);
					break;
				case 2:
					// Subtraction
					printf("%d\n", num1-num2);
					break;
				case 3:
					// Multiplication
					printf("%d\n", num1*num2);
					break;
				case 4:
					// Division
					if (num2 == 0){
						printf("Division by zero is not possible\n");
						break;
					}
					else {	
						printf("%.4f\n", (float)num1/num2);
						break;
					}
				case 5:
					// Modulus
					if (num2 == 0){
						printf("Modulus by zero is not possible\n");
						break;
					}
					else {
						printf("%d\n", num1%num2);
						break;
					}
			}
		}
	}
	return 0;
}
```