#include "tree.h"

vector<int> root;
vector<bool> is_mini_tree;

int find_root(int x){
    if(root[x] == 0)
        return(x);
    root[x] = find_root(root[x]);
    return root[x];
}

void output(string &answerPath){
	outfile.open(answerPath, ios::out);
    for(decltype(cross.size() )  i = 0; i < car.size(); ++i){
		outfile << "(" << car[i].id << ", " << car[i].planTime;
		short_road_output(car[i].from, car[i].to);
		outfile << ")" << endl;
	}
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

