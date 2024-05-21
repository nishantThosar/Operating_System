/*Pthreads program with structure*/

/*
	OUTPUT SCREENSHOT: 	https://drive.google.com/file/d/1H5NppOYzzNJM6p8kKRRj4PC_0ajjs8Y_/view?usp=sharing
	Author : Nishant Thosar
	Date: 21/MAY/2024
	Time: 10:02
	Place: CDAC
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h> // library for thread operations.
#include <stdlib.h>

//structure for passing arguments to function.
typedef struct func_arguments
{
	int a;
	int b;

}var;

/*----------------------------------------------Function prototypes--------------------------------------------*/
void* add(void *); // addition function in which void pointer is passed as a parameter.
void thread_check(int); // function to check if the thread is successfully made or not.
void thread_wait(int); // function to check if the process is waiting for the thread to execute or not.

/*---------------------------------------------Global Pthread Variables----------------------------------------*/
pthread_t thread_1; // thread var.
var *s_ptr = NULL; // structure pointer.

/*-----------------------------------------------Main func start-----------------------------------------------*/
int main(void)
{
	printf("\nProcess start");// to know the process has been started.
	int thread1 = pthread_create(&thread_1, NULL,add,(void *)&s_ptr); // making thread and passing the arguments of function.
	thread_check(thread1); // to check if the thread is made or not.
	int join = pthread_join(thread_1, NULL);// for asking the process to wait till the execution of thread
	thread_wait(join); // to check if the process waited or not.

	return 0;
}//main ends

/*-----------------------------------------------Add Function--------------------------------------------------*/
/* This function is called by thread.
In this function we are
0) Getting the thread ID.
1) Passing structure pointer as null pointer
2) Typecasting it and accessing members of it.
3) Modifying the structure members.
4) Adding the values of members
5) Printing the addition. */
void* add(void *arg)
{
	printf("\tThread ID: %ld", pthread_self());// to get the thread ID.

	var local_var = *(var*)arg; // casting the void pointer passed in the function to struct type again.

	//User input for modifying the structure
	printf("\nEnter the value of a: ");
	scanf("%d", &local_var.a); // modifying the "a" member of structure
	printf("\nEnter the value of b: ");
	scanf("%d", &local_var.b); // modifying the "b" member of structure.
	printf("\nAddition : %d", local_var.a+local_var.b);

	// sleep(10);// comment this if you don't want to find the thread in th top command.
}//add ends.






/*-----------------------------------------THESE ARE OPTIONAL FUNCTIONS----------------------------------------*/






/*---------------------------------------------Thread check function--------------------------------------------*/
/*This function checks if the thread is created or not
if the kernal failes to make thread then it exits the progam.*/
void thread_check(int thread)
{
	if(thread < 0)
	{
		perror("Error in making thread");
		exit(0); 
	}// if ends
	else if (thread == 0)
	{
		printf("\nThread Created SUCESSFULLY");
		return;
	}//else if ends
}//thread check function ends

/*--------------------------------------------Thread return function--------------------------------------------*/
/*This function checks if the parent process is waiting for thread to execute fully or not*/
void thread_wait(int joint)
{
	if(joint == 0)
	{
		printf("\nParent process waited till the thread to execute.\n");
	}// if ends
	else if (joint != 0)
	{
		printf("\nError parent killed or didn't wait to execute the thread.");
	}//else if ends
}//thread wait ends

