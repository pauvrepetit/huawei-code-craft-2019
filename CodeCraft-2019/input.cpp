#include "input.h"

vector<Car> car;
vector<Road> road;
vector<Cross> cross;
vector<Preset> preset;
ofstream outfile;
vector<vector<double>> road_preset;
int map_1_2;

int lowbit(int x)
{
    return x&(-x);
}

void tree_edit(int cross_num,int i,double delta)
{
    for (int j = i; j <= MAX_TIME; j += lowbit(j))
        road_preset[cross_num][j] += delta;
}

double tree_sum (int cross_num,int k)
{
    double ans = 0;
    for (int i = k; i > 0; i -= lowbit(i))
        ans += road_preset[cross_num][i];
    return ans;
}



int find_road_num(int x){
	for(decltype(road.size() ) i = 0; i < road.size(); ++i)
		if(road[i].id == x)
			return i;
	return -1;
}

int find_cross_num(int x){
	for(decltype(road.size() ) i = 0; i < cross.size(); ++i)
		if(cross[i].id == x)
			return i;
	return -1;
}

int find_preset_num(int x){
	for(decltype(preset.size() ) i = 0; i < preset.size(); ++i)
		if(preset[i].id == x)
			return i;
	return -1;
}

int find_car_num(int x){
	for(decltype(car.size() ) i = 0; i < car.size(); ++i)
		if(car[i].id == x)
			return i;
	return -1;
}

int car_numtoreal(int x){
	return car[x].id;
}

int road_numtoreal(int x){
	return road[x].id;
}

int cross_numtoreal(int x){
	return cross[x].id;
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

bool input(string &carPath, string &roadPath, string &crossPath, string &presetAnswer){
    ifstream infile;
	infile.open(carPath);

	string one_line;
	
	getline(infile, one_line);
	for(;getline(infile, one_line);){
		vector<int> re_value = string_analysis(one_line);
		Car new_car;
		new_car.id = re_value[0] ;// car 10000
		//car_num.push_back(new_car.id);
		new_car.from = re_value[1] ;     // cross 1
		new_car.to = re_value[2] ;		// cross 1
		new_car.speed = re_value[3];
		new_car.planTime = re_value[4];
		new_car.isPriority = re_value[5];
		new_car.isPreset = re_value[6];
		//if(new_car.isPreset == 0)
		//	new_car.planTime += 1000;
		car.push_back(new_car);
	}
	/*sort(car.begin(), car.end());
	for(decltype(car.size()) i = 0; i < car.size(); i++){
		car_num.push_back(car[i].id);
	}*/

	infile.close();
	/*if(car[0].id == 24370)
		map_1_2 = 18900;
	else
		map_1_2 = 10200;*/
	

	infile.open(roadPath, ios::in);
	getline(infile, one_line);
	for(;getline(infile, one_line);){
		vector<int> re_value = string_analysis(one_line);
		Road new_road;
		new_road.id = re_value[0] ;  // road 5000
		//road_num.push_back(new_road.id);
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
		//cross_num.push_back(new_cross.id);
		for(int i = 0; i < 4; ++i){
			new_cross.roadId[i] = re_value[i + 1];
		}
		cross.push_back(new_cross);
	}
	infile.close();

	road_preset.resize(road.size());
	for(decltype(road_preset.size() ) i = 0; i < road_preset.size(); ++i){
		road_preset[i].resize(MAX_TIME, 0);
	}

	int temple = 0;
	infile.open(presetAnswer, ios::in);
	getline(infile, one_line);
	for(;getline(infile, one_line);){
		vector<int> re_value = string_analysis(one_line);
		Preset new_preset;	
		new_preset.id = re_value[0] ; //cross 1
		new_preset.plantime = re_value[1];
		//preset_num.push_back(new_preset.id);
		for(decltype(re_value.size() ) i = 2; i < re_value.size(); ++i){
			int road_num = find_road_num(re_value[i]);
			new_preset.roadId.push_back(road_num);
			//tree_edit(road_num,re_value[1],1);
			/*if(road_num == 193 && re_value[1] < 105){
				
				cout << temple << endl;
			}*/
		}
		preset.push_back(new_preset);
	}
	infile.close();

	
	for(decltype(preset.size()) i = 0; i < preset.size(); ++i){
		double inc_time = 0;
		int car_num = find_car_num(preset[i].id);
		car[car_num].planTime = preset[i].plantime;
		for(decltype(preset[i].roadId.size()) j = 0; j < preset[i].roadId.size(); ++j){
			inc_time += static_cast<double>(road[preset[i].roadId[j]].length) / min(road[preset[i].roadId[j]].speed, car[car_num].speed); 
		}
		inc_time *=  15/static_cast<double>(preset[i].roadId.size());
		//if(inc_time > 150)
		//	cout << inc_time << endl;
		for(decltype(preset[i].roadId.size()) j = 0; j < preset[i].roadId.size(); ++j){
			/*if(preset[i].roadId[j] == 193 && preset[i].plantime < 105){
				temple ++;
				cout << temple << endl;
			}*/
				
			tree_edit(preset[i].roadId[j], preset[i].plantime, inc_time); 
		}
	}

	for(decltype(car.size()) i = 0; i < car.size(); ++i){
		//car[i].id = i;
		car[i].from = find_cross_num(car[i].from);
		car[i].to = find_cross_num(car[i].to);
	}

	for(decltype(car.size()) i = 0; i < road.size(); ++i){
		//road[i].id = i;
		road[i].from = find_cross_num(road[i].from);
		road[i].to = find_cross_num(road[i].to);
	}

	for(decltype(car.size()) i = 0; i < cross.size(); ++i){
		//cross[i].id = i ; //cross 1
		for(int j = 0; j < 4; ++j){
			if(cross[i].roadId[j] != -1)
				cross[i].roadId[j] = find_road_num(cross[i].roadId[j]);
		}
	}

    return true;
}