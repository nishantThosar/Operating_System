/*1>> Using the shared memory IPC try to see race condition. Have one
    shared structure. Modify that in two different process.*/
/*In this program the race condition is occuring as */
#include<sys/types.h>
#include<unistd.h>
#include<wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>

typedef struct shmem
{
	int count;
}mem;

mem *shared = NULL;//shared memory pointer.

int main(int argc, char const *argv[])
{
	int i=0;
	int j = 0;
	key_t key= ftok("q3a1",14);

	int id = shmget(key,sizeof(mem),IPC_CREAT | 0600); // to create the shared memory  	
	if (id < 0){perror("\nError in shmget");exit(0);}

	shared = shmat(id,0,0); //to link the shared memory with the structure pointer. 
	// if (shared == (-1)){perror("\nError in fork");exit(1);}
	
	shared->count = 12;//initialization of shared memory variable.

	int process = fork();//making a new process.
	if ( process > 0)
	{
		printf("\nIn parent process\n");
				
		while(i < 2055)
		{
			shared->count--; // decreasing the count var.
			i++;
		}//while ends
		printf("\nFinal output: %d\n", shared->count);
		wait(NULL);
	}//Parent ends
	if (process < 0){perror("\nError in fork");exit(2);}

	//in child process
	if ( process == 0)
	{ 
		printf("\nIn child process\n");
		
		while(j < 2055)
		{
			shared->count++;// increasing the count var
			j++;
		}//while ends
		printf("\nFinal output: %d\n", shared->count);
	}//if ends(child ends)

	//in parent process

	return 0;
}
