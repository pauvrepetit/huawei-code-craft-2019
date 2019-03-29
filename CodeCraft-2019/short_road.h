#ifndef _SHORTROAD_
#define _SHORTROAD_

#include "input.h"

extern vector<Cross_temporary> cross_temporary;
extern vector<vector <int> > front_road;
extern vector<vector <int> > front_cross;

void short_road_output(int from, int to);
bool build_weighted_map();
bool shortest_path();
bool Dijkstra(int s, int t) ;
bool pre_short();
#endif