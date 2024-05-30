/*Program for binary ssemaphore*/

/*1>> Using the shared memory IPC try to see race condition. Have one
    shared structure. Modify that in two different process.*/
/*In this program the race condition is occuring as */
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include <sys/sem.h>
#include<sys/shm.h> //for semaphore.

//union for semaphore
union semun
{
	int val;
}u1;

//shared memory
typedef struct shmem
{
	long int count;
	
}mem;

mem *shared = NULL;//shared memory pointer.

//user defined funct for getting and releasing the binary semaphore
void get(void);
void release(void);

int main(int argc, char const *argv[])
{
	int i=0; // for counting
	int j = 0; // for counting
	struct sembuf sembuf1; //struct var
	key_t key= ftok("q3a1",14); // to create key.
	key_t key1= ftok("q3a1",15);
	int id = shmget(key,1,IPC_CREAT|0600); // to create the shared memory  	
	if (id < 0){perror("\nError in shmget");exit(1);}

	int sem_id = semget(key1,1,IPC_CREAT | 0600); //create a shared memory for semaphore.
	if (sem_id < 0){perror("\nError in shmget for semaphore");exit(2);}	
	u1.val = 1;
	printf("u1.val: %d\n",u1.val);
	int ret1 = semctl(sem_id,0,GETVAL);
	if(ret1<0) { perror("error in semctl getting"); exit(4); }

   printf("current semaphore value is %d\n", ret1); 
	int ret = semctl(sem_id,0,SETVAL,u1);//setting the semaphore value.

	if (ret < 0){printf("Error\n"); perror("\nError in assigning value to semaphore5");exit(3);}

	shared = shmat(id,0,0); //to link the shared memory with the structure pointer. 
	// if (shared == (-1)){perror("\nError in fork");exit(1);}
	
	shared->count = 12;//initialization of shared memory variable.

	int process = fork();//making a new process.
	if ( process > 0)
	{
		printf("\nIn parent process\n");
			
		sembuf1.sem_num = 0;
		sembuf1.sem_op = -1;
		sembuf1.sem_flg = 0;
		int ret = semop(sem_id,&sembuf1,1);//setting the semaphore value.
		if (ret < 0){perror("\nError in assigning value to semaphore1");exit(0);}
			while(i < 200055) // critical section
			{
				shared->count--; // decreasing the count var.
				i++;
			}//while ends
			printf("\nFinal output: %d\n", shared->count);
		sembuf1.sem_num = 0;
		sembuf1.sem_op = +1;
		sembuf1.sem_flg = 0;
		ret = semop(sem_id,&sembuf1,1);//setting the semaphore value.
		if (ret < 0){perror("\nError in assigning value to semaphore2");exit(0);}

			wait(NULL);
	}//Parent ends
	if (process < 0){perror("\nError in fork");exit(2);}

	//in child process
	if ( process == 0)
	{ 
		printf("\nIn child process\n");
		
		sembuf1.sem_num = 0;
		sembuf1.sem_op = -1;
		sembuf1.sem_flg = 0;
		int ret = semop(sem_id,&sembuf1,1);//setting the semaphore value.
		if (ret < 0){perror("\nError in assigning value to semaphore3");exit(0);}

		while(j < 200055)
		{
			shared->count++;// increasing the count var
			j++;
		}//while ends
		
		printf("\nFinal output: %d\n", shared->count);
		sembuf1.sem_num = 0;
		sembuf1.sem_op = +1;
		sembuf1.sem_flg = 0;
		ret = semop(sem_id,&sembuf1,1);//setting the semaphore value.
		if (ret < 0){perror("\nError in assigning value to semaphore4");exit(0);}
	}//if ends(child ends)

	//in parent process

	return 0;
}

