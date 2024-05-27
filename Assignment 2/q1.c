/*Program for bidirectional pipe*/
/*Create a program, have 2 child created from the parent
  process and establish pipe ipc between 2 childs.*/
#include <Program_shared_IPC.h>
#include <string.h>
int main(void)
{
	char *prasad = "Hello world\n";
	char lalit[20];//buffer for first pipe.
	char lalit2[30];//buffer for second pipe.
	int pipe_f[2]; //pipe descriptor 1
	int pipe_f2[2];//pipe descriptor 2
	int pip = pipe(pipe_f);// making pipe.
	int pipe2 = pipe(pipe_f2);//made pipe 2
	if (pip < 0){perror("\nError in making pipe");exit(0);}

	int process = fork();//for making new child.
	if (process < 0){perror("\nError in fork");exit(0);}
	
	//in parent process
	else if (process > 0)
	{
		printf("\nIn parent: PID: %d, PPID: %d", getpid(),getppid());
		
		//making second child
		int child2 = fork();
		if (child2 < 0){perror("\nError in fork");exit(1);}
		else if (child2 > 0)
		{
			printf("\nIn parent PID: %d, PPID %d", getpid(),getppid());
		}//parent ends.
		else if(child2 == 0)
		{
			printf("\nChild 2 PID: %d, PPID: %d", getpid(),getppid());
			close(pipe_f[1]);//to close the writing end of pipe.
			read(pipe_f[0],lalit,20);//to read 20 char from buffer.
			printf("\nlalit: %s", lalit);
			close(pipe_f[0]);//to close the 
		}//child 2 ends.
		write(pipe_f2[1],"In parent afte child 2\n", sizeof("In parent afte child 2\n"));

	}//parent ends

	//in child
	else if (process == 0)
	{
		close(pipe_f[0]); // to close the read end
		write(pipe_f[1],prasad,strlen(prasad));//sending the string in the prasad array.		
		close(pipe_f[1]);

		read(pipe_f2[0],lalit2,30);
		printf("\nlalit2: %s", lalit2);
	}//child ends

	return 0;
}