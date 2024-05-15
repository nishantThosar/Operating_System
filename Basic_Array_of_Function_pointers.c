/*Array of function pointer*/

/*
	Author: Nishant Thosar
	Date: 15 May 2024
	Place CDAC
*/


#include <stdio.h>

//func ptorotypres
void add(int, int);
void sub(int, int);
void mul(int, int);
void div(int, int);
void mod(int, int);

void main(void)
{
	int a,b, choice;
	void(*func_ptr_arr[])(int ,int) = {add,sub,mul,div,mod}; //declaration and initilization of function pointer array.

while(1)
{
	//Menu
	printf("1.Add\t2.Sub\t3.Mul\t4.Div\t5.Mod ");
	printf("\n0 to EXIT\nEnter a number: ");
	scanf("%d", &choice);

	printf("\nEnter the vlaue of a: ");
	scanf("%d", &a);
	printf("\nEnter the vlaue of b: ");
	scanf("%d", &b);


	  switch (choice) 
	  {
	  	case 0:
	  	  return;
	    case 1:
	      func_ptr_arr[0](a,b);					//Add function call with parameters a & b.
	      break;
	    case 2:
	      func_ptr_arr[1](a,b);					//Sub function call with parameters a & b.
	      break;
	    case 3:
	      func_ptr_arr[2](a,b);					//mul function call with parameters a & b.
	      break;
	    case 4:
	      func_ptr_arr[3](a,b);					//div function call with parameters a & b.
	      break;
	    case 5:
	      func_ptr_arr[4](a,b);					//mod function call with parameters a & b.
	      break;
	    default:
	      printf("Invalid choice. Please enter a number between 1 and 5.\n");
	  }//switch ends
}//while ends
	// for (int i = 0; i < 5; ++i)
	// {
	// 	func_ptr_arr[i](a,b);
	// }
}//main ends

//Function definations
void add(int a, int b){printf("Addition: %d\n", a+b);}
void sub(int a, int b){printf("Subtraction: %d\n", a-b);}
void mul(int a, int b){printf("Multiplication: %d\n", a*b);}
void div(int a, int b){printf("Division: %d\n", a/b);}
void mod(int a, int b){printf("Mod: %d\n", a%b);}
