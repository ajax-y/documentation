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
