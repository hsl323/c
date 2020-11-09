#pragma comment (lib,"ws2_32.lib")
#include <stdio.h>
#include <string.h>
#include <WinSock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <process.h>

void ErrorHandling(char *message);

bool Quit;
SOCKET hSocket;

int main()
{

	system("mode con:lines=2");
	int argc=3;
	char *argv[3] = {"client","5.109.242.199","1324"};
	WSADATA wsaData;
	char message[256];
	int strLen;
	char ip[] = "5.109.242.199";
	char port[] = "1324";
	char name[10];
	int i=0;
	char gum[10];
	SOCKADDR_IN servAddr;
	
	fflush(stdin);
	printf("IP : ");
	scanf("%s",ip);
	system("cls");
	fflush(stdin);
	printf("이름 : ");
	gets(name);
	system("cls");
	fflush(stdin);
	fflush(stdin);
	printf("금칙어 : ");
	gets(gum);
	system("cls");

	if(argc !=3)
	{
		printf("usage : %s <ip> <port> \n",argv[0]);
		exit(1);
	}

	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
		ErrorHandling("WSAStartup() error!");

	hSocket=socket(PF_INET,SOCK_STREAM,0);
	if(hSocket == INVALID_SOCKET)
		ErrorHandling("hSocket() error!");

	memset(&servAddr,0,sizeof(servAddr));
	servAddr.sin_family=AF_INET;
	servAddr.sin_addr.s_addr=inet_addr(ip);
	servAddr.sin_port=htons(atoi(port));

	if(connect(hSocket,(SOCKADDR*)&servAddr,sizeof(servAddr))==SOCKET_ERROR)
		ErrorHandling("connect() error!");

      while(!Quit)
        {
			if(i == 0)
			{
				strLen = send(hSocket,name,sizeof(name),0);
				strLen = send(hSocket,gum,sizeof(gum),0);
				if(strLen == SOCKET_ERROR)   
               {
                       printf("소켓에러! [send]\n");
                       Quit = true;
               }
				i++;
			}
			fflush(stdin);
			printf(" : ");
            gets(message);
			system("cls");
             if(!strcmp(message,"exit"))
                       Quit = true;
 
               strLen = send(hSocket,message,sizeof(message),0);
               if(strLen == SOCKET_ERROR)   
               {
                       printf("소켓에러! [send]\n");
                       Quit = true;
               }
        }
	   Quit = true;

    printf("main 함수종료!!\n");
	closesocket(hSocket);
	WSACleanup();
	return 0;
}
void ErrorHandling(char *message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}
