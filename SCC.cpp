// computing strongly connected components

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
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

int DFS(const vector<vector<int>> &graph, int s, vector<bool> &visited) {
	int count = 1;
	visited[s] = true;
	for (int i=0; i<graph[s].size(); ++i) {
		if (!visited[graph[s][i]]) {
			count += DFS(graph, graph[s][i], visited);
		}
	}
	return count;
}

vector<int> computeSCC(const vector<vector<int>> &graph) {
	int N = graph.size();
	vector<vector<int>> revGraph(N, vector<int>());
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
	for (int i=0; i<N; ++i) {
		visited[i] = false;
		revGraph[i].resize(0);
	}
	revGraph.resize(0);
	vector<int> res(5, 0);
	for (int i=finishTime-1; i>=0; --i) {
		if (!visited[map[i]]) {
			res.push_back(DFS(graph, map[i], visited));
			sort(res.begin(), res.end());
			reverse(res.begin(), res.end());
			res.resize(res.size()-1);
		}
	}
	return res;
}

int main() {
	int N = 875714;
	vector<vector<int>> graph(N, vector<int>());
	ifstream fin("C:\\Users\\Administrator\\Desktop\\SCC.txt");
	while (!fin.eof()) {
		string line;
		getline(fin, line);
		int pos = 0;
		while (line[pos] != ' ') ++pos;
		int i = atoi(line.substr(0, pos).c_str()) - 1;
		int tmp = ++pos;
		while (line[pos] != ' ') ++pos;
		int j = atoi(line.substr(tmp, pos-tmp).c_str()) - 1;
		graph[i].push_back(j);
	}
	fin.close();
	vector<int> res = computeSCC(graph);
	for (int i=0; i<res.size() && i<5; ++i) cout << res[i] << " ";
	return 0;
}