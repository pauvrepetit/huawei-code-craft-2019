#ifndef _TREE_H
#define _TREE_H
#include"input.h"

struct Heap {
	int id;
	double w;
	bool operator < (const Heap &rhs) const {
		return w < rhs.w;
	}
};

int Dijkstra(int s);
bool build_weighted_map();
void Output(int from, int to, int &plantime, int car_speed, int &roadCount);/* Shortest path output */
bool tree_solve(string &);
bool minimum_spanning_tree();
int find_root(int x);
bool shortest_path();
void output(string &);
void short_road_output(int from, int to);
int find_id(int id);
#endif