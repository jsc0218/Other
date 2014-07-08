// Prim with Heap, time complexity O(mlog(n))

#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <queue>
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
	vector<int> dist(N, INT_MAX);
	for (int i=1; i<graph[0].size(); ++i) dist[graph[0][i].id] = graph[0][i].dist;
	typedef pair<int,int> Elem;
	vector<Elem> elems(N);
	for (int i=0; i<N; ++i) elems[i].first = dist[i], elems[i].second = i;	
	priority_queue<Elem, vector<Elem>, greater<Elem>> pq(elems.begin(), elems.end());
	for (int i=1; i<N; ++i) {
		int t = 0;
		while (t == 0) {
			Elem e = pq.top(); pq.pop();
			if (!visited[e.second]) {
				t = e.second;
				visited[t] = true;
				cost += e.first;
			}
		}
		for (int j=1; j<graph[t].size(); ++j) {
			int v = graph[t][j].id, d = graph[t][j].dist;
			if (!visited[v] && dist[v]>d) {
				dist[v] = d;
				pq.push(Elem(d, v));
			}
		}
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
		graph[v2].push_back(Node(v1, dist));
	}
	fin.close();
	cout<<Prim(graph)<<endl;
	return 0;
}