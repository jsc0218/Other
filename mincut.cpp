// randomized contraction algorithm for the min cut problem

#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
using namespace std;

void printGraph(const vector<list<int>> &graph) {
	for (int i=0; i<graph.size(); ++i) {
		for (list<int>::const_iterator it=graph[i].begin(); it!=graph[i].end(); ++it) {
			cout << *it << " ";
		}
		cout << endl;
	}
}

int minCut(vector<list<int>> &graph) {
	int eCount = 0, nCount = 0, N = graph.size();
	for (int i=0; i<N; ++i) {
		eCount += graph[i].front();
		if (graph[i].front() > 0) ++nCount;
	}
	if (nCount == 2) return eCount >> 1;
	int r = rand() % eCount, tail, head;
	for (int i=0; i<N; ++i) {
		if (r+1 > graph[i].front()) {
			r -= graph[i].front();
			continue;
		}
		tail = i + 1;
		list<int>::iterator it = graph[i].begin();
		for (int j=0; j<=r; ++j) ++it;
		head = *it;
		break;
	}
	graph[head-1].splice(graph[head-1].end(), graph[tail-1], ++graph[tail-1].begin(), graph[tail-1].end());
	graph[head-1].front() += graph[tail-1].front();
	graph[tail-1].front() = 0;
	for (int i=0; i<N; ++i) {
		for (list<int>::iterator it=++graph[i].begin(); it!=graph[i].end(); ++it) {
			if (*it == tail) *it = head;
		}
	}
	for (list<int>::iterator it=++graph[head-1].begin(); it!=graph[head-1].end(); ++it) {
		if (*it == head) {
			it = --graph[head-1].erase(it);
			--graph[head-1].front();
		}
	}
	return minCut(graph);
}

int main() {
	ifstream fin("C:\\Users\\Administrator\\Desktop\\kargerMinCut.txt");
	int N = 200;
	vector<list<int>> graph(N, list<int>(1, 0));
	for (int i=0; i<N; ++i) {
		string line;
		getline(fin, line);
		int end = line.find_first_of('\t'), begin = end + 1;
		while ((end=line.find_first_of('\t', begin)) != string::npos) {
			string str = line.substr(begin, end-begin);
			graph[i].push_back(atoi(str.c_str()));
			++graph[i].front();
			begin = end + 1;
		}
	}
	fin.close();
	int tryCount = 40000, res = INT_MAX;
	for (int i=0; i<tryCount; ++i) {
		vector<list<int>> copy(graph);
		res = min(res, minCut(copy));
	}
	cout << res << endl;
	return 0;
}