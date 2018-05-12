/*
 * Board.cpp
 *
 *  Created on: 2016年2月4日
 *      Author: long
 */
#include"Executive.h"
#include<iostream>
#include <stdlib.h>
using namespace std;
Board::Board(int m,int n, int init_row, int init_col)
{
	board=new int*[m];
	for(int i=0;i<m;i++)
	{
		board[i]=new int[n];
		for(int j=0;j<n;j++)
		{
			board[i][j]=-1;
		}
	}
}
Board::~Board()
{
	for(int i=0;i<m;i++)
	{
		delete [] board[i];
	}
	delete board;
	board=nullptr;
}
void Board::setvalue(int crow, int ccol, int num)
{
	board[crow][ccol]=num;
}
int Board::getvalue(int crow, int ccol)
{
	return board[crow][ccol];
}


