/*Thread program to make thread and mutex*/

#include <Program_shared_IPC.h>
//#define pthread_mutex_t PTHREAD
// #define pthread_mutex PTH

void *print_t(void *);
void *update(void *);

//Mutual execlusive structure.
typedef struct
{
	int a;
	int b;
}shar;

shar shared; // structure var.

int counter;

pthread_mutex_t lock; // mutex structure variable named as "lock".

int main(void)
{
	int i = 0;
	int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
	pthread_t thread_id[2]; //to store the currently created thread ID
	
	
	int stat = pthread_create(&thread_id[0], NULL,update,(void*)&shared);//creating the thread.
	if(stat != 0){perror("\nError in making thread1");exit(1);}//if thread is not created then exit the program.
	printf("\nTread 1 made\n\n");//just to print the number of thread.
	
	int stat2 = pthread_create(&thread_id[1], NULL,print_t,(void*)&shared);//creating the thread.
	if(stat2 != 0){perror("\nError in making thread2");exit(1);}//if thread is not created then exit the program.
	printf("\nTread 2 made\n\n");//just to print the number of thread.


	pthread_join(thread_id[0],NULL); // to block the process from where the thread is created to wait till the thread is done execution.
	pthread_join(thread_id[1],NULL); // to block the process from where the thread is created to wait till the thread is done execution.
	printf("\nTotal times mutex used: %d\n\n", counter);
	return 0;
}

//Printing the value of structure
void *print_t(void *arg)
{
	pthread_mutex_lock(&lock); // locking the mutex.
	counter ++;

	shar *sh = (shar*)arg; // again typecasting it in struct data type.
	printf("\nThread ID: %ld",pthread_self());// to print the thread ID.
	printf("\nValue of a: %d", sh->a);
	printf("\nValue of b: %d", sh->b);

	printf("\nWriting finished");
	pthread_mutex_unlock(&lock);// unlocking the mutex
}//print function ends

void *update(void *arg2)
{
	pthread_mutex_lock(&lock); // locking the mutex.
	counter ++;
	shar *sh = (shar*)arg2;// again typecasting it in struct data type.
	printf("\nThread ID: %ld",pthread_self());// to print the thread ID.
	printf("\nEnter value of a: ");
	scanf("%d", &sh->a);
	printf("\nEnter value of b: ");
	scanf("%d", &sh->b);
	pthread_mutex_unlock(&lock);// unlocking the mutex
}



