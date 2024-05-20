/*
	Author: Nishant Thosar
	Date: 20/May/2024
	Place: CDAC 
*/
/* First program of pthreads*/

/*In this program we are creating two thread with thread1 & thread2 thread variables which are calling the same function
(ie: func()).
*/


#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void* func();//function declaration

pthread_t thread1,thread2; // thread variables

int main()
{
	int apt;  // for catching the exit status of thread 1 (this is throwing warning while compling)
	void *t_exit_stat = NULL;//for catching the ext status of thread 2.
	int thread = pthread_create(&thread1, NULL,func,NULL);// creating thread 2.
	pthread_join(thread1,&apt); //to wait the main process until the thread is done executing
	printf("\nExit_status of thread1: %p", apt);// to print the exit status of thread.

	int thread_2 = pthread_create(&thread2, NULL,func,NULL);// creating the thread 2
	pthread_join(thread2,&t_exit_stat); // to wait the main process unless the thread is done executing.
	printf("\nExit_status of thread2: %p", ((int*)t_exit_stat)); // to print the exit status of thread 
	return 0;
}

//Function to print the thread.
void* func()
{
	for (int i = 0; i < 7; ++i)
	{
		printf("\n%d", i);
	}
	// while(1);
}