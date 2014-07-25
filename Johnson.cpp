// Johnson Algorithm, time complexity O(nmlog(n)), space complexity O(n^2)

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

const int MAX = 100000000;

struct Node {
	Node(int v, int d=0): id(v), dist(d) {}
	int id;
	int dist;
};

// O(mn) time, O(n) space
bool BellmanFord(const vector<vector<Node>> &graph, int s, vector<int> &dist) {
	int N = graph.size();
	vector<vector<Node>> rGraph(N);
	for (int i=0; i<N; ++i) {
		for (int j=0; j<graph[i].size(); ++j) {
			rGraph[graph[i][j].id].push_back(Node(i, graph[i][j].dist));
		}
	}
	vector<vector<int>> table(2, vector<int>(N));
	for (int i=0; i<N; ++i) table[0][i] = i!=s? MAX: 0;
	bool bStop = false;
	for (int i=1; i<=N && !bStop; ++i) {
		bStop = true;
		for (int j=0; j<N; ++j) {
			int minW = INT_MAX;
			for (int k=0; k<rGraph[j].size(); ++k) {
				minW = min(minW, table[(i-1)%2][rGraph[j][k].id]+rGraph[j][k].dist);
			}
			table[i%2][j] = min(table[(i-1)%2][j], minW);
			if (table[i%2][j] < table[(i-1)%2][j]) bStop = false;
		}
	}
	dist = table[N%2];
	return bStop;
}

// O(mlog(n)) time, O(n) space
void Dijkstra(const vector<vector<Node>> &graph, int s, vector<int> &dist) {
	int N = graph.size();
	vector<bool> visited(N, false);
	visited[s] = true;
	for (int i=0; i<graph[s].size(); ++i) dist[graph[s][i].id] = graph[s][i].dist;
	typedef pair<int, int> Elem;
	vector<Elem> elems(N);
	for (int i=0; i<N; ++i) elems[i].first = dist[i], elems[i].second = i;	
	priority_queue<Elem, vector<Elem>, greater<Elem>> pq(elems.begin(), elems.end());
	for (int i=1; i<N; ++i) {
		int t = s;
		while (t == s) {
			Elem e = pq.top(); pq.pop();
			if (!visited[e.second]) {
				t = e.second;
				visited[t] = true;
			}
		}
		for (int j=0; j<graph[t].size(); ++j) {
			int v = graph[t][j].id, d = graph[t][j].dist+dist[t];
			if (!visited[v] && dist[v]>d) {
				dist[v] = d;
				pq.push(Elem(d, v));
			}
		}
	}
}

bool Johnson(vector<vector<Node>> &graph, vector<vector<int>> &table) {
	int N = graph.size();
	for (int i=1; i<N; ++i) graph[0].push_back(Node(i, 0));
	if (!BellmanFord(graph, 0, table[0])) return false;
	for (int i=1; i<N; ++i) {
		for (int j=0; j<graph[i].size(); ++j) {
			graph[i][j].dist += table[0][i] - table[0][graph[i][j].id]; 
		}
	}
	for (int i=1; i<N; ++i) {
		Dijkstra(graph, i, table[i]);
		for (int j=1; j<N; ++j) table[i][j] += table[0][j] - table[0][i];
	}
	for (int i=1; i<N; ++i) {
		for (int j=0; j<graph[i].size(); ++j) {
			graph[i][j].dist += table[0][graph[i][j].id] - table[0][i]; 
		}
	}
	return true;
}

int main() {
	ifstream fin("C:\\Users\\Administrator\\Desktop\\large.txt");
	int V, E, s, v, d;
	fin>>V>>E;
	vector<vector<Node>> graph(V+1);
	for (int i=0; i<E; ++i) {
		fin>>s>>v>>d;
		graph[s].push_back(Node(v, d));
	}
	fin.close();
	vector<vector<int>> table(V+1, vector<int>(V+1, MAX));
	bool bAcyclic = Johnson(graph, table);
	cout<<bAcyclic<<endl;
	if (bAcyclic) {
		int sp = INT_MAX;
		for (int i=1; i<=V; ++i) {
			for (int j=1; j<=V; ++j) sp = min(sp, table[i][j]);
		}
		cout<<sp<<endl;
	}
	return 0;
}