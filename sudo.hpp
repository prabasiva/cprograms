#ifndef SUDO
#define SUDO
#include <iostream>
#include <vector>
#include <map>
using namespace std;
#define DIM 9
#define SUBDIM 3
#define FALSE 0
#define TRUE 1

int sudoko[DIM][DIM];
void __initialize()
{
int i,j;

/* Initialize the matrix */

for (i=0;i<DIM;i++)
	for (j=0;j<DIM;j++)
		{
		sudoko[i][j]=0;
		}
		

/* preload the sudoko matrix */ 

sudoko[0][2]=4; sudoko[0][3]=1; sudoko[0][6]=5; sudoko[0][7]=6;
sudoko[1][2]=9; sudoko[1][3]=7; 
sudoko[2][1]=8; sudoko[2][3]=3; sudoko[2][4]=6; sudoko[2][8]=2;
sudoko[3][1]=4; sudoko[3][5]=1; sudoko[3][8]=5;
sudoko[4][2]=8; sudoko[4][4]=7; sudoko[4][6]=4; 
sudoko[5][0]=3; sudoko[5][3]=9; sudoko[5][7]=1; 
sudoko[6][0]=9; sudoko[6][4]=8; sudoko[6][5]=7; sudoko[6][7]=3;
sudoko[7][5]=9; sudoko[7][6]=6;
sudoko[8][0]=4; sudoko[8][2]=2; sudoko[8][5]=3; sudoko[8][6]=8;


}



























#endif 


