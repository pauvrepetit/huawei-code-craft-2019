#include "dyn.h"
#include "time.h"

vector<vector<int> > car_path;
vector<double> car_time;
priority_queue< Heap> inc_time;
priority_queue< Heap> dyn_car;

void dyn_feedback(int id, int now){
	if(car[id].from == now)
		return;
	dyn_feedback(id, front_cross[car[id].from][now]);
	car_time[id] += static_cast<double>(road[front_road[car[id].from][now] ].length )/ min(road[front_road[car[id].from][now] ].speed, car[id].speed);
    car_path[id].push_back(front_road[car[id].from][now]);

	return;
}


void dyn_solve(string &answerPath){
    srand (time(NULL));
    car_path.resize(car.size() );
    car_time.resize(car.size(), 0);
    build_weighted_map();
    for(auto car_to:car){
        dyn_car.push(Heap{car_to.id, static_cast<double>(car_to.planTime)});
    }
    pre_short();
    for(;!dyn_car.empty();){
        Heap one_car = dyn_car.top();
        dyn_car.pop();
        for(;!inc_time.empty() && inc_time.top().w < one_car.w;){
            for(auto road_to : car_path[inc_time.top().id]){
                road[road_to].len_sped -= car_time[inc_time.top().id] * 2;
            }
            inc_time.pop();
        }
        bool len = Dijkstra(car[one_car.id].from, car[one_car.id].to);
        if(!len){
            one_car.w += (rand()%5) + 1;
            dyn_car.push(one_car);
            continue;
        }
        dyn_feedback(one_car.id, car[one_car.id].to);
        outfile << "(" << car[one_car.id].id + 10000 << ", " << static_cast<int>( one_car.w);
        for(auto road_to : car_path[one_car.id]){
            outfile << ", " << road_to + 5000;
            road[road_to].len_sped += car_time[one_car.id] * 2;
        }
        outfile << ")" << endl;
        inc_time.push(Heap{static_cast<int>(one_car.id),one_car.w + car_time[one_car.id]});
    }
    
}


