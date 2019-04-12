#ifndef _INPUT_H
#define _INPUT_H
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#define MAX_TIME 1000
#define ROAD_LIMIT 12000

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
	int isPriority;
	int isPreset;
	bool operator < (const Car &rhs) const {
		/*if (planTime == rhs.planTime) {

			return speed > rhs.speed;
		}
		return planTime < rhs.planTime;*/
		return isPriority > rhs.isPriority;
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

typedef struct Preset{
	int id;
	int plantime;
	vector<int> roadId;
}Preset;

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

struct car_Heap{
	int number;
	int priority;
	int plantime;
	int preset;
	int speed;
	bool operator < (const car_Heap &rhs) const {
	//	if(plantime == rhs.plantime && preset == rhs.preset && priority == rhs.priority)
	//		return speed < rhs.speed;
		if(plantime == rhs.plantime && preset == rhs.preset)
			return priority < rhs.priority;
		if(plantime == rhs.plantime)
			return preset < rhs.preset;
		return plantime > rhs.plantime;
	}
};


extern vector<Car> car;
extern vector<Road> road;
extern vector<Cross> cross;
extern vector<Preset> preset;
extern ofstream outfile;
extern vector<vector<double>> road_preset;
extern int map_1_2;
extern int late_set;

int car_numtoreal(int x);
int road_numtoreal(int x);
int cross_numtoreal(int x);
int find_preset_num(int x);
double tree_sum (int cross_num,int k);
bool input(string &carPath, string &roadPath, string &crossPath, string &presetAnswer);
vector<int> string_analysis(string &one_line);

#endif