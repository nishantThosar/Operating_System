/*Int Pointer array*/
//Program for making and accessing int values in an int pointer array.
/*
Author Nishant Thosar
Date: 14 May 2024
Place CDAC
*/


#include <stdio.h>
#include<stdlib.h>

int main(int argc, char const *argv[])
{
	system("clear");
	int *arr[3];//int pointer array of size 3.

	//int var to store in array;
	int var1 = 10;
	int var2 = 20;
	int var3 = 30;

	//initilization of int pointer array.
	arr[0] = &var1;
	arr[1] = &var2;
	arr[2] = &var3;

	//initilization of array can be done like this too
	int *arr_2[3] = { &var1, &var2, &var3 }; //I have taken another array for showing other type of initilization.


	for (int i = 0; i < 3; ++i)
	{
		printf("arr[%d]: %d\n",i+1, *arr[i]);
	}

	//for printing array initilized by other method.
	printf("\nPrinting another array below\n");
	for (int i = 0; i < 3; ++i)
	{
		printf("arr[%d]: %d\n",i+1, *arr_2[i]);
	}
	return 0;
}
