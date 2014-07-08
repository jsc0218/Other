// Prim without Heap, time complexity O(nm)

#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
using namespace std;

struct Node {
	Node(int v, int d=0): id(v), dist(d) {}
	int id;
	int dist;
};

int Prim(const vector<vector<Node>> &graph) {
	int N = graph.size(), cost = 0;
	vector<bool> visited(N, false);
	visited[0] = true;
	for (int i=1; i<N; ++i) {
		int minDist = INT_MAX, nodeId = INT_MAX;
		for (int j=0; j<N; ++j) {
			for (int k=1; k<graph[j].size(); ++k) {
				if (visited[graph[j][0].id] == visited[graph[j][k].id]) continue;
				if (graph[j][k].dist >= minDist) continue;
				minDist = graph[j][k].dist;
				nodeId = visited[graph[j][0].id]? graph[j][k].id: graph[j][0].id;
			}
		}
		visited[nodeId] = true;
		cost += minDist;
	}
	return cost;
}

int main() {
	ifstream fin("C:\\Users\\Administrator\\Desktop\\edges.txt");
	int n, m;
	fin>>n>>m;
	vector<vector<Node>> graph(n, vector<Node>(1, Node(-1)));
	for (int i=0; i<n; ++i) graph[i][0].id = i;
	for (int i=0; i<m; ++i) {
		int v1, v2, dist;
		fin>>v1>>v2>>dist;
		graph[--v1].push_back(Node(--v2, dist));
	}
	fin.close();
	cout<<Prim(graph)<<endl;
	return 0;
}