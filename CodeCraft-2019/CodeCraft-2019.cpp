#include "iostream"
#include "input.h"
//#include "tree.h"
//#include "grid.h"
#include "dyn.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

int main(int argc, char *argv[])
{
    std::cout << "Begin" << std::endl;
	
	if(argc < 6){
		std::cout << "please input args: carPath, roadPath, crossPath,  presetAnswer, answerPath" << std::endl;
		exit(1);
	}
	
	string carPath(argv[1]);
	string roadPath(argv[2]);
	string crossPath(argv[3]);
	string presetAnswer(argv[4]);
	string answerPath(argv[5]);
	
	std::cout << "carPath is " << carPath << std::endl;
	std::cout << "roadPath is " << roadPath << std::endl;
	std::cout << "crossPath is " << crossPath << std::endl;
	std::cout << "presetAnswer is " << presetAnswer << std::endl;
	std::cout << "answerPath is " << answerPath << std::endl;
	
	/*if(input(carPath, roadPath, crossPath, presetAnswer) == false){
		cout << "input error" << endl;
		exit(1);
	}*/
	outfile.open(answerPath, ios::out);
	//grid_solve(answerPath);
	//dyn_solve(answerPath);*/
	ifstream infile;
	infile.open("../CodeCraft-2019/1.txt");
	string one_line;
	for(;getline(infile, one_line);){
		outfile << one_line << endl;
	}
	
	return 0;
}

