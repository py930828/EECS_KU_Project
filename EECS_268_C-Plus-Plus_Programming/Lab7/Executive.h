#ifndef EXECUTIVE_H_
#define EXECUTIVE_H_
#include<iostream>
#include<string>
#include<fstream>
#include"Board.h"
using namespace std;
class Executive
{
private:
        int m;
        int n;
        int crow;
        int ccol;
        int step;
	Board* bd;
public:
/* @ pre none
* @ post initialize the private varaible and the pointer
* return none
*/
        Executive(int argv[]);
/* @ pre none
* @ post delete the contents of the pointer
* return none
*/
	~Executive();
/* @ pre none
* @ post check if it's valid to move
* return true if it's good to move false else wise
*/
	bool isSafe(int row, int col);
/* @ pre none
* @ post move the chess to the next spot
* return true if success move, false else wise
*/
        bool move(int row, int col);
	
};
#endif

