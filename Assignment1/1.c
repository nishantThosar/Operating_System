/*File for fork operations in a program.*/
/*Link to output screenshots: 
	1} Fork Output in top command: https://drive.google.com/file/d/1cYH6Ojf4yAn2ayLGKvY-sJC9sXf8TDhW/view?usp=drive_link
 	2} After renice positive value: https://drive.google.com/file/d/1tEPjU1HA4jYewnpEdrRsnLXk-FYfLyY-/view?usp=drive_link
  	3} After renice negative value: https://drive.google.com/file/d/1tuXOTgIhOGgz2EAyv4PHZsXnHH1rgQqX/view?usp=sharing
   	4} ps -u command: https://drive.google.com/file/d/1aeBwFCJjNno9ghTfhlWceLGGTy1ejEsf/view?usp=sharing
    	5} ps -eh command: https://drive.google.com/file/d/1Xt14adnwM1KVNtnJfKODgTR2fB2NEAVR/view?usp=sharing
*/
/*
	Author: Nishant Thosar
 	Date: 19 May 2024 Sunday
  	Place: Pune
*/


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
