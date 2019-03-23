#ifndef _SHORTROAD_
#define _SHORTROAD_

#include "input.h"

extern vector<Cross_temporary> cross_temporary;

void short_road_output(int from, int to);
bool build_weighted_map();
bool shortest_path();

#endif