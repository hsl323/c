#include <stdio.h>
#include <string.h>
#include <process.h>
#include <stdlib.h>
#include <conio.h>
#include <WinSock2.h>
#pragma comment (lib,"ws2_32.lib")

bool Quit;

SOCKET hClntSock;

#define RIGHT   77
#define LEFT    75
#define DOWN    80
#define UP      72

void start();
int multi_server();
int multi_client();
void how();
int wall(int i);
int move(int i);
void map();
void sw(int i); // �����϶� �÷��̾ �ٷ� ���� ������.
void end();
void ErrorHandling(char *message);
void gotoxy(int x, int y)//���� ���ϴ� ��ġ�� Ŀ�� �̵�
{
	COORD pos = {x-1, y-1};//Ŀ���� X��ǥ���� -1 �Ѱ�. Y��ǥ���� -1�� ������ �̵�
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);// WIN32API �Լ��Դϴ�. �̰� ���ʿ� �����
}

int player[2][2];
int j; // sw ���� 2�� �÷��̾�
int wal;
int k;
char walx;	
int s=10;
char waly;
int wal_x[50];
int wal_y[50];
int wal_x_h[50];
int wal_y_h[50];
int v=0;
int z;
int h=0;
int wal_c=0;
int wal_hc=0;
int m=0;
int ms=0;
char name[1][10];
int argc = 3;
char *argv[3] = {"client","0","9888"};

WSADATA wsadata;

SOCKADDR_IN sockaddr;	

WSADATA wsaData;

SOCKET hServSock;
SOCKADDR_IN servAddr;
SOCKADDR_IN clntAddr;
int szClntAddr;
int strLen;
char message[256];
char port[] = "9888";
char ip[] = "127.0.0.1";

int main()
{

	char select=0;

	printf(" ==============================================================================\n");
	printf("                                    Quoridor                                   \n");
	printf("                                                                 Made By DB,HS \n");
	printf(" ==============================================================================\n\n");
	while(1)
	{
		printf(" 1.����\n");
		printf(" 2.���ӹ��\n");
		printf(" 3.��Ƽ\n");
		printf(" 4.����\n");

		fflush(stdin);
		select = _getch();

		switch(select)
		{
		case '1':
			start();
			break;
		case '2':
			how();
			break;
		case '3':
			m = 1;
			printf("1.�游���\n");
			printf("2.�����ϱ�\n");
			select = _getch();
			for(;;)
			{
				switch(select)
				{
				case '1':
					multi_server();
					break;
				case '2':
					ms =2;
					multi_client();
					break;
				default :
					printf("\n������°� ��������\n\n");
				}
			}
			break;
		case '4':
			return 0;
		default:
			printf("\n������°� ��������\n\n");
		}
	}
	return 0;
}
void start()
{

	int i;
	int c=0;
	char select =0;
	if(m != 1)
	{
		system("cls");
		printf("\n�÷��̾� �̸��� �Է����ּ���.\n\n");
		printf("�÷��̾� 1 : ");
		scanf("%s",&name[0]);
		printf("\n�÷��̾� 2 : ");
		scanf("%s",&name[1]);
	}
	player[0][0]=6;
	player[0][1]=19;
	player[1][0]=70;
	player[1][1]=19;

	while(1)
	{
		for(i=0;i<=1;i++)
		{
			if(i==0)
				j=1;
			else
				j=0;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			map();
			if(i==1)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			else if(i==0)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);

			printf(" %s���� ��\n",name[i]);
			printf("1. �̵�\n");
			printf("2. ��\n");
			fflush(stdin);
			if(ms !=2)
			{
				if(m == 1 && i == 0)
				{
					select = _getch();
					for(i=0;i<256;i++)
					{
						message[i] = 0;
					}
					message[0] = select;
					strLen = send(hClntSock,message,sizeof(message),0); // ����������
					if(strLen == SOCKET_ERROR)   
					{
						printf("���Ͽ���! [send]\n");
						Quit = true;
					}
				}
				else if(m == 1 && i == 1)
				{
					strLen = recv(hClntSock,message,sizeof(message),0);
					if(strLen == SOCKET_ERROR )
					{
						printf("���Ͽ���! [recv]\n");
						Quit = true;
					}
					select = message[0];
				}
				else
					select = _getch();
			}
			else if(ms == 2)
			{
				if(i == 0)
				{
					strLen = recv(hClntSock,message,sizeof(message),0);
					if(strLen == SOCKET_ERROR )
					{
						printf("���Ͽ���! [recv]\n");
						Quit = true;
					}
					select = message[0];
				}
				else if(i == 1)
				{
					select = _getch();
					for(i=0;i<256;i++)
					{
						message[i] = 0;
					}
					message[0] = select;
					strLen = send(hClntSock,message,sizeof(message),0); // ����������
					if(strLen == SOCKET_ERROR)   
					{
						printf("���Ͽ���! [send]\n");
						Quit = true;
					}
				}
				else 
					select = _getch();
			}

			s= 10;
P:
			while(s!=0)
			{
				fflush(stdin);
				s=0;
				switch(select)
				{
				case '2':
					s = wall(i);
					break;
				case '1':
					s = move(i);
					break;
				default:
					printf("1���̳� 2����������\n");
				}
				if(s == 5)
				{
					map();
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
					printf("%s ���� �¸��ϼ˽��ϴ�!\n",name[1]);
					end();
					return;
				}
				if(s==6)
				{
					map();
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
					printf("%s ���� �¸��ϼ˽��ϴ�!\n",name[0]);
					end();
					return;
				}
			}
		}
	}
	return;
}
void how()
{
	system("cls");
	printf("�������� ���� �����մϴ�.\n�ڽ��� ���� �Ǹ� 2������ �ϳ��� �����ϴµ� �̵��� �� �Դϴ�.\n�̵��� �ڽ��� ���� �����¿��� ��ĭ ������ �� ������\n");
	printf("���� ĭ�� ���̿� �������� ���ϴ� ���� �״� ���Դϴ�.\n���鳢�� ���ֺ��� �پ���� �� ������ �¸� ������ �ݴ��ʿ� ��� ���Դϴ�.\n\n");
	return ;
}int wall(int i)
{
	char select =0;
Z:
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	map();
	printf("���� ������ ������ �ּ���.\n");
	printf("1.����\n");
	printf("2.����\n");
	if(m == 1 && i == 0)
	{
		select = _getch();
		for(i=0;i<256;i++)
		{
			message[i] = 0;
		}
		message[0] = select;
		strLen = send(hClntSock,message,sizeof(message),0); // ����������
		if(strLen == SOCKET_ERROR)   
		{
			printf("���Ͽ���! [send]\n");
			Quit = true;
		}
	}
	else if(m == 1 && i == 1)
	{
		strLen = recv(hClntSock,message,sizeof(message),0);
		if(strLen == SOCKET_ERROR )
		{
			printf("���Ͽ���! [recv]\n");
			Quit = true;
		}
		select = message[0];
	}
	else
		select = _getch();

	if(select == '1')
		wal =1;
	else if(select =='2')
		wal =2;
	else
	{
		printf("������°� ����.\n");
		goto Z;
	}

L:

	printf("���� ������ ��ǥ�� �Է����ּ���.(�ϳ��� ���ĺ����� �빮�ڸ�)\n");
	printf("���� �������� �����ϴ�\n");
	fflush(stdin);
	if(m == 1 && i == 0)
	{
		scanf("%s%s",&walx,&waly);
		for(i=0;i<256;i++)
		{
			message[i] = 0;
		}
		message[0] = walx;
		strLen = send(hClntSock,message,sizeof(message),0); // ����������
		if(strLen == SOCKET_ERROR)   
		{
			printf("���Ͽ���! [send]\n");
			Quit = true;
		}
		message[0] = waly;
		strLen = send(hClntSock,message,sizeof(message),0); // ����������
		if(strLen == SOCKET_ERROR)   
		{
			printf("���Ͽ���! [send]\n");
			Quit = true;
		}
	}
	else if(m == 1 && i == 1)
	{
		strLen = recv(hClntSock,message,sizeof(message),0);
		if(strLen == SOCKET_ERROR )
		{
			printf("���Ͽ���! [recv]\n");
			Quit = true;
		}
		walx = message[0];
		strLen = recv(hClntSock,message,sizeof(message),0);
		if(strLen == SOCKET_ERROR )
		{
			printf("���Ͽ���! [recv]\n");
			Quit = true;
		}
		waly = message[0];
	}
	else
		scanf("%s%s",&walx,&waly);

	if(waly < 1 || waly > 8)
		goto L;
	system("cls");
	map();
	if(wal_c == 2 || wal_hc ==2)
	{
		wal_c =0;
		wal_hc=0;
		goto L;
	}
	else
		return 0;
}
int move(int i)
{
	char input =0;
	int c;
	int q=0;
	printf("����Ű�� �����ּ��� �ʹ����� Ż���ϸ� �ȵ˴ϴ�\n");
in:
	if(ms != 2)
	{
		if(m == 1 && i == 0)
		{
			input = _getch();
			for(i=0;i<256;i++)
			{
				message[i] = 0;
			}
			message[0] = input;
			strLen = send(hClntSock,message,sizeof(message),0); // ����������
			if(strLen == SOCKET_ERROR)   
			{
				printf("���Ͽ���! [send]\n");
				Quit = true;
			}
		}
		else if(m == 1 && i == 1)
		{
			strLen = recv(hClntSock,message,sizeof(message),0);
			if(strLen == SOCKET_ERROR )
			{
				printf("���Ͽ���! [recv]\n");
				Quit = true;
			}
			input = message[0];
		}
		else
			input = _getch();
	}
	else if(ms == 2)
	{
		if( i == 0)
		{
			strLen = recv(hClntSock,message,sizeof(message),0);
			if(strLen == SOCKET_ERROR )
			{
				printf("���Ͽ���! [recv]\n");
				Quit = true;
			}
			input = message[0];
		}
		else if( i == 1)
		{
			input = _getch();
			for(i=0;i<256;i++)
			{
				message[i] = 0;
			}
			message[0] = input;
			strLen = send(hClntSock,message,sizeof(message),0); // ����������
			if(strLen == SOCKET_ERROR)   
			{
				printf("���Ͽ���! [send]\n");
				Quit = true;
			}
		}
	}

	switch(input)
	{
	case LEFT:
		z = player[i][0]-8;
		for(c=0;c<=h-1;c++)
		{
			if(player[i][0] > wal_x_h[c] && z < wal_x_h[c] && player[i][1] < (wal_y_h[c]+8) && player[i][1] > wal_y_h[c])
				return 1;
		}
		if(z == player[j][0] && player[i][1] == player[j][1])
		{
			q = 1;
			printf("��������� ���ðڽ��ϱ�?\n");
			sw(i);
			for(c=0;c<=v+h;c++)
			{
				if(player[i][0] < wal_x_h[c] && z > wal_x_h[c] && player[i][1] < (wal_y_h[c]+8) && player[i][1] > wal_y_h[c])
					return 1;
				if(player[i][0] > wal_x_h[c] && z < wal_x_h[c] && player[i][1] < (wal_y_h[c]+8) && player[i][1] > wal_y_h[c])
					return 1;
				if(player[i][1] < wal_y[c] && k > wal_y[c] && player[j][0] < (wal_x[c]+12) && player[j][0] > wal_x[c])
					return 1;
				if(player[i][1] > wal_y[c] && k < wal_y[c] && player[j][0] < (wal_x[c]+12) && player[j][0] > wal_x[c])
					return 1;
			}
		}
		if(z <= 3)
			return 1; 

		player[i][0] = z;
		if(q == 1)
			player[i][1] = k;
		if(player[1][0] == 6)
			return 5;
		break;

	case RIGHT:
		z = player[i][0]+8;
		for(c=0;c<=h-1;c++)
		{
			if(player[i][0] < wal_x_h[c] && z > wal_x_h[c] && player[i][1] < (wal_y_h[c]+8) && player[i][1] > wal_y_h[c])
				return 1;
		}
		if(z == player[j][0] && player[i][1] == player[j][1])
		{
			q = 1;
			printf("��������� ���ðڽ��ϱ�?\n");
			sw(i);
			for(c=0;c<=v+h;c++)
			{
				if(player[i][0] < wal_x_h[c] && z > wal_x_h[c] && player[i][1] < (wal_y_h[c]+8) && player[i][1] > wal_y_h[c])
					return 1;
				if(player[i][0] > wal_x_h[c] && z < wal_x_h[c] && player[i][1] < (wal_y_h[c]+8) && player[i][1] > wal_y_h[c])
					return 1;
				if(player[i][1] < wal_y[c] && k > wal_y[c] && player[j][0] < (wal_x[c]+12) && player[j][0] > wal_x[c])
					return 1;
				if(player[i][1] > wal_y[c] && k < wal_y[c] && player[j][0] < (wal_x[c]+12) && player[j][0] > wal_x[c])
					return 1;
			}
		}
		if(z >= 75)
			return 1; 

		player[i][0] = z;
		if(q == 1)
			player[i][1] = k;
		if(player[0][0] == 70)
			return 6;
		break;

	case DOWN:
		k = player[i][1]+4;
		z = player[i][0];
		for(c=0;c<=v-1;c++)
		{
			if(player[i][1] < wal_y[c] && k > wal_y[c] && z < (wal_x[c]+12) && z > wal_x[c])
				return 1;

		}	
		if(k > 38)
			return 1;
		if(player[i][0] == player[j][0] && k == player[j][1])
		{
			q = 1;
			printf("��������� ���ðڽ��ϱ�?\n");
			sw(i);
			for(c=0;c<=v+h;c++)
			{
				if(player[i][0] < wal_x_h[c] && z > wal_x_h[c] && player[j][1] < (wal_y_h[c]+8) && player[j][1] > wal_y_h[c])
					return 1;
				if(player[i][0] > wal_x_h[c] && z < wal_x_h[c] && player[j][1] < (wal_y_h[c]+8) && player[j][1] > wal_y_h[c])
					return 1;
				if(player[i][1] < wal_y[c] && k > wal_y[c] && player[i][0] < (wal_x[c]+12) && player[i][0] > wal_x[c])
					return 1;
				if(player[i][1] > wal_y[c] && k < wal_y[c] && player[i][0] < (wal_x[c]+12) && player[i][0] > wal_x[c])
					return 1;
			}
		}
		if(k <= 2)
			return 1; 

		player[i][1] = k;
		if(q == 1)
			player[i][0] = z;
		break;
	case UP:
		k = player[i][1] - 4;
		z = player[i][0];
		for(c=0;c<=v-1;c++)
		{
			if(player[i][1] > wal_y[c] && k < wal_y[c] && z < (wal_x[c]+12) && z > wal_x[c])
				return 1;

		}
		if(k < 2)
			return 1;
		if(player[i][0] == player[j][0] && k == player[j][1])
		{
			q = 1;
			printf("��������� ���ðڽ��ϱ�?\n");
			sw(i);
			for(c=0;c<=v+h;c++)
			{
				if(player[i][0] < wal_x_h[c] && z > wal_x_h[c] && player[j][1] < (wal_y_h[c]+8) && player[j][1] > wal_y_h[c])
					return 1;
				if(player[i][0] > wal_x_h[c] && z < wal_x_h[c] && player[j][1] < (wal_y_h[c]+8) && player[j][1] > wal_y_h[c])
					return 1;
				if(player[i][1] < wal_y[c] && k > wal_y[c] && player[i][0] < (wal_x[c]+12) && player[i][0] > wal_x[c])
					return 1;
				if(player[i][1] > wal_y[c] && k < wal_y[c] && player[i][0] < (wal_x[c]+12) && player[i][0] > wal_x[c])
					return 1;
			}
		}
		if(k >=37 )
			return 1; 

		player[i][1] = k;
		if(q == 1)
			player[i][0] = z;
		break;
	default:
		goto in;
	}
	return 0;
}
void map()
{
	int i;
	int c;
	system("mode con: cols=75 lines=45");
	printf("         A       B       C       D       E       F       G       H     \n");
	printf("   ������  ������  ������  ������  ������  ������  ������  ������  ������\n");
	printf("   ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��\n");
	printf("   ������  ������  ������  ������  ������  ������  ������  ������  ������\n 1\n");
	printf("   ������  ������  ������  ������  ������  ������  ������  ������  ������\n");
	printf("   ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��\n");
	printf("   ������  ������  ������  ������  ������  ������  ������  ������  ������\n 2\n");
	printf("   ������  ������  ������  ������  ������  ������  ������  ������  ������\n");
	printf("   ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��\n");
	printf("   ������  ������  ������  ������  ������  ������  ������  ������  ������\n 3\n");
	printf("   ������  ������  ������  ������  ������  ������  ������  ������  ������\n");
	printf("   ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��\n");
	printf("   ������  ������  ������  ������  ������  ������  ������  ������  ������\n 4\n");
	printf("   ������  ������  ������  ������  ������  ������  ������  ������  ������\n");
	printf("   ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��\n");
	printf("   ������  ������  ������  ������  ������  ������  ������  ������  ������\n 5\n");
	printf("   ������  ������  ������  ������  ������  ������  ������  ������  ������\n");
	printf("   ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��\n");
	printf("   ������  ������  ������  ������  ������  ������  ������  ������  ������\n 6\n");
	printf("   ������  ������  ������  ������  ������  ������  ������  ������  ������\n");
	printf("   ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��\n");
	printf("   ������  ������  ������  ������  ������  ������  ������  ������  ������\n 7\n");
	printf("   ������  ������  ������  ������  ������  ������  ������  ������  ������\n");
	printf("   ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��\n");
	printf("   ������  ������  ������  ������  ������  ������  ������  ������  ������\n 8\n");
	printf("   ������  ������  ������  ������  ������  ������  ������  ������  ������\n");
	printf("   ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��\n");
	printf("   ������  ������  ������  ������  ������  ������  ������  ������  ������\n");
	gotoxy(player[0][0],player[0][1]);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("��");
	gotoxy(player[1][0],player[1][1]);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("��");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	if(wal ==1)
	{
		switch(waly)
		{
		case '1':
			wal_y[v]=5;
			break;
		case '2':
			wal_y[v]=9;
			break;
		case '3':
			wal_y[v]=13;
			break;
		case '4':
			wal_y[v]=17;
			break;
		case '5':
			wal_y[v]=21;
			break;
		case '6':
			wal_y[v]=25;
			break;
		case '7':
			wal_y[v]=29;
			break;
		case '8':
			wal_y[v]=33;
			break;
		}
		switch(walx)
		{
		case 'A':
			wal_x[v]=5;
			break;
		case 'B':
			wal_x[v]=13;
			break;
		case 'C':
			wal_x[v]=21;
			break;
		case 'D':
			wal_x[v]=29;
			break;
		case 'E':
			wal_x[v]=37;
			break;
		case 'F':
			wal_x[v]=45;
			break;
		case 'G':
			wal_x[v]=53;
			break;
		case 'H':
			wal_x[v]=61;
			break;

		}
		for(c=0;c<=v+h;c++)
		{
			if(c == v)
				continue;
			if(wal_y[v] > wal_y_h[c] &&  wal_y[v] < (wal_y_h[c]+8) && wal_x[v] < wal_x_h[c] && (wal_x[v]+12) > wal_x_h[c])
			{
				wal_hc = 2;
			}
			if(wal_y[v] == wal_y[c] && wal_x[v] < wal_x[c] && (wal_x[v]+12) > wal_x[c])
			{
				wal_hc = 2;
			}
			if(wal_y[v] == wal_y[c] && wal_x[v] > wal_x[c] && (wal_x[v]-12) < wal_x[c])
			{
				wal_hc = 2;
			}
		}
	}

	else if(wal == 2)
	{
		switch(waly)
		{
		case '1':
			wal_y_h[h]=2;
			break;
		case '2':
			wal_y_h[h]=6;
			break;
		case '3':
			wal_y_h[h]=10;
			break;
		case '4':
			wal_y_h[h]=14;
			break;
		case '5':
			wal_y_h[h]=18;
			break;
		case '6':
			wal_y_h[h]=22;
			break;
		case '7':
			wal_y_h[h]=26;
			break;
		case '8':
			wal_y_h[h]=30;
			break;
		}
		switch(walx)
		{
		case 'A':
			wal_x_h[h]=10;
			break;
		case 'B':
			wal_x_h[h]=18;
			break;
		case 'C':
			wal_x_h[h]=26;
			break;
		case 'D':
			wal_x_h[h]=34;
			break;
		case 'E':
			wal_x_h[h]=42;
			break;
		case 'F':
			wal_x_h[h]=50;
			break;
		case 'G':
			wal_x_h[h]=58;
			break;
		case 'H':
			wal_x_h[h]=66;
			break;
		}
		for(c=0;c<=v+h;c++)
		{
			if(c == h)
				continue;
			if(wal_x_h[h] > wal_x[c] && wal_x_h[h] < (wal_x[c]+12) && wal_y_h[h] < wal_y[c] && (wal_y_h[h]+8) > wal_y[c])
			{	
				wal_c = 2;
			}
			if(wal_x_h[h] == wal_x_h[c] && wal_y_h[h] < wal_y_h[c] && (wal_y_h[h]+8) > wal_y_h[c])
			{
				wal_c=2;
			}
			if(wal_x_h[h] == wal_x_h[c] && wal_y_h[h] > wal_y_h[c] && (wal_y_h[h]-8) <wal_y_h[c])
			{
				wal_c=2;
			}
		}	
	}


	for(i=0;i<=v-1;i++)
	{
		gotoxy(wal_x[i],wal_y[i]);
		printf("������������");
	}
	for(i=0;i<=h-1;i++)
	{
		gotoxy(wal_x_h[i],wal_y_h[i]);
		printf("��");
		gotoxy(wal_x_h[i],wal_y_h[i]+1);
		printf("��");
		gotoxy(wal_x_h[i],wal_y_h[i]+2);
		printf("��");
		gotoxy(wal_x_h[i],wal_y_h[i]+3);
		printf("��");
		gotoxy(wal_x_h[i],wal_y_h[i]+4);
		printf("��");
		gotoxy(wal_x_h[i],wal_y_h[i]+5);
		printf("��");
		gotoxy(wal_x_h[i],wal_y_h[i]+6);
		printf("��");
	}
	if(wal_c != 2 && wal == 2)
		h++;
	if(wal_hc !=2 && wal == 1)
		v++;
	gotoxy(1,38);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	fflush(stdin);
	return ;
}
void sw(int i)
{
	char iput = 0;
	fflush(stdin);
K:
	if(ms !=2)
	{
		if(m == 1 && i == 0)
		{
			iput = _getch();
			for(i=0;i<256;i++)
			{
				message[i] = 0;
			}
			message[0] = iput;
			strLen = send(hClntSock,message,sizeof(message),0); // ����������
			if(strLen == SOCKET_ERROR)   
			{
				printf("���Ͽ���! [send]\n");
				Quit = true;
			}
		}
		else if(m == 1 && i == 1)
		{
			strLen = recv(hClntSock,message,sizeof(message),0);
			if(strLen == SOCKET_ERROR )
			{
				printf("���Ͽ���! [recv]\n");
				Quit = true;
			}
			iput = message[0];
		}
		else
			iput = _getch();
	}
	else if(ms ==2)
	{
		if(i==0)
		{
			strLen = recv(hClntSock,message,sizeof(message),0);
			if(strLen == SOCKET_ERROR )
			{
				printf("���Ͽ���! [recv]\n");
				Quit = true;
			}
			iput = message[0];
		}
		else if(i ==1)
		{
			iput = _getch();
			for(i=0;i<256;i++)
			{
				message[i] = 0;
			}
			message[0] = iput;
			strLen = send(hClntSock,message,sizeof(message),0); // ����������
			if(strLen == SOCKET_ERROR)   
			{
				printf("���Ͽ���! [send]\n");
				Quit = true;
			}
		}
	}

	switch(iput)
	{
	case LEFT:
		z = player[j][0] - 8;
		k = player[j][1];
		return;
	case RIGHT:
		z = player[j][0] + 8;
		k = player[j][1];
		return;
	case DOWN:
		z = player[j][0];
		k = player[j][1] + 4;
		return;
	case UP:
		z = player[j][0];
		k = player[j][1] - 4;
		return;
	default:
		printf("������°� ��������\n");
		goto K;
	}
	return ;
}
void end()
{
	char select = 0;
	int i;
	printf("1.����\n");
	printf("2.����\n");

	for(;;)
	{
		fflush(stdin);
		select = _getch();

		switch(select)
		{
		case '1':
			for(i=0;i<=v+h;i++)
			{
				wal_x[i] = 0;
				wal_y[i] = 0;
				wal_x_h[i] = 0;
				wal_y_h[i] = 0;
			}
			v=0;
			h=0;
			for(i=0;i<=10;i++)
			{
				name[1][i] = 0;
				name[0][i] = 0;
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			return;
		case '2':
			exit(0);
		default:
			printf("������°� ������.\n");
		}
	}
}
int multi_server()
{
	player[0][0]=6;
	player[0][1]=19;
	player[1][0]=70;
	player[1][1]=19;

	printf("�÷��̾��� �̸��� �Է����ּ���\n");
	scanf("%s",&name[0]);
	printf("��ø� ��ٷ� �ּ���");

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

	if(listen(hServSock,5)==SOCKET_ERROR)
		ErrorHandling("listen() error!");
	szClntAddr=sizeof(clntAddr);
	hClntSock = accept(hServSock,(SOCKADDR*)&clntAddr,&szClntAddr);
	if(hClntSock==INVALID_SOCKET)
		ErrorHandling("accept() error!");

	printf("dd");

	while(!Quit)
	{
		strcpy(message,name[0]);
		if(!strcmp(message,"exit"))
			Quit = true;

		strLen = send(hClntSock,message,sizeof(message),0); // ����������
		if(strLen == SOCKET_ERROR)   
		{
			printf("���Ͽ���! [send]\n");
			Quit = true;
		}
		strLen = recv(hClntSock,message,sizeof(message),0);
		if(strLen == SOCKET_ERROR )
		{
			printf("���Ͽ���! [recv]\n");
			Quit = true;
		}
		strcpy(name[1],message);
		start();
	}

	Quit = true;

	printf("main �Լ�����!!\n");
	closesocket(hClntSock);
	WSACleanup();

	return 0;
}
int multi_client()
{
	printf("�̸� : ");
	scanf("%s",&name[1]);
	fflush(stdin);
	printf("ip : ");
	scanf("%s",ip);
	WSAStartup(MAKEWORD(2,0),&wsadata);

	hClntSock = socket(PF_INET,SOCK_STREAM,0);
	memset(&sockaddr,0,sizeof(sockaddr));

	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.S_un.S_addr = inet_addr(ip);
	sockaddr.sin_port = htons(atoi("9888"));

	connect(hClntSock,(SOCKADDR*)&sockaddr,sizeof(sockaddr));

	while(1)
	{
		strcpy(message,name[1]);
		if(!strcmp(message,"exit"))
			Quit = true;

		strLen = recv(hClntSock,message,sizeof(message),0);
		if(strLen == SOCKET_ERROR )
		{
			printf("���Ͽ���! [recv]\n");
			Quit = true;
		}
		strcpy(name[0],message);
		strcpy(message,name[1]);
		strLen = send(hClntSock,message,sizeof(message),0); // ����������
		if(strLen == SOCKET_ERROR)   
		{
			printf("���Ͽ���! [send]\n");
			Quit = true;
		}
		start();
	}
	closesocket(hClntSock);
	WSACleanup();

	return 0;
}
void ErrorHandling(char *message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}