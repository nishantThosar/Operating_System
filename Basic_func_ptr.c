/*Prog of using function pointer */

#include <stdio.h>
#include<stdlib.h>

void add(int,int);					// declaration of add function.

int main(int argc, char const *argv[])
{
	system("clear");
	int a,b; // temp var for user input

	//scanning the user input.
	printf("\nEnter the first number ");
	scanf("%d", &a);
	printf("\nEnter the second number ");
	scanf("%d", &b);

	void (*func_ptr)(int,int) = &add; // Declaration and initliization of function pointer at a line.


	/*We can also declare and initilize the function pointer on seprate lines
	
	void(*func_ptr)(int,int); 	// declaration of function pointers.
	func_ptr = &add; 			// initilization of function pointer.
	*/

	(*func_ptr)(a,b); // calling the function through function pointer.


	return 0;
}//main ends


void add(int a, int b)
{
	printf("Addition: %d\n",a+b);
}//add func ends
