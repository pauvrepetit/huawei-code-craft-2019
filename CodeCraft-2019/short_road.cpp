#include "short_road.h"



vector<Cross_temporary> cross_temporary;

vector<vector <int> > front_road;
vector<vector <int> > front_cross;

bool build_weighted_map(){
    for(decltype(cross.size() ) i = 0; i < cross.size(); ++i){
		Cross_temporary new_cross_temporary;
		new_cross_temporary.id = cross[i].id;
		for(int j = 0; j < 4; ++j){
			new_cross_temporary.roadId[j] = cross[i].roadId[j];
			if(new_cross_temporary.roadId[j] == -1)
				continue;
			if(road[cross[i].roadId[j] ].to == i && road[cross[i].roadId[j]].isDuplex == 0)	//5000
				new_cross_temporary.roadId[j] = -1;
			if(new_cross_temporary.roadId[j] == -1)
				continue;
			if(road[cross[i].roadId[j] ].to == i)
				new_cross_temporary.to[j] = road[cross[i].roadId[j] ].from;
			else
				new_cross_temporary.to[j] = road[cross[i].roadId[j] ].to;		
		}
		cross_temporary.push_back(new_cross_temporary);
	}
    return true;
}

bool Dijkstra(int s, int t) {
	double *dis = (double *)malloc(sizeof(double) * (cross.size() + 1));
	priority_queue<Heap> q;

	for(decltype(cross.size() )  i = 0; i <= cross.size(); ++i) {
		front_cross[s][i] = -1;
		front_road[s][i] = -1;
		dis[i] = 2147483647;
	}
	dis[s] = 0;
	q.push(Heap{s, dis[s]});
	

	while(!q.empty()) {
		Heap x = q.top(); 
		q.pop();
		if(x.id == t){
			free(dis);
			return true;
		}
		if(dis[x.id] != x.w) 
			continue;
		for(int i = 0; i < 4; ++i){
			if(cross_temporary[x.id ].roadId[i] == -1 || (road[cross_temporary[x.id ].roadId[i] ].len_sped / road[cross_temporary[x.id ].roadId[i] ].channel) > ROAD_LIMIT)
				continue;
			int k = cross_temporary[x.id ].to[i];
			if(dis[k] > dis[x.id] + road[cross_temporary[x.id ].roadId[i] ].len_sped){
				dis[k] = dis[x.id] + road[cross_temporary[x.id ].roadId[i] ].len_sped;
				front_cross[s][k] = x.id;
				front_road[s][k] = cross_temporary[x.id ].roadId[i];
				q.push(Heap{k, dis[k]});
			}
		}
	}
	free(dis);
	return false;

}


bool pre_short(){
	front_cross.resize(cross.size() + 1);
	for(decltype(cross.size() )  i = 0; i < front_cross.size(); ++i){
		front_cross[i].resize(cross.size() + 1);
	}

	front_road.resize(cross.size() + 1);
	for(decltype(cross.size() )  i = 0; i < front_road.size(); ++i){
		front_road[i].resize(cross.size() + 1);
	}
	return true;
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
	//	Dijkstra(i);
	}

	return true;
}

