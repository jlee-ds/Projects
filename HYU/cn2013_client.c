/*
 * cn2013_client.c
 * 2011004095 이종원
 */

#include <stdio.h>			//for standard function in C.
#include <stdlib.h>			//for exit().		
#include <string.h>			//for memset().
#include <unistd.h>			//for read(), write(), close().
#include <arpa/inet.h>		//for htons().
#include <sys/types.h>		//for typedef data for socketprogramming.
#include <sys/socket.h>		//for socket(), bind(), inet_addr(), connect().
#include <pthread.h>		//for use thread (create, join).
#define MAX_NAME_LENGTH 20 	//the maximum of name length is 20.
#define MAX_MSG_LENGTH 1000 //the maximum of msg length is 1000. include '\0'

void *send_msg(void *serv_sock);		//thread use this func for send msg to server.
void *receive_msg(void *serv_sock);		//thread use this func for read msg from server.
void error_handling(char *message);		//func for error msg print.

char clnt_name[MAX_NAME_LENGTH];		//client's name string.
char clnt_msg[MAX_MSG_LENGTH];			//client's message string.

int main(int argc, char **argv)		//main function.
{//main function body start.
	int serv_sock;					//server socket variable.
	struct sockaddr_in serv_addr;	//server socket info variable.
	pthread_t send_t, receive_t;	//thread for send msg and for receive msg.
	char entrancemsg[50];			//for entrance message.
	
	if(argc!=4)													//if input form is not correct,	
	{//if body start.
		printf("Usage : %s <IP> <port> <name>\n", argv[0]);		//print usage message.
		exit(1);												//and then, exit program.
	}//if body end.	

	sprintf(clnt_name,"[%s]",argv[3]);									//clnt_name is [name]
	sprintf(entrancemsg,">> %s entered chatting room.\n", clnt_name);	//for entrance message.

	serv_sock=socket(PF_INET, SOCK_STREAM, 0);  	//socket create. IPv4. TCP/IP.
	if(serv_sock == -1)								//if it does not create,
		error_handling("socket() error");			//call error_handling function.
	
	memset(&serv_addr, 0, sizeof(serv_addr));		//server socket info initialization.
	serv_addr.sin_family=AF_INET;					//IPv4
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);	//IP address
	serv_addr.sin_port=htons(atoi(argv[2]));		//Port number.
		
	if(connect(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)	//connect to server's socket.
		error_handling("connect() error!");										//if it does not connect, error msg print.
	else 																//else
		write(serv_sock, entrancemsg, strlen(entrancemsg));				//entrance message print.

	pthread_create(&send_t, NULL, send_msg, (void*)&serv_sock);			//and then, create thread that send msg to server.
	pthread_create(&receive_t, NULL, receive_msg, (void*)&serv_sock);	//create thread that receive msg from server.
	pthread_join(send_t, NULL);											//until end of thread, wait.
	pthread_join(receive_t, NULL);										//until end of thread, wait.
	
	close(serv_sock); 													//when threads are finished, disconnect to server socket.
	
	return 0;															//return 0;
}//main function body end.

void *send_msg(void *serv_sock)									//send_msg function.
{//send_msg function body start.
	int server_socket = *((int*)serv_sock);						//set server_socket variable using parameter.
	char msgtosend[MAX_MSG_LENGTH+MAX_NAME_LENGTH];				//message to send to server that concatenate name and msg.
	char leftmsg[30];											//for client's left message.

	sprintf(leftmsg, ">> %s left.\n", clnt_name);				//make left message.

	while(1)													//infinit loop.
	{//while body start.
		fgets(clnt_msg, MAX_MSG_LENGTH, stdin);					//터미널에서로부터 받은 문자열을 clnt_msg에 저장.
		if(!strcmp(clnt_msg,"q\n")||!strcmp(clnt_msg,"Q\n"))	//q\n이거나 Q\n가 들어왔는 지 확인.
		{//if body start.
			write(server_socket, leftmsg, strlen(leftmsg));		//만약 그러하다면 퇴장메세지를 서버에 전송.
			close(server_socket);								//그리고 서버와의 연결을 종료.
			exit(0);											//프로그램 강제종료.
		}//if body end.
		sprintf(msgtosend, "%s %s", clnt_name, clnt_msg);		//Q\n or q\n가 아니라면 받은 메세지를 이름과 함친다.
		write(server_socket, msgtosend, strlen(msgtosend));		//합친 문자열을 서버에 전송.
	}//while body end.
	return NULL;												//NULL 리턴.
}//send_msg function body end.

void *receive_msg(void *serv_sock)									//receive_msg function.
{//receive_msg function body start.
	int server_socket = *((int*)serv_sock);							//입력받은 파라미터를 이용하여 server_socket을 설정한다.
	char msgtoread[MAX_MSG_LENGTH+MAX_NAME_LENGTH];					//서버로 부터 읽어드릴 문자열을 저장하기 위한 배열.
	int msglen;														//그러한 문자열의 길이를 저장할 변수.

	while(1)														//무한루프
	{//while body start.
		msglen = read(server_socket, msgtoread, sizeof(msgtoread));	//메세지를 읽어서 msgtoread에 저장. 또 그 길이를 msglen에 저장.
		if(msglen==-1)												//read func error.
			return (void*)-1;										//function exit.
		msgtoread[msglen] = '\0';									//msgtoread배열의 뒷부분에 남아있는 그 전에 받아드린 문자열을 없애주기 위해서 길이의 맨 마지막에 \0 캐릭터를 넣어준다.
		fputs(msgtoread, stdout);									//그리고 나서 client 화면에 출력.	
	}//while body end.
	return NULL;													//NULL 리턴.
}//receive_msg function body end.

void error_handling(char *message)		//error_handling function.
{//error_handling function body start.
	fputs(message, stderr);				//입력받은 파라미터를 출력.
	fputc('\n', stderr);				//줄바꾸기.
	exit(1);							//프로그램 강제종료.
}//error_handling function body end.
