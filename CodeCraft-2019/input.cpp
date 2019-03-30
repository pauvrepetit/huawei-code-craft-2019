#include "input.h"

vector<Car> car;
vector<Road> road;
vector<Cross> cross;
ofstream outfile;
vector<int> car_num;
vector<int> road_num;
vector<int> cross_num;

int find_road_num(int x){
	for(decltype(road.size() ) i = 0; i < road.size(); ++i)
		if(road_num[i] == x)
			return i;
}

int find_cross_num(int x){
	for(decltype(road.size() ) i = 0; i < cross.size(); ++i)
		if(cross_num[i] == x)
			return i;
}

int car_numtoreal(int x){
	return car_num[x];
}

int road_numtoreal(int x){
	return road_num[x];
}

int cross_numtoreal(int x){
	return cross_num[x];
}

vector<int> string_analysis(string &one_line){
	vector<int> re_value;
	int value = 0;
	int can_push = 0;
	for(decltype(one_line.size() )  i = 1; i < one_line.size(); ++i){
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

bool input(string &carPath, string &roadPath, string &crossPath){
    ifstream infile;
	infile.open(carPath);

	string one_line;
	
	getline(infile, one_line);
	for(;getline(infile, one_line);){
		vector<int> re_value = string_analysis(one_line);
		Car new_car;
		new_car.id = re_value[0] ;// car 10000
		car_num.push_back(new_car.id);
		new_car.from = re_value[1] ;     // cross 1
		new_car.to = re_value[2] ;		// cross 1
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
		new_road.id = re_value[0] ;  // road 5000
		road_num.push_back(new_road.id);
		new_road.length = re_value[1];
		new_road.speed = re_value[2];
		new_road.channel = re_value[3];
		new_road.from = re_value[4] ;// cross 1
		new_road.to = re_value[5] ;// cross 1
		new_road.isDuplex = re_value[6];
        new_road.len_sped = static_cast<double>(new_road.length)/new_road.speed;
		road.push_back(new_road);
	}
	infile.close();

	infile.open(crossPath, ios::in);
	getline(infile, one_line);
	for(;getline(infile, one_line);){
		vector<int> re_value = string_analysis(one_line);
		Cross new_cross;	
		new_cross.id = re_value[0] ; //cross 1
		cross_num.push_back(new_cross.id);
		for(int i = 0; i < 4; ++i){
			new_cross.roadId[i] = re_value[i + 1];
		}
		cross.push_back(new_cross);
	}
	infile.close();

	for(decltype(car.size()) i = 0; i < car.size(); ++i){
		car[i].id = i;
		car[i].from = find_cross_num(car[i].from);
		car[i].to = find_cross_num(car[i].to);
	}

	for(decltype(car.size()) i = 0; i < road.size(); ++i){
		road[i].id = i;
		road[i].from = find_cross_num(road[i].from);
		road[i].to = find_cross_num(road[i].to);
	}

	for(decltype(car.size()) i = 0; i < cross.size(); ++i){
		cross[i].id = i ; //cross 1
		for(int j = 0; j < 4; ++j){
			if(cross[i].roadId[j] != -1)
				cross[i].roadId[j] = find_road_num(cross[i].roadId[j]);
		}
	}
    return true;
}