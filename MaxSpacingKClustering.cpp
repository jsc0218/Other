#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// lazy unioin
class UFSets {
public:
	UFSets(int size) {
		for (int i=0; i<size; ++i) sets.push_back(i);
	}
	// O(n)
	int find(int node) {
		while (sets[node] != node) node = sets[node];
		return node;
	}
	// O(n)
	void unionSets(int node1, int node2) {
		sets[find(node1)] = find(node2);		
	}

private:
	vector<int> sets;
};

struct Edge {
	Edge(int h, int t, int c): head(h), tail(t), cost(c) {}
	int head;
	int tail;
	int cost;
	bool operator < (const Edge &edge) const {
		return cost < edge.cost;
	}
};

int maxSpacingKClustering(int N, vector<Edge> &edges, int k) {
	sort(edges.begin(), edges.end());
	UFSets cluster(N);
	for (int i=N, j=0; i>=k; --i, ++j) {
		while (cluster.find(edges[j].head) == cluster.find(edges[j].tail)) ++j;
		if (i == k) return edges[j].cost;
		cluster.unionSets(edges[j].head, edges[j].tail);
	}
	return INT_MAX;
}

int main() {
	ifstream fin("C:\\Users\\Administrator\\Desktop\\clustering1.txt");
	int N, h, t, c;
	fin>>N;
	vector<Edge> edges;
	while (fin>>h>>t>>c) edges.push_back(Edge(--h, --t, c));
	fin.close();
	cout<<maxSpacingKClustering(N, edges, 4)<<endl;
	return 0;
}


#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// lazy unioin + union by rank
class UFSets {
public:
	UFSets(int size) {
		for (int i=0; i<size; ++i) {
			sets.push_back(i);
			ranks.push_back(0);
		}
	}
	// O(log(n))
	int find(int node) {
		while (sets[node] != node) node = sets[node];
		return node;
	}
	// O(log(n))
	void unionSets(int node1, int node2) {
		int p1 = find(node1), p2 = find(node2);
		if (ranks[p1] < ranks[p2]) sets[p1] = p2;
		else if (ranks[p1] > ranks[p2]) sets[p2] = p1;
		else {
			sets[p1] = p2;
			++ranks[p2];
		}
	}

private:
	vector<int> sets;
	vector<int> ranks;
};

struct Edge {
	Edge(int h, int t, int c): head(h), tail(t), cost(c) {}
	int head;
	int tail;
	int cost;
	bool operator < (const Edge &edge) const {
		return cost < edge.cost;
	}
};

int maxSpacingKClustering(int N, vector<Edge> &edges, int k) {
	sort(edges.begin(), edges.end());
	UFSets cluster(N);
	for (int i=N, j=0; i>=k; --i, ++j) {
		while (cluster.find(edges[j].head) == cluster.find(edges[j].tail)) ++j;
		if (i == k) return edges[j].cost;
		cluster.unionSets(edges[j].head, edges[j].tail);
	}
	return INT_MAX;
}

int main() {
	ifstream fin("C:\\Users\\Administrator\\Desktop\\clustering1.txt");
	int N, h, t, c;
	fin>>N;
	vector<Edge> edges;
	while (fin>>h>>t>>c) edges.push_back(Edge(--h, --t, c));
	fin.close();
	cout<<maxSpacingKClustering(N, edges, 4)<<endl;
	return 0;
}


#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// lazy unioin + union by rank + path compression
class UFSets {
public:
	UFSets(int size) {
		for (int i=0; i<size; ++i) {
			sets.push_back(i);
			ranks.push_back(0);
		}
	}
	// m operations, O(m¦Á(n))
	int find(int node) {
		int p = node;
		while (sets[p] != p) p = sets[p];
		sets[node] = p;
		return p;
	}
	// m operations, O(m¦Á(n))
	void unionSets(int node1, int node2) {
		int p1 = find(node1), p2 = find(node2);
		if (ranks[p1] < ranks[p2]) sets[p1] = p2;
		else if (ranks[p1] > ranks[p2]) sets[p2] = p1;
		else {
			sets[p1] = p2;
			++ranks[p2];
		}
	}

private:
	vector<int> sets;
	vector<int> ranks;
};

struct Edge {
	Edge(int h, int t, int c): head(h), tail(t), cost(c) {}
	int head;
	int tail;
	int cost;
	bool operator < (const Edge &edge) const {
		return cost < edge.cost;
	}
};

int maxSpacingKClustering(int N, vector<Edge> &edges, int k) {
	sort(edges.begin(), edges.end());
	UFSets cluster(N);
	for (int i=N, j=0; i>=k; --i, ++j) {
		while (cluster.find(edges[j].head) == cluster.find(edges[j].tail)) ++j;
		if (i == k) return edges[j].cost;
		cluster.unionSets(edges[j].head, edges[j].tail);
	}
	return INT_MAX;
}

int main() {
	ifstream fin("C:\\Users\\Administrator\\Desktop\\clustering1.txt");
	int N, h, t, c;
	fin>>N;
	vector<Edge> edges;
	while (fin>>h>>t>>c) edges.push_back(Edge(--h, --t, c));
	fin.close();
	cout<<maxSpacingKClustering(N, edges, 4)<<endl;
	return 0;
}