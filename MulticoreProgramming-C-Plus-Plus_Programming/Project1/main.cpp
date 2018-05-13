#include <iostream>
#include <fstream>
#include <string>
#include "Executive.h"
using namespace std;

int main(int argc, char* argv[]){
  Executive ex(argv[1]);
  ex.ThreadInitial();
  return 0;
}
