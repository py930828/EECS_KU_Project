#include <iostream>
#include <string>
#include <fstream>
#include "Executive.h"


int main(int argc, char* argv[])
{
	Executive exe(argv[1]);//argv[1]);
	exe.run();
	cout<<"main finished";
	return 0;
}
