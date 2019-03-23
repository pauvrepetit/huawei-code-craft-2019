#include "grid.h"
#include <utility>
#include <stack>

using std::pair;
using std::make_pair;
using std::stack;

vector < pair<int, int> > cross_num;
vector <bool> cross_num_conflict;


stack<int> road_answer;

bool numbering(int row, int column, int id){
    bool re_bool = true;
    if(cross_num_conflict[id] == true && cross_num[id] != make_pair(row, column))
        return false;
    if(cross_num_conflict[id] == true)
        return true;
    cross_num_conflict[id] = true;
    cross_num[id] = make_pair(row, column);
    for(int i = 0;i < 4; ++i){
        if(cross_temporary[id].roadId[i] == -1)
            continue;
        switch (i)
        {
            case 0:
                re_bool = re_bool & numbering(row - 1, column, cross_temporary[id].to[i]);
                break;

            case 1:
                re_bool = re_bool & numbering(row, column + 1, cross_temporary[id].to[i]);
                break;
            
            case 2:
                re_bool = re_bool & numbering(row + 1, column, cross_temporary[id].to[i]);
                break;

            case 3:
                re_bool = re_bool & numbering(row, column - 1, cross_temporary[id].to[i]);
                break;

            default:
                break;
        }
    }
    return re_bool;
}

void preprocessing(){
    build_weighted_map();
    shortest_path();
    return;
}

bool numbering_cross(){
    cross_num.resize(cross.size() + 1 );
    cross_num_conflict.resize(cross.size() + 1, false);
    preprocessing();
    if(numbering(0,0,1) == false){
        cout << "numbering_cross error" << endl;
        return false;
    }
    return true;
}

bool lu_to_rd(int from, int to){
    if(from == to)
        return true;
    if(cross_num[from].first < cross_num[to].first && cross_temporary[from].roadId[2] != -1){
        road_answer.push(cross_temporary[from].roadId[2]);
        if(lu_to_rd(cross_temporary[from].to[2], to) == true)
            return true;
        else{
            road_answer.pop();
        }
    }
    if(cross_num[from].second < cross_num[to].second && cross_temporary[from].roadId[1] != -1){
        road_answer.push(cross_temporary[from].roadId[1]);
        if(lu_to_rd(cross_temporary[from].to[1], to) == true)
            return true;
        else{
            road_answer.pop();
            return false;
        }
        
    }
    else
        return false;
}

bool rd_to_lu(int from, int to){
    if(from == to)
        return true;
    if(cross_num[from].first > cross_num[to].first && cross_temporary[from].roadId[0] != -1){
        road_answer.push(cross_temporary[from].roadId[0]);
        if(rd_to_lu(cross_temporary[from].to[0], to) == true)
            return true;
        else{
            road_answer.pop();
        }
    }
    if(cross_num[from].second > cross_num[to].second && cross_temporary[from].roadId[3] != -1){
        road_answer.push(cross_temporary[from].roadId[3]);
        if(rd_to_lu(cross_temporary[from].to[3], to) == true)
            return true;
        else{
            road_answer.pop();
            return false;
        }
        
    }
    else
        return false;
    
}

bool ru_to_ld(int from, int to){
    if(from == to)
        return true;
    if(cross_num[from].second > cross_num[to].second && cross_temporary[from].roadId[3] != -1){
        road_answer.push(cross_temporary[from].roadId[3]);
        if(ru_to_ld(cross_temporary[from].to[3], to) == true)
            return true;
        else{
            road_answer.pop();
        }
    }
    if(cross_num[from].first < cross_num[to].first && cross_temporary[from].roadId[2] != -1){
        road_answer.push(cross_temporary[from].roadId[2]);
        if(ru_to_ld(cross_temporary[from].to[2], to) == true)
            return true;
        else{
            road_answer.pop();
            return false;
        }
        
    }
    else
        return false;
    
}

bool ld_to_ru(int from, int to){
    if(from == to)
        return true;
    if(cross_num[from].second < cross_num[to].second && cross_temporary[from].roadId[1] != -1){
        road_answer.push(cross_temporary[from].roadId[1]);
        if(ld_to_ru(cross_temporary[from].to[1], to) == true)
            return true;
        else{
            road_answer.pop();
        }
    }
    if(cross_num[from].first > cross_num[to].first && cross_temporary[from].roadId[0] != -1){
        road_answer.push(cross_temporary[from].roadId[0]);
        if(ld_to_ru(cross_temporary[from].to[0], to) == true)
            return true;
        else{
            road_answer.pop();
            return false;
        }
        
    }
    else
        return false;
    
}

void clear_road_answer(){
    if(road_answer.empty() == true)
        return;
    int id = road_answer.top();
    road_answer.pop();
    clear_road_answer();
    outfile << ", " << id;
}

void output(string &answerPath){
    outfile.open(answerPath, ios::out);

    for(decltype(car.size()) i = 0; i < car.size(); i++){
        if((cross_num[car[i].from ].first <= cross_num[car[i].to ].first) && (cross_num[car[i].from ].second <= cross_num[car[i].to ].second)){
            outfile << "(" << car[i].id << ", " << car[i].planTime;
            if(lu_to_rd(car[i].from, car[i].to) == false){
                cout << "can't find a road" << endl;
                //return;
                short_road_output(car[i].from, car[i].to);
            }
            clear_road_answer();
            outfile << ")" << endl;
        }

        if((cross_num[car[i].from ].first > cross_num[car[i].to ].first) && (cross_num[car[i].from ].second > cross_num[car[i].to ].second)){
            outfile << "(" << car[i].id << ", " << car[i].planTime + 80;
            if(rd_to_lu(car[i].from, car[i].to) == false){
                cout << "can't find a road" << endl;
                //return;
                short_road_output(car[i].from, car[i].to);
            }
            clear_road_answer();
            outfile << ")" << endl;
        }

        if((cross_num[car[i].from ].first <= cross_num[car[i].to ].first) && (cross_num[car[i].from ].second > cross_num[car[i].to ].second)){
            outfile << "(" << car[i].id << ", " << car[i].planTime + 160;
            if(ru_to_ld(car[i].from, car[i].to) == false){
                cout << "can't find a road" << endl;
                //return;
                short_road_output(car[i].from, car[i].to);
            }
            clear_road_answer();
            outfile << ")" << endl;
        }

        if((cross_num[car[i].from ].first > cross_num[car[i].to ].first) && (cross_num[car[i].from ].second <= cross_num[car[i].to ].second)){
            outfile << "(" << car[i].id << ", " << car[i].planTime + 240;
            if(ld_to_ru(car[i].from, car[i].to) == false){
                cout << "can't find a road" << endl;
                //return;
                short_road_output(car[i].from, car[i].to);
            }
            clear_road_answer();
            outfile << ")" << endl;
        }
    }
}

bool grid_solve(string &answerPath){
    if(numbering_cross() == false)
        return false;
    output(answerPath);
    return true;
}
