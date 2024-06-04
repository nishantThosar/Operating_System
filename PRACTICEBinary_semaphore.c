/*Binary semaphore program*/

#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>

long int shared = 1;
sem_t s; // semaphore variable.

void* func1();
void* func2();


int main(int argc, char const *argv[])
{
	pthread_t thread_id[2]; // array of thread id
	sem_init(&s,0,1); // initilization of semaphore.

	pthread_create(&thread_id[0], NULL, func1, NULL);
	pthread_create(&thread_id[1], NULL, func2, NULL);
	
	pthread_join(thread_id[0],NULL);
	pthread_join(thread_id[1],NULL);
	printf("\nShared: %ld", shared);
	return 0;
}

void* func1()
{
	sem_wait(&s);
	
	printf("\nIn func1");
	for (int i = 0; i < 90; ++i)
	{
		shared++;
	}
	sem_post(&s);
}

void* func2()
{
	sem_wait(&s);
	printf("\nIn func2");
	for (int i = 0; i < 91; ++i)
	{
		shared--;
	}
	sem_post(&s);
}
