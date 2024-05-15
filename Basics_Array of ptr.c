/*Program for array of int/char pointer*/
/*In this program array demonstration of array of pointers is done*/

/*
	Author: Nishant Thosar
	Date: 15 May 2024
	Place CDAC
*/

#include<stdio.h>
#include<stdlib.h>

int main(int argc, char const *argv[])
{
	//Temp var
	int a = 10;
	int b = 20;
	int c = 30;

	//initilization of arr pointer.
	int *arr[3] = { &a,&b,&c };
	for (int i = 0; i < 3; ++i)
	{
		printf("arr[%d]: %d\n", i,*arr[i]);
	}//for ends




	//array of char pointer is initilized.
	char *ch[] = {"Nishant","Thosar", "Mayur"}; //This will be stored in SLP.
	for (int i = 0; i < 3; ++i)
	{
		printf("ch[%d] :%s\n", i, ch[i]);
	}
	return 0;
}
