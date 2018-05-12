/*
 * Executive.cpp
 *
 *  Created on: 2016/3/15
 *      Author: long
 */
#include"Executive.h"
#include <iostream>
#include <stdlib.h>
using namespace std;
Executive::Executive(int argv[])
{
	step=0;
        m=argv[0];
        n=argv[1];
        crow=argv[2];
        ccol=argv[3];
	bd=new Board(m,n,crow,ccol);
	move(crow,ccol);
}
Executive::~Executive()
{
	bd->~Board();
	delete bd;
	bd=nullptr;
}
bool Executive::isSafe(int row, int col)
{
	if(row<m&&col<n&&row>=0&&col>=0&&bd->getvalue(row,col)==-1)
	{
		return true;
	}
	else
	{
		return false;
	}

}
bool Executive::move(int row, int col)
{
	if(step==m*n)
	{
		for(int i=0;i<m;i++)
		{
			for(int j=0;j<n;j++)
			{
				cout<<"["<<bd->getvalue(i,j)<<"] ";
			}
			cout<<endl;
		}
		return true;
	}

	if(isSafe(row, col))
	{
		bd->setvalue(row, col, step);
		step++;
		if(move(row-1,col-2))
		{
			return true;
		}
		if(move(row + 2,col-1))
		{
			return true;
		}
		if(move(row+1,col-2))
		{
			return true;
			cout<<endl;
		}
		if(move(row-2,col-1))
		{
			return true;
			
		}
		if(move(row-2,col+1))
		{
			return true;
		}
		if(move(row-1,col+2))
		{
			return true;
		}
		if(move(row+1,col+2))
		{
			return true;
		}
		if(move(row+2,col+1))
		{
			return true;
		}
			bd->setvalue(row,col,-1);
			step=step-1;
			return false;
	}
	else
	{
		return false;
	}
}
