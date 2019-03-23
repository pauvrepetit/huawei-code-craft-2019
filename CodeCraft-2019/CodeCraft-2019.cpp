#include "iostream"
#include "input.h"
//#include "tree.h"
#include "grid.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

int main(int argc, char *argv[])
{
    std::cout << "Begin" << std::endl;
	
	if(argc < 5){
		std::cout << "please input args: carPath, roadPath, crossPath, answerPath" << std::endl;
		exit(1);
	}
	
	string carPath(argv[1]);
	string roadPath(argv[2]);
	string crossPath(argv[3]);
	string answerPath(argv[4]);
	
	std::cout << "carPath is " << carPath << std::endl;
	std::cout << "roadPath is " << roadPath << std::endl;
	std::cout << "crossPath is " << crossPath << std::endl;
	std::cout << "answerPath is " << answerPath << std::endl;
	
	if(input(carPath, roadPath, crossPath) == false){
		cout << "input error" << endl;
		exit(1);
	}
	grid_solve(answerPath);
	return 0;
}

