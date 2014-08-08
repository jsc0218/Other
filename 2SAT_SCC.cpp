// 2SAT using SCC

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <set>
using namespace std;

void revDFS(const vector<vector<int>> &graph, int s, vector<bool> &visited, int &finishTime, vector<int> &map) {
	visited[s] = true;
	for (int i=0; i<graph[s].size(); ++i) {
		if (!visited[graph[s][i]]) {
			revDFS(graph, graph[s][i], visited, finishTime, map);
		}
	}
	map[finishTime++] = s;
}

bool DFS(const vector<vector<int>> &graph, int s, vector<bool> &visited, set<int> &c) {
	visited[s] = true;
	for (int i=0; i<graph[s].size(); ++i) {
		if (!visited[graph[s][i]]) {
			DFS(graph, graph[s][i], visited, c);
		}
	}
	if (c.find(graph.size()-1-s) != c.end()) return false;
	c.insert(s);
	return true;
}

bool computeSCC(const vector<vector<int>> &graph) {
	int N = graph.size();
	vector<vector<int>> revGraph(N);
	for (int i=0; i<N; ++i) {
		for (int j=0; j<graph[i].size(); ++j) {
			revGraph[graph[i][j]].push_back(i);
		}
	}
	vector<bool> visited(N, false);
	vector<int> map(N);
	int finishTime = 0;
	for (int i=N-1; i>=0; --i) {
		if (!visited[i]) {
			revDFS(revGraph, i, visited, finishTime, map);
		}
	}
	for (int i=0; i<N; ++i) visited[i] = false;
	for (int i=finishTime-1; i>=0; --i) {
		if (!visited[map[i]]) {
			set<int> c;
			if (!DFS(graph, map[i], visited, c)) {
				return false;
			}
		}
	}
	return true;
}

bool twoSAT(const vector<pair<int, int>> &input) {
	int N = input.size();
	vector<vector<int>> graph(1+(N<<1));
	for (int i=0; i<N; ++i) {
		graph[-input[i].first+N].push_back(input[i].second+N);
		graph[-input[i].second+N].push_back(input[i].first+N);
	}
	return computeSCC(graph);
}

int main() {
	ifstream fin("C:\\Users\\Administrator\\Desktop\\2sat2.txt");
	int N;
	fin>>N;
	vector<pair<int, int>> input(N);
	for (int i=0; i<N; ++i) fin>>input[i].first>>input[i].second;
	fin.close();
	cout<<twoSAT(input)<<endl;
	return 0;
}