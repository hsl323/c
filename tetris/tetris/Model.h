#ifndef MODEL_H
#define MODEL_H
#include "iostream"
#include "ctime"


class Model{
	int map[10][20];
public:
    int random_block(int blocks){
        int random=0, shape1[4][4] = {{0,0,0,0},{0,1,0,0},{1,1,1,0},{0,0,0,0}}, shape2[4][4] = {{0,0,0,0},{0,0,0,0},{2,2,2,2},{0,0,0,0}}, shape3[4][4] = {{0,0,0,0},{0,3,3,0},{0,3,3,0},{0,0,0,0}};
        int shape4[4][4] = {{0,0,0,0},{4,0,0,0},{4,4,4,0},{0,0,0,0}}, shape5[4][4] = {{0,0,0,0},{0,0,5,0},{5,5,5,0},{0,0,0,0}}, shape6[4][4] = {{0,0,0,0},{6,6,0,0},{0,6,6,0},{0,0,0,0}}, shape7[4][4] = {{0,0,0,0},{0,7,7,0},{7,7,0,0},{0,0,0,0}};
        srand(unsigned(time(NULL)));
        random=rand()%7+1;
        if(random==1)
            return shape1[4][4];
        else if(random==2)
            return shape2[4][4];
        else if(random==3)
            return shape3[4][4];
        else if(random==4)
            return shape4[4][4];
        else if(random==5)
            return shape5[4][4];
        else if(random==6)
            return shape6[4][4];
        else if(random==7)
            return shape7[4][4];
    }
};
#endif