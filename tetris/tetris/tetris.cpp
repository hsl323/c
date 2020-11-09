#include "iostream"
#include "Consola.h"
#include "View.h"
#include "Windows.h"

int main()
{
	system("mode con: cols=85 lines=50");
	/*View vi;
	vi.start_screen();*/
	int block[4][4];
	block[0][0] = 5;
	block[0][1] = 5;
	block[0][2] = 10;
	int newblock[4][4];

	*newblock = *block;
	for(int i =0 ;i<4;i++)
		std::cout << newblock[0][i];
	return 0;
}