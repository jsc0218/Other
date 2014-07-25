// Floyd-Warshall Algorithm, time complexity O(n^3), space complexity O(n^2)

#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
using namespace std;

const int MAX = 100000000;

struct Node {
	Node(int v, int d=0): id(v), dist(d) {}
	int id;
	int dist;
};

bool FloydWarshall(const vector<vector<Node>> &graph, vector<vector<int>> &table) {
	int N = graph.size();
	for (int i=1; i<N; ++i) {
		table[i][i] = 0;
		for (int j=0; j<graph[i].size(); ++j) {
			table[i][graph[i][j].id] = graph[i][j].dist;
		}
		if (table[i][i] < 0) return false;
	}
	for (int k=1; k<N; ++k) {
		for (int i=1; i<N; ++i) {
			for (int j=1; j<N; ++j) {
				table[i][j] = min(table[i][j], table[i][k]+table[k][j]);
			}
			if (table[i][i] < 0) return false;
		}
	}
	return true;
}

int main() {
	ifstream fin("C:\\Users\\Administrator\\Desktop\\g3.txt");
	int V, E, s, v, d;
	fin>>V>>E;
	vector<vector<Node>> graph(V+1);
	for (int i=0; i<E; ++i) {
		fin>>s>>v>>d;
		graph[s].push_back(Node(v, d));
	}
	fin.close();
	vector<vector<int>> table(V+1, vector<int>(V+1, MAX));
	bool bAcyclic = FloydWarshall(graph, table);
	cout<<bAcyclic<<endl;
	if (bAcyclic) {
		int sp = INT_MAX;
		for (int i=1; i<=V; ++i) {
			for (int j=1; j<=V; ++j) {
				sp = min(sp, table[i][j]);
			}
		}
		cout<<sp<<endl;
	}
	return 0;
}