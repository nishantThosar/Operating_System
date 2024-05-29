/*Write a program to implement the message-queue IPC.*/
/*In this program we are taking key from the user whie executing the program*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>

//structure for message queue
typedef struct mesg
{
	long type;
	char text[100];
}msg;



int main(void)
{
	key_t key = ftok("proc2",12);
	// if (argc <1){perror("\n\n<Insert key while running>");exit(0);}//if ends
	printf("\nIn prog 1");
	// printf("\n%s",argv[1]);
	msg message;//struct var.
	// char buff[100];//temp buffer
	//checking if user have given the arguments or not.

	// int key = atoi(argv[1]); // accepting key
	int msg_id = msgget(key, 0666| IPC_CREAT);//to create msg id.	
	if (msg_id < 0){perror("\nError in creating Message Queue");exit(1);}

	message.type = 1; // type of message.
	
	//to take input from user.
/*	printf("\nEnter the string: ");
	scanf("%[^\n]s",message.text);
	printf("\nString received: %s",message.text);*/

	strncpy(message.text,"Hello",strlen("Hello")+1); // to cpoy the input from buffer to the struct member

	int m_sent = msgsnd(msg_id,&message,sizeof(msg),0);// to sent the message in the queue.
	
	if (m_sent < 0){perror("\nError in sendin message");exit(3);}	
	return 0;
}//main ends
