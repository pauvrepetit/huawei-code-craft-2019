#include "tree.h"


vector<Cross_temporary> cross_temporary;

vector<vector <int> > front_road;
vector<vector <int> > front_cross;
ofstream outfile;

vector<int> root;
vector<bool> is_mini_tree;

bool build_weighted_map(){
    for(decltype(cross.size() ) i = 0; i < cross.size(); ++i){
		Cross_temporary new_cross_temporary;
		new_cross_temporary.id = cross[i].id;
		for(int j = 0; j < 4; ++j){
			new_cross_temporary.roadId[j] = cross[i].roadId[j];
			if(new_cross_temporary.roadId[j] == -1)
				continue;
            if(is_mini_tree[cross[i].roadId[j] - 5000] == 0)           //  mini_tree new increase
                new_cross_temporary.roadId[j] = -1;
			if(road[cross[i].roadId[j] - 5000].to == cross[i].id && road[cross[i].roadId[j] - 5000].isDuplex == 0)	//5000
				new_cross_temporary.roadId[j] = -1;
			if(new_cross_temporary.roadId[j] == -1)
				continue;
			if(road[cross[i].roadId[j] - 5000].to == cross[i].id)
				new_cross_temporary.to[j] = road[cross[i].roadId[j] - 5000].from;
			else
				new_cross_temporary.to[j] = road[cross[i].roadId[j] - 5000].to;
			new_cross_temporary.length[j] = road[cross[i].roadId[j] - 5000].len_sped;		
			//cout << i +1 << " " << 	new_cross_temporary.to[j]  << endl;	
		}
		cross_temporary.push_back(new_cross_temporary);
	}
    return true;
}

int Dijkstra(int s) {
	double *dis = (double *)malloc(sizeof(double) * (cross.size() + 1));
	priority_queue<Heap> q;

	for(decltype(cross.size() )  i = 0; i <= cross.size(); ++i) 
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
/* Shortest path output */
void Output(int from, int to, int &plantime, int car_speed, int &roadCount){
	if(to == from)
		return;
	roadCount++;
	Output(from, front_cross[from][to], plantime, car_speed, roadCount);
	plantime += road[front_cross[from][to] ].length / min(road[front_cross[from][to] ].speed, car_speed);
	outfile << ", " << front_road[from][to];
	return;
}

bool tree_solve(string &answerPath){
	root.resize(cross.size()+1 , 0);
	is_mini_tree.resize(road.size(), 0);
    if(minimum_spanning_tree() == false)
        return false;
    build_weighted_map();
	shortest_path();
	output(answerPath);
	return true;
}

bool minimum_spanning_tree(){
	vector<Road> road_to_tree(road);
    sort(road_to_tree.begin(), road_to_tree.end());
    decltype(cross.size() )  sum = 0;
    for(decltype(cross.size() )  i = 0; i < road_to_tree.size() && sum < cross.size() - 1; i++){
        if(road_to_tree[i].isDuplex == 0){
            cout << "can't init a undirect tree" << endl;
            return false;
        }
        int from_root, to_root;
        from_root = find_root(road_to_tree[i].from);
        to_root = find_root(road_to_tree[i].to);
        if(from_root == to_root)
            continue;
        root[from_root] = to_root;
        sum++;
		int id = road_to_tree[i].id - 5000;  
		//cout << road.size() << endl;
        is_mini_tree[id] = true; // 5000??????????????
    }
	if(sum == cross.size() - 1)
    	return true;
	else{
		cout << "can't init a undirect tree" << endl;
        return false;
	}
}

int find_root(int x){
    if(root[x] == 0)
        return(x);
    root[x] = find_root(root[x]);
    return root[x];
}

bool shortest_path(){
    front_cross.resize(cross.size() + 1);
	for(decltype(cross.size() )  i = 0; i < front_cross.size(); ++i){
		front_cross[i].resize(cross.size() + 1);
	}

	front_road.resize(cross.size() + 1);
	for(decltype(cross.size() )  i = 0; i < front_road.size(); ++i){
		front_road[i].resize(cross.size() + 1);
	}

	for(decltype(cross.size() )  i = 0; i < cross.size(); ++i){
		Dijkstra(i+1);
	}

	return true;
}

void output(string &answerPath){
	outfile.open(answerPath, ios::out);
    for(decltype(cross.size() )  i = 0; i < car.size(); ++i){
		outfile << "(" << car[i].id << ", " << car[i].planTime;
		short_road_output(car[i].from, car[i].to);
		outfile << ")" << endl;
	}
}

void short_road_output(int from, int to){
    if(to == from)
		return;
	short_road_output(from, front_cross[from][to]);
	outfile << ", " << front_road[from][to];
}
