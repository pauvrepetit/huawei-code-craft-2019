#include "iostream"
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

typedef struct Car{
	int id;
	int from;
	int to;
	int speed;
	int planTime;
	bool operator < (const Car &rhs) const {
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


vector<int> string_analysis(string &one_line){
	vector<int> re_value;
	int value = 0;
	int can_push = 0;
	for(int i = 1; i < one_line.size(); ++i){
		if(one_line[i] == '-'){
			can_push = -1;
			continue;
		}
		if(one_line[i] >= '0' && one_line[i] <= '9'){
			value = value * 10 + one_line[i] - '0';
			if(can_push == 0)
				can_push = 1;
		}
		else{
			if(can_push != 0){
				re_value.push_back(value * can_push);
				value = 0;
				can_push = 0;
			}
			
		}
		
	}
	return re_value;
}

vector<Car> car;
vector<Road> road;
vector<Cross> cross;
vector<Cross_temporary> cross_temporary;

int Dijkstra(int s);
struct Heap {
	int id;
	double w;
	bool operator < (const Heap &rhs) const {
		return w < rhs.w;
	}
};
void Output(int from, int to, int &plantime, int car_speed);	
vector<vector <int> > front_road;
vector<vector <int> > front_cross;
ofstream outfile;

int main(int argc, char *argv[])
{
    std::cout << "Begindasd" << std::endl;
	
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
	
	// TODO:read input filebuf
	// TODO:process
	// TODO:write output file
	
	ifstream infile;
	infile.open(carPath);
//	if(infile.is_open())
//		cout << "open" << endl;

	string one_line;
	
	getline(infile, one_line);
	for(;getline(infile, one_line);){
		vector<int> re_value = string_analysis(one_line);
		Car new_car;
		new_car.id = re_value[0];
		new_car.from = re_value[1];
		new_car.to = re_value[2];
		new_car.speed = re_value[3];
		new_car.planTime = re_value[4];
		car.push_back(new_car);
	}
	infile.close();

	infile.open(roadPath, ios::in);
	getline(infile, one_line);
	for(;getline(infile, one_line);){
		vector<int> re_value = string_analysis(one_line);
		Road new_road;
		new_road.id = re_value[0];
		new_road.length = re_value[1];
		new_road.speed = re_value[2];
		new_road.channel = re_value[3];
		new_road.from = re_value[4];
		new_road.to = re_value[5];
		new_road.isDuplex = re_value[6];
		road.push_back(new_road);
	}
	infile.close();

	infile.open(crossPath, ios::in);
	getline(infile, one_line);
	for(;getline(infile, one_line);){
		vector<int> re_value = string_analysis(one_line);
		Cross new_cross;
		new_cross.id = re_value[0];
		for(int i = 0; i < 4; ++i){
			new_cross.roadId[i] = re_value[i + 1];
		}
		cross.push_back(new_cross);
	}
	infile.close();

	//cout << "end  2 " << endl;
	for(int i = 0; i < cross.size(); ++i){
		//cout << i << endl;
		Cross_temporary new_cross_temporary;
		new_cross_temporary.id = cross[i].id;
		for(int j = 0; j < 4; ++j){
			//cout << i << j << endl;
			new_cross_temporary.roadId[j] = cross[i].roadId[j];
			if(new_cross_temporary.roadId[j] == -1)
				continue;
			if(road[cross[i].roadId[j] - 5000].to == cross[i].id && road[cross[i].roadId[j] - 5000].isDuplex == 0)	//5000
				new_cross_temporary.roadId[j] = -1;
			if(new_cross_temporary.roadId[j] == -1)
				continue;
			//cout << i << j << endl;
			if(road[cross[i].roadId[j] - 5000].to == cross[i].id)
				new_cross_temporary.to[j] = road[cross[i].roadId[j] - 5000].from;
			else
				new_cross_temporary.to[j] = road[cross[i].roadId[j] - 5000].to;
			//cout << i << j <<endl;
			new_cross_temporary.length[j] = static_cast<double>(road[cross[i].roadId[j] - 5000].length) / road[cross[i].roadId[j] - 5000].speed;				
		}
		//cout << i << endl;
		cross_temporary.push_back(new_cross_temporary);
	}
	//cout << "end 1  " << endl;
	front_cross.resize(cross.size() + 1);
	for(int i = 0; i < front_cross.size(); ++i){
		front_cross[i].resize(cross.size() + 1);
	}

	front_road.resize(cross.size() + 1);
	for(int i = 0; i < front_road.size(); ++i){
		front_road[i].resize(cross.size() + 1);
	}

	//cout << "end   " << endl;
	for(int i = 0; i < cross.size(); ++i){
		Dijkstra(i+1);
	}
	

	sort(car.begin(), car.end());
	int planTime = car[0].planTime;
	outfile.open(answerPath, ios::out);
	for(int i = 0; i < car.size(); ++i){
		outfile << "(" << car[i].id << ", " << planTime;
		Output(car[i].from, car[i].to, planTime, car[i].speed);
		outfile << ")" << endl;
	}
	return 0;
}

int Dijkstra(int s) {
	double *dis = (double *)malloc(sizeof(double) * (cross.size() + 1));
	priority_queue<Heap> q;

	for(int i = 0; i <= cross.size(); ++i) 
		dis[i] = 2147483647;
	dis[s] = 0;
	q.push(Heap{s, dis[s]});
	front_cross[s][s] = -1;

	while(!q.empty()) {
		Heap x = q.top(); 
		q.pop();
		if(dis[x.id] != x.w) 
			continue;
		for(int i = 0; i < 4; ++i){
			if(cross_temporary[x.id - 1].roadId[i] == -1)
				continue;
			int k = cross_temporary[x.id - 1].to[i];
			if(dis[k] > dis[x.id] + cross_temporary[x.id - 1].length[i]){
				dis[k] = dis[x.id] + cross_temporary[x.id - 1].length[i];
				front_cross[s][k] = x.id;
				front_road[s][k] = cross_temporary[x.id - 1].roadId[i];
				q.push(Heap{k, dis[k]});
			}
		}
	}
	return 0;

}

void Output(int from, int to, int &plantime, int car_speed){
	if(to == from)
		return;
	Output(from, front_cross[from][to], plantime, car_speed);
	plantime += road[front_cross[from][to] ].length / min(road[front_cross[from][to] ].speed, car_speed);
	outfile << ", " << front_road[from][to];
}