#ifndef _INPUT_H
#define _INPUT_H
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using std::string;
using std::cin;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::vector;
using std::priority_queue;
using std::getline;
using std::endl;
using std::min;
using std::max;

typedef struct Car{
	int id;
	int from;
	int to;
	int speed;
	int planTime;
	bool operator < (const Car &rhs) const {
		if (planTime == rhs.planTime) {

			return speed > rhs.speed;
		}
		return planTime < rhs.planTime;
	}
}Car;

typedef struct Road{
	int id;
	int length;
	int speed;
	int channel;
	int from;
	int to;
	int isDuplex;
    double len_sped;
    	bool operator < (const Road &rhs) const {
		if (isDuplex == rhs.isDuplex) {
			return len_sped  < rhs.len_sped;
		}
		return isDuplex > rhs.isDuplex;
	}
}Road;

typedef struct Cross{
	int id;
	int roadId[4];
}Cross;

typedef struct Cross_temporary{
	int id;
	int to[4];
	int roadId[4];
	double length[4];
}Cross_temporary;

struct Heap {
	int id;
	double w;
	bool operator < (const Heap &rhs) const {
		return w > rhs.w;
	}
};

extern vector<Car> car;
extern vector<Road> road;
extern vector<Cross> cross;
extern ofstream outfile;

bool input(string &carPath, string &roadPath, string &crossPath);

#endif