/*Receiver progam for message queue*/
/*In this program we are reading the message from msg queue*/
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
	// printf("\nKEY: %s",argv[1]);
	// if (argc <1){perror("\n\n<Insert key while running>");exit(0);}//if ends
	printf("\nIn 2nd prog");
	//to check if the user has input the 2nd argument or not.
	
	msg message;//struct var.
	//int key = atoi(argv[1]); // accepting key
	int msg_id = msgget(key, 0666| IPC_CREAT);//to create msg id.	
	if (msg_id < 0){perror("\nError in creating Message Queue");exit(1);}
	
	int ret = msgrcv(msg_id,&message,sizeof(msg),1,0);
	if (ret < 0){perror("\nError in receiving message");exit(2);}
	printf("Rec message: %s\n",message.text);
	//strncpy(message.text,buff,strlen(buff)+1); // to cpoy the input from buffer to the struct member
	return 0;
}//main ends