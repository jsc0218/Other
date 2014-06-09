// Dijkstra without Heap, time complexity O(nm)

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Node {
	Node(int v, int d=0): id(v), dist(d) {}
	int id;
	int dist;
};

void Dijkstra(const vector<vector<Node>> &graph, int s, vector<int> &dist) {
	int N = graph.size();
	vector<bool> visited(N, false);
	visited[s] = true;
	for (int i=0; i<graph[s].size(); ++i) dist[graph[s][i].id] = graph[s][i].dist;
	for (int i=1; i<N; ++i) {
		int minVal = INT_MAX, t = s;
		for (int j=0; j<N; ++j) {
			if (!visited[j] && dist[j]<minVal) {
				t = j;
				minVal = dist[j];
			}
		}
		visited[t] = true;
		for (int j=1; j<graph[t].size(); ++j) {
			int v = graph[t][j].id;
			if (!visited[v]) dist[v] = min(dist[v], graph[t][j].dist+dist[t]);
		}
	}
}

int main() {
	int N = 200;
	vector<vector<Node>> graph(N);
	ifstream fin("C:\\Users\\Administrator\\Desktop\\dijkstraData.txt");
	for (int i=0; i<N; ++i) {
		string line;
		getline(fin, line);
		graph[i].push_back(Node(i));
		int j = 0;
		while (line[j] != '\t') ++j;
		int k = ++j;
		for (; j<line.size(); ++j) {
			if (line[j] == '\t') {
				int t = k;
				while (line[t] != ',') ++t;
				string a = line.substr(k, t-k), b = line.substr(t+1, j);
				graph[i].push_back(Node(atoi(a.c_str())-1, atoi(b.c_str())));
				k = j + 1;
			}
		}
	}
	fin.close();
	vector<int> dist(N, INT_MAX);
	Dijkstra(graph, 0, dist);
	cout<<dist[6]<<" "<<dist[36]<<" "<<dist[58]<<" "<<dist[81]<<" "<<dist[98]<<" ";
	cout<<dist[114]<<" "<<dist[132]<<" "<<dist[164]<<" "<<dist[187]<<" "<<dist[196]<<" ";
	return 0;
}