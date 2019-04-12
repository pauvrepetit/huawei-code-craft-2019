#include "dyn.h"
#include "time.h"

vector<vector<int> > car_path;
vector<double> car_time;
priority_queue< car_Heap> inc_time;
priority_queue< car_Heap> dyn_car;
int road_number = 0;

void dyn_feedback(int id, int now){
	if(car[id].from == now || now == -1 || front_road[car[id].from][now] == -1){
		return;
    }
    road_number ++;
	dyn_feedback(id, front_cross[car[id].from][now]);
	car_time[id] += static_cast<double>(road[front_road[car[id].from][now] ].length )/ min(road[front_road[car[id].from][now] ].speed, car[id].speed);
    car_path[id].push_back(front_road[car[id].from][now]);
	return;
}


void dyn_solve(string &answerPath){
    int ans = 0;
    srand (time(NULL));
    car_path.resize(car.size() );
    car_time.resize(car.size(), 0);
    build_weighted_map();

    int car_num = 0;
    for(auto car_to:car){
        if(car_to.isPriority == 1 && car_to.isPreset == 0)
            car_to.planTime = max(car_to.planTime, late_set);
        dyn_car.push(car_Heap{car_num++, car_to.isPriority, car_to.planTime, car_to.isPreset, car_to.speed});
    }

    pre_short();
    car_Heap one_car;
    for(;!dyn_car.empty();){
        one_car = dyn_car.top();
        dyn_car.pop();
        for(;!inc_time.empty() && inc_time.top().plantime <=  one_car.plantime;){
            for(auto road_to : car_path[inc_time.top().number]){
                road[road_to].len_sped -= car_time[inc_time.top().number];
            }
            inc_time.pop();
        }

        road_number = 0;

        if(car[one_car.number].isPreset == 1){
             car_path[one_car.number] = preset[find_preset_num(car_numtoreal(one_car.number) )].roadId;
             road_number = car_path[one_car.number].size();
             for(decltype(car_path[one_car.number].size()) i = 0; i < car_path[one_car.number].size(); ++i){
                 car_time[one_car.number] += static_cast<double>(road[car_path[one_car.number][i]].length) / min(road[car_path[one_car.number][i]].speed, car[one_car.number].speed); 
             }
            car_time[one_car.number] *=  15/static_cast<double>(road_number);
            for(auto road_to : car_path[one_car.number]){
                road[road_to].len_sped += car_time[one_car.number];
            }
            one_car.plantime += static_cast<int>(car_time[one_car.number]);
            inc_time.push(one_car);
        }

        else{
            bool len = Dijkstra(car[one_car.number].from, car[one_car.number].to);
            if(!len){
               // if(one_car.priority == 1)
               //     one_car.plantime =  inc_time.top().plantime;
              //  else
                    if(one_car.plantime < MAX_TIME)
                        one_car.plantime =  inc_time.top().plantime +rand()%30;
                    else
                        one_car.plantime =  inc_time.top().plantime + rand()%8 +(20 - one_car.speed) ;
                dyn_car.push(one_car);
                continue;
            }
            dyn_feedback(one_car.number, car[one_car.number].to);
            car_time[one_car.number] *=  15/static_cast<double>(road_number);

            if(one_car.plantime < MAX_TIME){
                bool kg = false;
                for(auto road_to : car_path[one_car.number]){
                    double pre_num = tree_sum(road_to, one_car.plantime + static_cast<int>(car_time[one_car.number])) - tree_sum(road_to, one_car.plantime);
                    if((road[road_to].len_sped + car_time[one_car.number] + pre_num  ) / road[road_to].channel > ROAD_LIMIT){
                        car_time[one_car.number] = 0;
                        car_path[one_car.number].clear();
                        if(inc_time.empty()){
                          //  if(one_car.priority == 1)
                          //      one_car.plantime ++;
                           // else
                                one_car.plantime += rand()%30; //8 + (20 - one_car.speed) ;
                        }
                        else{
                         //   if(one_car.priority == 1)
                          //      one_car.plantime =  inc_time.top().plantime;
                          //  else
                                one_car.plantime =  inc_time.top().plantime +rand()%30; //8 + (20 - one_car.speed);
                        }
                        dyn_car.push(one_car);
                        kg = true;
                        break;
                    } 
                }
                if(kg == true)
                    continue;
            }

            outfile << "(" << car_numtoreal( one_car.number) << ", " <<  one_car.plantime;
            for(auto road_to : car_path[one_car.number]){
                outfile << ", " << road_numtoreal(road_to) ;
                road[road_to].len_sped += car_time[one_car.number];
            }
            outfile << ")" << endl;
            if( one_car.priority == 1)
                ans = one_car.plantime;
            one_car.plantime += static_cast<int>(car_time[one_car.number]);
            inc_time.push(one_car);
        }
    }
    cout << ans << endl;
}


