/*Program of shared memory IPC with semaphore*/
/*In this program we are creating two shared memories 
1) for sharing actual memory (ie: structure)
2) for sharing the semaphore.
*/

#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include <sys/sem.h> //in this sembuf structure is declared.
#include<sys/shm.h>

key_t  key  = ftok("shared_memory_semaphore", 11);

//shared area structure.
typedef struct shared_area
{
	long count;
}share;//struct ends

share *sh_ptr = NULL; // shared area structure pointer


union semun
{
	int val; //to hold the semaphore value
	
	// unsigned short *arr;
	int *ptr; // to make the size of union 8 bytes
};//union ends

int main()
{
	int ret;
	int id; //var to store the id of the shared memory.
	int sem_id;//var to get shared semaphore id.
	int wait_stat; // for wait state.
	int status;
	int ret_1;

	/* This struct is declared in the header file names as sys/sem.h
	Taking a variable of it named as sembuf1 (struct variable)*/
	struct sembuf sembuf1; 

	union semun u1;

	unsigned long int i = 0;
	unsigned long int j = 0;

	id = shmget(key, sizeof(share), IPC_CREAT | 0600);//CREATING A SHARED MEMORY FOR STRUCTURE.
	
	//if shmget is failed then exit.
	if (id < 0){perror("\nError in shmget");exit(1);}//if ends

	sh_ptr = shmat(id,0,0); // Attaching the structure pointer to the shared memory.
	
	//if attaching structure to the shared memory is failed then exit the program.
	if (sh_ptr == (share*) -1){perror("\nError in shmat");exit(1);}//if ends

	/*--------------------------------------Creating a SEMAPHORE-------------------------------*/
	//Here we are creating a shared memory for semaphore so that we can share semaphore between two processes.

	sem_id = semget(key,1,IPC_CREAT |0600);//Creating the semaphore shared memory with size only 1.
	if(sem_id < 0){perror("\nError in creating memory for semaphore");exit(2);}

	u1.val = 1; // this is the initial value of semaphore is initialized.

	/* here we are setting the 0 because only one semaphore 
	and setting the value to the value in the u1, which is equal to 1 in this case.
	*/
	ret_1 = semctl(sem_id,0,SETVAL,u1);
	if (ret_1 < 0){perror("\nError in setting value in semaphore"); exit(3);}

	printf("\nCurrent val of semaphore: %d", semctl(sem_id,0,GETVAL)); // to get the current value of semaphore.
	
	/*-------------------------------------SEMAPHORE intitilization ends------------------------*/
	
	printf("\nPointer address of struct member: %p", &sh_ptr->count);
	sh_ptr->count = 1;//initilization of structure member

	while(i < 0)
	{
		ret = fork(); // making a child process for parallel exec.

		if ( ret < 0){perror("\nError in fork");exit(5);}
/*----------------------------------------------------PARENT PROCESS-------------------------------------------------------*/
		if(ret > 0)
		{
			printf("\nIn parent process PID: %d, PPID: %d", getpid(),getppid());

			/*------------INITILIZATION OF SEMAPHORE STRUCT MEMBERS------------*/
			sembuf1.sem_num = 0; // semaphore index value (Here 0 because of only 1 semaphore is implimented).
			sembuf1.sem_op = -1; // This is for updating the semaphore value.
			sembuf1.sem_flag = 0;// don't know about this.
			/*-----------------------------END----------------------------------*/
			//DECRIMENTING THE SEMAPHORE VALUE BEFORE ENTERING THE CRITICAL SECTION.
			if ((semop(sem_id, &sembuf1,1)) < 0){perror("\nError! in setting semaphore value");exit(6);}

			while(j < 12)
			{
				sh_ptr->count ++;

			}//while ends
			/*------------INITILIZATION OF SEMAPHORE STRUCT MEMBERS------------*/
			sembuf1.sem_num = 0; // semaphore index value (Here 0 because of only 1 semaphore is implimented).
			sembuf1.sem_op = +1; // This is for updating the semaphore value.
			sembuf1.sem_flag = 0;// don't know about this.
			/*-----------------------------END----------------------------------*/

			//INCRIMENTING THE SEMAPHORE VALUE
			if ((semop(sem_id,&sembuf1,1))<0){perror("\nError! in setting semaphore value");exit(6);}

			printf("\nEnd in parent");
			
		}//if ends (parent ends)

		i++;

		wait_stat = waitpid(-1,&status,0);
		if (wait_stat > 0)
		{
			if((WIFEXITED(status)) == 0){//normal & successful}
			else{//normal but not sucess}
		}
		else{//abnormal termination}

		if(wait_stat < 0)
		{
			printf("\nFinal value: %d", sh_ptr->count);

		}//if ends
		shmctl(id,IPC_RMID,0);
	}//while ends
/*-------------------------------------CHILD PROCESS--------------------------------------------------------------------*/
	if (ret == 0)
	{
		printf("\nIn child PID: %d, PPID: %d", getpid(),getppid());
		/*------------INITILIZATION OF SEMAPHORE STRUCT MEMBERS------------*/
			sembuf1.sem_num = 0; // semaphore index value (Here 0 because of only 1 semaphore is implimented).
			sembuf1.sem_op = -1; // This is for updating the semaphore value.
			sembuf1.sem_flag = 0;// don't know about this.
		/*-----------------------------END----------------------------------*/

		//DECRIMENTING THE SEMAPHORE VALUE.
		if ((semop(sem_id,&sembuf1,1))<0){perror("\nError! in setting semaphore value");exit(6);}		
		
		while(j < 5)
		{
			sh_ptr->count--;
		}
		
		/*------------INITILIZATION OF SEMAPHORE STRUCT MEMBERS------------*/
			sembuf1.sem_num = 0; // semaphore index value (Here 0 because of only 1 semaphore is implimented).
			sembuf1.sem_op = +1; // This is for updating the semaphore value.
			sembuf1.sem_flag = 0;// don't know about this.
		/*-----------------------------END----------------------------------*/

		//INCRIMENTING THE SEMAPHORE VALUE.
		if ((semop(sem_id,&sembuf1,1))<0){perror("\nError! in setting semaphore value");exit(6);}		


	}//if ends (child ends).



	return 0;
}//main ends