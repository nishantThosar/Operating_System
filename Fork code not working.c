/*For binary semaphore with fork*/

/*Binary semaphore program*/

#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/wait.h>

sem_t s; // semaphore variable.

void* func1();
void* func2();

pthread_mutex_t mutex; // mutex var
long int shared;

int main(int argc, char const *argv[])
{
	pthread_t thread_id[2]; // array of thread id
	pthread_mutex_init (&mutex, NULL);
	sem_init(&s,0,1); // initilization of semaphore.

	pid_t ret = fork();
	if (ret < 0){perror("\nError in fork1");return -1;}

	if (ret == 0)
	{
		printf("\nIn child 1 PID: %d, PPID: %d", getpid(),getppid());
		pthread_create(&thread_id[0], NULL, func1, (void*)&shared);		
		pthread_join(thread_id[0],NULL);
	}

	if (ret > 0)
	{

		printf("\nIn Parent PID: %d, PPID: %d", getpid(),getppid());
		pthread_create(&thread_id[1], NULL, func2, (void*)&shared);
		pthread_join(thread_id[1],NULL);
		wait(NULL);
		printf("\nThread 2 exited");
	}

	pthread_mutex_destroy(&mutex);
	printf("\nShared: %ld\n", shared);
	return 0;
}

void* func1(void *arg)
{
	long int *ptr = (long int*)arg;
	sem_wait(&s);
	
	printf("\nIn func1");
	for (int i = 0; i < 90; ++i)
	{
		pthread_mutex_lock(&mutex);
		*ptr = i;
		
		pthread_mutex_unlock(&mutex);

	}
	printf("\nShared after fun1: %ld", *ptr);
	sem_post(&s);
	sleep(1);
}

void* func2(void* arg)
{
	long int *ptr = (long int*)arg;
	// sleep(1);
	sem_wait(&s);
	printf("\nIn func2");
	printf("\nShared before fun2: %ld", *ptr);
	for (int i = 0; i < 90; ++i)
	{
		pthread_mutex_lock(&mutex);
		printf("\nvalue in i = %ld", *ptr);
		pthread_mutex_unlock(&mutex);
	}
	sem_post(&s);
	sleep(1);
}
