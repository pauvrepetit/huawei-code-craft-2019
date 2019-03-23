#ifndef _TREE_H
#define _TREE_H
#include "input.h"
#include "short_road.h"

struct Heap {
	int id;
	double w;
	bool operator < (const Heap &rhs) const {
		return w < rhs.w;
	}
};

bool tree_solve(string &);
bool minimum_spanning_tree();
#endif