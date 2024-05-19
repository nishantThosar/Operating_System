/*File for fork operations in a program.*/
/**/


#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	int child = fork();													// making a child process

	if (child == 0)														//if child is made then print the PPID & PID 
	{
		printf("\nChild PID: %d PPID: %d\n", getpid(), getppid());
		while(1)
		{

		}
	}//if ends
	else if (child > 0)													//parent ID printing
	{
		printf("\nParent PID: %d, PPID: %d\n", getpid(), getppid());
		while(1);
	}
	else if (child < 0)													//error handling if fork fail
	{
		perror("\nChild making");
	}

	return 0;
}