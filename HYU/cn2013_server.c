/*
 * cn2013_server.c
 * 2011004095 이종원 
 */

#include <stdio.h>			//for standard function in C.
#include <stdlib.h>			//for exit().		
#include <string.h>			//for memset().
#include <unistd.h>			//for read(), write(), close().
#include <arpa/inet.h>		//for htons(), htonl().
#include <sys/types.h>		//for typedef data for socketprogramming.
#include <sys/socket.h>		//for socket(), bind(), connect(), accept().
#include <pthread.h>		//for thread. (create, join, mutex)
#define MAX_CLIENT 100 		//the maximum number of client is 100.
#define MAX_MSG_LENGTH 1000	//the maximum length of msg is 1000 characters. include '\0'

void *manage_client(void *clnt_sock);	//declare manage_clinet function. threads do this.
void error_handling(char *message);		//declare error_handling function.

pthread_mutex_t mutex;			//for mutex at critical area.
int clnt_count = 0;				//current connected client number. 
int clnt_sockets[MAX_CLIENT];	//current connected clinets' sokect number array.

int main(int argc, char **argv)			//main function declaration.
{//main function's body start.
	int serv_sock;						//server's socket num variable.
	int clnt_sock;						//client's socket num variable.
	struct sockaddr_in serv_addr;		//server's socket info struct variable.
	struct sockaddr_in clnt_addr;		//client's socket info struct variable.
	int clnt_addr_size;					//client's socket info struct's size variable.
	pthread_t thread_id;				//thread variable for create thread that manage client.
	
	if(argc!=2)										//if input does not have port number.
	{//if statement's body start.	
		printf("Usage : %s <port>\n", argv[0]);		//print usage mssage to stdout.
		exit(1);									//and then, exit program.
	}//if statement's body end.
	
	pthread_mutex_init(&mutex, NULL);				//mutex initialization.
	serv_sock=socket(PF_INET, SOCK_STREAM, 0); 		//socket create. IPv4, TCP/IP.
	if(serv_sock == -1)								//if socket does not create,
		error_handling("socket() error");			//call error_handling function.
	
	memset(&serv_addr, 0, sizeof(serv_addr));		//server's socket info initialization.
	serv_addr.sin_family=AF_INET;					//use IPv4.
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);	//현재 사용중인 컴퓨터의 아이피주소로 아이피주소 설정.
	serv_addr.sin_port=htons(atoi(argv[1]));		//입력받은 포트번호으로 포트번호 설정.
	
	if( bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1 ) 		//생성된 소켓과 설정한 소켓정보를 연결.
		error_handling("bind() error"); 											//call error_handling function.
	
	if( listen(serv_sock, 5)==-1 )  				//소켓연결을 할 수 있는 상태로.
		error_handling("listen() error");			//call error_handling function.
	
	while(1)										//infinit loop.
	{//while statement's body start.
		clnt_addr_size = sizeof(clnt_addr);  											//클라이언트 소켓 정보의 크기 설정.
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);	//소켓연결을 대기하는 상태로.
		if(clnt_sock==-1)							//소켓대기에 실패하면,
			error_handling("accept() error"); 		//call error_handling function.

		pthread_mutex_lock(&mutex);					//use mutex_lock to protect critical area.
		clnt_sockets[clnt_count] = clnt_sock;		//연결된 클라이언트 소켓을 클라이언트 소켓배열에 저장.
		clnt_count++;								//현재 연결된 클라이언트 수를 1 증가.
		pthread_mutex_unlock(&mutex);				//use mutex_lock to protect critical area.

		pthread_create(&thread_id, NULL, manage_client, (void*)&clnt_sock);			//해당 클라이언트 소켓을 관리하는 스레드생성.
		pthread_detach(thread_id);													//해당 스레드가 끝나면 그냥 사라지도록 하는 함수.
		printf("New Connetion, Client IP is %s\n",inet_ntoa(clnt_addr.sin_addr));	//연결된 클라이언트의 아이피주소를 서버의 창에 띄움.
	}//while statement's body end.

	return 0;										//return 0;
}//main function's body end.

void *manage_client(void *clnt_sock)			//manage_client function.
{//manage_client function's body start.
	int client_socket = *((int*)clnt_sock);		//파라미터로 입력받은 클라이언트 소켓을 저장.
	int msg_len = 0;							//읽은 메세지의 길이를 저장할 변수. 0으로 초기화.
	int i;										//반복문을 위한 변수 i.
	char msg[MAX_MSG_LENGTH];					//메세지를 저장하기위한 캐릭터배열. 문자열.

	while((msg_len = read(client_socket, msg, sizeof(msg)))!=0)	//계속 클라이언트 소켓에서 메세지를 읽어드린다. 클라이언트 소켓이 종료될 떄까지.
	{//while statement's body start.
		pthread_mutex_lock(&mutex);									//전역변수를 사용하니 뮤텍스로 보호한다.
		for(i=0;i<clnt_count;i++)									//현재 연결된 모든 클라이언트에게
		{//if statement's body start.
			write(clnt_sockets[i], msg, msg_len);					//방금 읽은 메세지를 보낸다.
		}//if statement's body end.
		pthread_mutex_unlock(&mutex);								//뮤텍스 해제.
	}//while statement's body end.

	pthread_mutex_lock(&mutex);							//또 전역변수를 건드리므로 뮤텍스로 보호.
	for(i=0;i<clnt_count;i++)							//모든 클라이언트 중에서
	{//for statement's body start.
		if(client_socket == clnt_sockets[i])			//현재 연결된 클라이언트(종료된 클라이언트)와 같은 클라이언트를 찾아서
		{//if statement's body start.
			while(i<clnt_count-1)						//그 뒤의 클라이언트를 
			{//while statement's body start.
				clnt_sockets[i] = clnt_sockets[i+1];	//앞으로 옮김. (자연스레 종료된 클라이언트 사라짐)
				i++;									//하나씩.
			}//while statement's body end.
			break;										//다 옮기면 for statement를 break;
		}//if statement's body end.
	}//for statement's body end.
	clnt_count--;										//현재 클라이언트 수를 1 감소.
	pthread_mutex_unlock(&mutex);						//뮤텍스 해제.

	close(client_socket);				//해당 클라이언트와의 연결을 해제.
	return NULL;						//NULL을 리턴.
}//manage_client function's body end.

void error_handling(char *message)			//error_handling function.
{//error_handling function's body start.
	fputs(message, stderr);					//받은 파라미터를 그대로 출력.
	fputc('\n', stderr);					//엔터도 입력.
	exit(1);								//프로그램을 강제종료.
}//error_handling function's body end.
