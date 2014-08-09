// 2SAT using DFS, too slow

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
using namespace std;

bool test(const vector<bool> &term, int depth, const vector<pair<int, int>> &clause, const vector<vector<int>> &mapping) {
	for (int i=0; i<mapping[depth].size(); ++i) {
		int a = clause[mapping[depth][i]].first, b = clause[mapping[depth][i]].second;
		if (abs(a)>depth+1 || abs(b)>depth+1) continue;
		bool s = a>0 ? term[a-1]: !term[-a-1]; 
		if (s) continue;
		s = b>0 ? term[b-1]: !term[-b-1];
		if (!s) return false;
	}
	return true;
}

bool twoSAT(vector<bool> &term, int depth, const vector<pair<int, int>> &clause, const vector<vector<int>> &mapping) {
	if (depth == term.size()) return true;
	term[depth] = 1;
	if (test(term, depth, clause, mapping) && twoSAT(term, depth+1, clause, mapping)) return true;
	term[depth] = 0;
	return test(term, depth, clause, mapping) && twoSAT(term, depth+1, clause, mapping);
}

int main() {
	ifstream fin("C:\\Users\\Administrator\\Desktop\\2sat1.txt");
	int N;
	fin>>N;
	vector<pair<int, int>> clause(N);
	vector<vector<int>> mapping(N);
	for (int i=0; i<N; ++i) {
		fin>>clause[i].first>>clause[i].second;
		mapping[abs(clause[i].first)-1].push_back(i);
		mapping[abs(clause[i].second)-1].push_back(i);
	}
	fin.close();
	vector<bool> term(N);
	cout<<twoSAT(term, 0, clause, mapping)<<endl;
	return 0;
}