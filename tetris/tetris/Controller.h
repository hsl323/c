#ifndef VIEW-H
#define VIEW_H
#include "iostream"
#include "Model.h"

class Controller
{
	int block[10][20];
public:
	void move_block();
	bool check_line();
};
#endif