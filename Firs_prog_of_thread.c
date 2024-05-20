/*First program for making thread
The following are the parameters in the pthread_create function.
	handler to thread
	attributes to thread like stack size, schudling policy, 
	Function pointer.
	argument to function
	pass structure variable which contains the  else pass NULL
*/


/*
Ulinke fork 
Pthread when successufly creation returns 0.
*/

/*pthread_create(&thread_id, &pthread_attribute, func_ptr, arg_of_fun)*/

/*to find the thread id in PS command write
ps - elf -o LWP
*/

#include <stdio.h>
#include <pthread.h>//thread library 
#include <unistd.h>//library for getid().

//structure for passing argument
typedef struct arg
{
	int a;
	int b;
}arg1;


void* display(void *);//basic print function declaration here I have given parameter as void therefore the void* in parameter
void* add(void *arg);//function for accessing the struct var.
void* add2(void *arg2);// function for updating the struct var and then adding

//thread variables
pthread_t thread_1; //thread struct var
pthread_t thread_2; //thread struct var
pthread_t thread_3; //thread struct var

int main(void)
{
	arg1 argument = {5,5};// initilization of struct var  
	void **t_stat = NULL;// to catch the exit status of thread


	printf("\nParent process PID: %d PPID: %d", getpid(), getppid()); // to print the pid & ppid of main.
	int thread_stat = pthread_create(&thread_1, NULL,display, NULL); //creating thread
	int thread_stat2 = pthread_create(&thread_2, NULL,add, (void*)&argument); //creating thread & passing the struct var pointer as void type
	int thread_stat3 = pthread_create(&thread_2, NULL,add2, (void*)&argument); //creating thread & passing the struct var pointer as void type
	
	//Till here the execution of main will be done.
	pthread_join(thread_1, t_stat);			    // By this line the parent will wait till the thread is sucessfully executed.
	pthread_join(thread_2, t_stat);			    // By this line the parent will wait till the thread is sucessfully executed.
	pthread_join(thread_3, t_stat);			    // By this line the parent will wait till the thread is sucessfully executed.


	return 0;
}


/*Display function defination for printing the numbers from 1 to 6*/
void* display(void *)
{
	printf("\nThread 0 ID: %ld",pthread_self());
		for (int i = 1; i <= 6; ++i)
		{
			printf("\n %d", i);
		}	
	while(2); // to avoid termination of thread 1.
	
	
}//display ends


/*Add function defination
Here in this function we have passed the pointer to the structure as void 
for accessing the structure here we again have to typecast the structure pointer to struct data type
and then assign it to a local var (this is done in the line  arg1 locat_ptr = *(arg1*)(arg))
where arg is the pointer passed
local_ptr is the local var of struct*/
void* add(void *arg)// Add function defination.
{
	// arg1 local;//made a local var for struct.			
	// local = *(arg1*)(arg);// typecasted the void arg to struct data type and derefer it.
	// printf("\n addition: %d",  local.a + local.b);

	printf("\nThread 1 ID: %ld", pthread_self());
	arg1 local_ptr = *(arg1*)(arg);
	printf("\naddition : %d\n", local_ptr.a + local_ptr.b);
	while(2);
}//display ends

/*In this function we are updating the structure member*/
void* add2(void *arg2)// Add 2 function defination.
{
	printf("\nThread 2 ID: %ld", pthread_self());
	arg1 local_ptr = *(arg1*)(arg2);

	local_ptr.a = 23;
	printf("\naddition : %d\n", local_ptr.a + local_ptr.b);
	while(2);
}//display ends

