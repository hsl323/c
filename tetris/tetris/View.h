#ifndef VIEW-H
#define VIEW_H
#include "iostream"
#include "Consola.h"

class View
{
	int block[4][4];
public:
	void start_screen();
	void score(float score);
};
void start_screen(void)
{
	gotoxy(20,2);
	textbackground(WHITE);
	for(int i=0;i<40;i++)
		std::cout << " ";
	for(int i=0;i<40;i++)
	{
		gotoxy(20,i+3);
		textbackground(WHITE);
		std::cout << "  ";
		textbackground(BLACK);
		for(int i=0;i<18;i++)
			std::cout << "  ";
		textbackground(WHITE);
		std::cout << "  ";
	}
	textbackground(BLACK);
	gotoxy(20,43);
	textbackground(WHITE);
	for(int i=0;i<40;i++)
		std::cout << " ";
	gotoxy(63,2);
	std::cout << "            ";
	for(int i=0;i<4;i++)
	{
		gotoxy(63,i+3);
		textbackground(WHITE);
		std::cout << "  ";
		textbackground(BLACK);
		for(int i=0; i<4;i++)
			std::cout << "  ";
		textbackground(WHITE);
		std::cout << "  ";
	}
	gotoxy(63,7);
	std::cout << "            ";
	textbackground(BLACK);
	gotoxy(25,45);
	std::cout << " Score : ";
}
void score(float score)
{
	gotoxy(34,45);
	std::cout << score;
}
#endif