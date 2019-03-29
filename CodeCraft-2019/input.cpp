#include "input.h"

vector<Car> car;
vector<Road> road;
vector<Cross> cross;
ofstream outfile;

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
		new_car.id = re_value[0] - 10000;   // car 10000
		new_car.from = re_value[1] - 1;     // cross 1
		new_car.to = re_value[2] - 1;		// cross 1
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
		new_road.id = re_value[0] - 5000;  // road 5000
		new_road.length = re_value[1];
		new_road.speed = re_value[2];
		new_road.channel = re_value[3];
		new_road.from = re_value[4] - 1;// cross 1
		new_road.to = re_value[5] - 1;// cross 1
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
		new_cross.id = re_value[0] - 1; //cross 1
		for(int i = 0; i < 4; ++i){
			new_cross.roadId[i] = re_value[i + 1];
			if(new_cross.roadId[i] != -1)
				new_cross.roadId[i] -= 5000;//road 5000
		}
		cross.push_back(new_cross);
	}
	infile.close();

    return true;
}