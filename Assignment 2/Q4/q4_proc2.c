/*Write a program to implement the message-queue IPC.*/
/*This program must be run with q4_proc1
as this program is the second process of q4_proc1*/

#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>


//struct of shared memory
typedef struct share_
{
	int a;
}share;

share *sh_ptr = NULL;//shared memory pointer.

int main(void)
{
	printf("\nFrom program 2"); // just to conform.
	key_t key = ftok("q4",11); // to make a key.
	
	int shared_mem_id;//to store the return ID of shared memory.
	int id = shmget(key,sizeof(share),IPC_CREAT | 0600);//creating a shared memory.
	if(id < 0){perror("error in making memory");exit(0);}
	sh_ptr = shmat(id,0,0);//to link the shared memory with struct pointer.
	if(sh_ptr ==(share*) -1){perror("error in linking shared memory");exit(1);}

	//Now accessing and reading from shared memory
	printf("\nShared memory variable value: %d\n\n",sh_ptr->a);
	return 0;
}
