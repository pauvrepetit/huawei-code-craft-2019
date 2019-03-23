#include "short_road.h"

struct Heap {
	int id;
	double w;
	bool operator < (const Heap &rhs) const {
		return w < rhs.w;
	}
};

vector<Cross_temporary> cross_temporary;

vector<vector <int> > front_road;
vector<vector <int> > front_cross;

bool build_weighted_map(){
	Cross_temporary new_cross_temporary;
	cross_temporary.push_back(new_cross_temporary);
    for(decltype(cross.size() ) i = 0; i < cross.size(); ++i){
		Cross_temporary new_cross_temporary;
		new_cross_temporary.id = cross[i].id;
		for(int j = 0; j < 4; ++j){
			new_cross_temporary.roadId[j] = cross[i].roadId[j];
			if(new_cross_temporary.roadId[j] == -1)
				continue;
            //if(is_mini_tree[cross[i].roadId[j] - 5000] == 0)           //  mini_tree new increase
            //    new_cross_temporary.roadId[j] = -1;
			if(road[cross[i].roadId[j] - 5000].to == cross[i].id && road[cross[i].roadId[j] - 5000].isDuplex == 0)	//5000
				new_cross_temporary.roadId[j] = -1;
			if(new_cross_temporary.roadId[j] == -1)
				continue;
			if(road[cross[i].roadId[j] - 5000].to == cross[i].id)
				new_cross_temporary.to[j] = road[cross[i].roadId[j] - 5000].from;
			else
				new_cross_temporary.to[j] = road[cross[i].roadId[j] - 5000].to;
			new_cross_temporary.length[j] = road[cross[i].roadId[j] - 5000].len_sped;		
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
			if(cross_temporary[x.id ].roadId[i] == -1)
				continue;
			int k = cross_temporary[x.id ].to[i];
			if(dis[k] > dis[x.id] + cross_temporary[x.id ].length[i]){
				dis[k] = dis[x.id] + cross_temporary[x.id ].length[i];
				front_cross[s][k] = x.id;
				front_road[s][k] = cross_temporary[x.id ].roadId[i];
				q.push(Heap{k, dis[k]});
			}
		}
	}
	return 0;

}

void short_road_output(int from, int to){
    if(to == from)
		return;
	short_road_output(from, front_cross[from][to]);
	outfile << ", " << front_road[from][to];
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

