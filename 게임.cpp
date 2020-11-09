#pragma comment (lib,"ws2_32.lib")
#include <stdio.h>
#include <string.h>
#include <WinSock2.h>
#include <stdlib.h>
#include <process.h>
#include <Windows.h>

unsigned int WINAPI ThreadFunction(void*arg);

void ErrorHandling(char *message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}

int start();
int how();
int make();
int enter();

bool q;

	char port[] = "1324";
struct clients{
	SOCKET hClntSock;
	SOCKADDR_IN clntAddr;
	int szClntAddr;
	char name[10];
	char gm_chic_a[10];
	};// 여러개의 클라이언트를위한 구조체
	struct clients cl[3];//구조체 배열 4개

void main()
{
	char select = 0;
	printf("==============================================\n");
	printf("\n");//여기다 게임 이름
	printf("							     Made By DB HS\n");
	printf("==============================================\n");
	for(;;)
	{
	printf("1.시작\n");
	printf("2.게임방법\n");
	printf("3.종료\n");
	select = getchar();

	switch(select)
	{
	case '1':
		start();
		break;
	case '2':
		how();
		break;
	case '3':
		return;
	default:
		printf("누루라는거 누르자.\n");
		Sleep(500);
	}
	}
	return;
}
int start()
{
	char select = 0;

	for(;;)
	{
	printf("1.방만들기\n");
	printf("2.참여하기\n");
	fflush(stdin);
	select = getchar();
	
	switch(select)
	{
	case '1':
		make();
		break;
	case '2':
		enter();
		break;
	default:
		printf("누르라는거누르자\n");
		Sleep(500);
	}
	}
	return 0;
}
int make()
{
	int i;
	int j;
	int gm=0;
	int client_num = 0; // 클라이언트 받을때 순차적으로 받기위해
	int strLen;	
	char message[256] ={0,};
	int L=0;
	int VALUE =0;
	WSADATA wsaData;
	SOCKET hServSock;
	SOCKADDR_IN servAddr;
	HANDLE hThread= NULL;
	DWORD dwThreadID= NULL;
	DWORD dw = 0;
	STARTUPINFO si;                   
	PROCESS_INFORMATION pi;    
	ZeroMemory(&si, sizeof(si));   
	si.cb = sizeof(si);                 
	ZeroMemory(&pi, sizeof(pi));

	if(WSAStartup(MAKEWORD(2,2),&wsaData) !=0)
		ErrorHandling("WSAStartup() error!");

	hServSock = socket(PF_INET,SOCK_STREAM,0);
	if(hServSock==INVALID_SOCKET)
		ErrorHandling("socket() error!");

	memset(&servAddr,0,sizeof(servAddr));
	servAddr.sin_family=AF_INET;
	servAddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servAddr.sin_port=htons(atoi(port));

	if(bind(hServSock,(SOCKADDR*)&servAddr,sizeof(servAddr))==SOCKET_ERROR)
		ErrorHandling("bind() error!");

	CreateProcess(TEXT("5명채팅.exe"),NULL,NULL,NULL,CREATE_NEW_CONSOLE,NULL,NULL,NULL,&si,&pi);

	for(i=0;i<3;i++)
	{
	if(listen(hServSock,5)==SOCKET_ERROR)
		ErrorHandling("listen() error!");
	cl[i].szClntAddr=sizeof(cl[i].clntAddr);
	cl[i].hClntSock = accept(hServSock,(SOCKADDR*)&cl[i].clntAddr,&cl[i].szClntAddr);
	if(cl[i].hClntSock==INVALID_SOCKET)
		ErrorHandling("accept() error!");
	printf("player %d 연결\n",i);
	}

	hThread = (HANDLE)_beginthreadex(NULL,0,ThreadFunction,NULL,0,(unsigned*)&dwThreadID);

	if(!hThread)
	{
		printf("_beginthread error");
		return FALSE;
	}

	while(!q)
	{
		if(L ==0)
		{
			strLen=recv(cl[0].hClntSock,cl[0].name,sizeof(cl[0].name),0);
			strLen=recv(cl[0].hClntSock,cl[1].gm_chic_a,sizeof(cl[1].gm_chic_a),0);
			if(strLen == SOCKET_ERROR)
			{
			printf("socket error[recv]\n");
			q = true;
			}
			L++;
			continue;
		}
		strLen=recv(cl[0].hClntSock,message,sizeof(message),0);
		if(strLen == SOCKET_ERROR)
		{
			printf("socket error[recv]\n");
			q = true;
		}
		printf("%s : %s\n",cl[0].name,message);
		for(i=0;i<strlen(message);i++)
			if(message[i]==cl[0].gm_chic_a[0])
				for(j=0;j<strlen(cl[0].gm_chic_a);j++)
					if(message[i+j]==cl[0].gm_chic_a[j])
						VALUE++;
		if(VALUE==strlen(cl[0].gm_chic_a))
		{
			printf("금칙어를 말하셨습니다.\n");
			gm = 1;
		}
		VALUE=0;
		strLen=send(cl[2].hClntSock,cl[0].name,sizeof(cl[0].name),0);
		strLen=send(cl[2].hClntSock,message,sizeof(message),0);
		if(strLen == SOCKET_ERROR)
		{
			printf("socket error [send]");
			q = true;
		}
		if(gm == 1)
		{
			strLen=send(cl[2].hClntSock,"금칙어를 말하셨습니다.\n",sizeof("금칙어를 말하셨습니다.\n"),0);
			if(strLen == SOCKET_ERROR)
			{
			printf("socket error [send]");
			q = true;
			}
			gm = 0;
		}
	}

	q = true;
	dw = WaitForSingleObject(hThread,INFINITE);
	if(dw == WAIT_FAILED)
	{
		printf("WaitForSingleObject Error\n");
        return FALSE;
	}

	for(i=0;i<3;i++)
	{
	closesocket(cl[i].hClntSock);
	}
	WSACleanup();
	return 0;
}
unsigned int WINAPI ThreadFunction(void*arg)
{
	int strLen;
	char message2[256];
	int k = 0;
	int i,j;
	int gm2=0;
	int VALUE2=0;
	while(!q)
	{
		if( k == 0)
		{
			strLen=recv(cl[1].hClntSock,cl[1].name,sizeof(cl[1].name),0);
			strLen=recv(cl[1].hClntSock,cl[0].gm_chic_a,sizeof(cl[0].gm_chic_a),0);
			if(strLen == SOCKET_ERROR)
			{
			printf("socket error[recv]\n");
			q = true;
			}
			k++;
			continue;
		}

		strLen=recv(cl[1].hClntSock,message2,sizeof(message2),0);
		if(strLen == SOCKET_ERROR)
		{
			printf("socket error[recv]\n");
			q = true;
		}
		printf("%s : %s\n",cl[1].name,message2);
		for(i=0;i<strlen(message2);i++)
			if(message2[i]== cl[1].gm_chic_a[0])
				for(j=0;j<strlen(cl[1].gm_chic_a);j++)
					if(message2[i+j]==cl[1].gm_chic_a[j])
						VALUE2++;
		if(VALUE2==strlen(cl[1].gm_chic_a))
		{
			printf("금칙어를 말하셨습니다.\n");
			gm2 =1;
		}		
		VALUE2=0;

		strLen=send(cl[2].hClntSock,cl[1].name,sizeof(cl[1].name),0);
		strLen=send(cl[2].hClntSock,message2,sizeof(message2),0);
		if(strLen == SOCKET_ERROR)
		{
			printf("socket error [send]");
			q = true;
		}
		if(gm2 == 1)
		{
			strLen=send(cl[2].hClntSock,"금칙어를 말하셨습니다.\n",sizeof("금칙어를 말하셨습니다.\n"),0);
			if(strLen == SOCKET_ERROR)
			{
			printf("socket error [send]");
			q = true;
			}
			gm2 = 0;
		}
	}

	return 0;
}
int how()
{
	return 0;
}
int enter()
{
	int argc=3;
	char *argv[3] = {"client","5.109.242.199","1324"};
	WSADATA wsaData;
	char message[256];
	int strLen;
	SOCKET hSocket;
	char ip[] = "5.109.242.199";
    char name[10];

	SOCKADDR_IN servAddr;

	fflush(stdin);

	scanf("%s",ip);

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

      while(!q)
        {
			strLen = recv(hSocket,name,sizeof(name),0);
               strLen = recv(hSocket,message,sizeof(message),0);
               if(strLen == SOCKET_ERROR )
               {
                       printf("소켓에러! [recv]\n");
                       q = true;
               }
               printf("%s : %s \n",name,message);
        }
	  q = true;
 
 
    printf("main 함수종료!!\n");
	closesocket(hSocket);
	WSACleanup();
	return 0;
}