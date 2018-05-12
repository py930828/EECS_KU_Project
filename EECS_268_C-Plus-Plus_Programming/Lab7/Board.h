/*
 * Board.h
 *
 *  Created on: 2016/3/7
 *      Author: long
 */
#ifndef BOARD_H_
#define BOARD_H_
#include<iostream>
using namespace std;
class Board
{
private:
	int m;
	int n;
        int init_row;
        int init_col;
public:
/* @ pre none
* @ post initialize the private varaible and the board pointer
* return none
*/
        Board(int m,int n, int init_row, int init_col);
/* @ pre pointing to a two dimentional array
* @ post delete everything include the pointer content
* return none
*/
	~Board();
/* @ pre none
* @ post store the number in for the knight board
* return int number;
*/
	int** board;
/* @ pre none
* @ post set numbers;
* return set numbers;
*/
	void setvalue(int m, int n, int num);
/* @ pre none
* @ post return numbers;
* return return numbers;
*/
	int getvalue(int crow, int ccol);
	
};
#endif

