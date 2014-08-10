// 2SAT using Papadimitriou, time complexity O(log(n)(n^2)m)

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <utility>
#include <cmath>
using namespace std;

bool test(const vector<bool> &term, const vector<pair<int, int>> &clause, const vector<vector<int>> &mapping, int k, set<int> &s) {
	if (k == -1) {
		for (int i=0; i<clause.size(); ++i) {
			bool a = term[abs(clause[i].first)-1], b = term[abs(clause[i].second)-1];
			if (clause[i].first < 0) a = !a;
			if (clause[i].second < 0) b = !b;
			if (!(a||b)) s.insert(i);
		}
	} else {
		for (int i=0; i<mapping[k].size(); ++i) {
			bool a = term[abs(clause[mapping[k][i]].first)-1], b = term[abs(clause[mapping[k][i]].second)-1];
			if (clause[mapping[k][i]].first < 0) a = !a;
			if (clause[mapping[k][i]].second < 0) b = !b;
			if (!(a||b)) s.insert(mapping[k][i]);
			else s.erase(mapping[k][i]);
		}
	}
	return s.empty();
}

bool twoSAT(vector<bool> &term, const vector<pair<int, int>> &clause, const vector<vector<int>> &mapping) {
	int N = 0;
	for (int i=0; i<mapping.size(); ++i) {
		if (mapping[i].size() > 0) ++N;
	}
	for (int i=0; i<log((double)N); ++i) {
		for (int j=0; j<term.size(); ++j) term[j] = rand() % 2;
		set<int> s;
		long long n = (long long)2*N*N;
		int k = -1;
		for (long long j=0; j<n; ++j) {
			if (test(term, clause, mapping, k, s)) return true;
			int p = rand() % s.size();
			set<int>::iterator it = s.begin();
			for (int q=0; q<p; ++q) ++it;
			k = rand()%2? abs(clause[*it].first)-1: abs(clause[*it].second)-1;
			term[k] = !term[k];
		}
	}
	return false;
}

void preprocess(vector<pair<int, int>> &clause, int N) {
	int M = clause.size();
	vector<int> v(N, 0);
	for (int i=0; i<M; ++i) {
		int idx = abs(clause[i].first) - 1;
		if (v[idx] == 0) {
			v[idx] = clause[i].first>0? 1: -1;
		} else if (v[idx] == 1) { 
			if (clause[i].first < 0) v[idx] = 2; 
		} else if (v[idx] == -1) {
			if (clause[i].first > 0) v[idx] = 2; 
		}
	}
	for (int i=0; i<M; ++i) {
		int idx = abs(clause[i].second) - 1;
		if (v[idx] == 0) {
			v[idx] = clause[i].second>0? 1: -1;
		} else if (v[idx] == 1) { 
			if (clause[i].second < 0) v[idx] = 2; 
		} else if (v[idx] == -1) { 
			if (clause[i].second > 0) v[idx] = 2; 
		}
	}
	vector<pair<int, int>> temp;
	for (int i=0; i<M; ++i) {
		if (v[abs(clause[i].first)-1]==2 && v[abs(clause[i].second)-1]==2) {
			temp.push_back(clause[i]);
		}
	}
	if (temp.size() < clause.size()) {
		clause = temp;
		v.clear();
		temp.clear();
		preprocess(clause, N);
	}
}

int main() {
	ifstream fin("C:\\Users\\Administrator\\Desktop\\2sat6.txt");
	int M, N;
	fin>>M;
	vector<pair<int, int>> clause(M);
	for (int i=0; i<M; ++i) fin>>clause[i].first>>clause[i].second;
	fin.close();
	preprocess(clause, N=M);
	M = clause.size();
	vector<vector<int>> mapping(N);
	for (int i=0; i<M; ++i) {
		mapping[abs(clause[i].first)-1].push_back(i);
		mapping[abs(clause[i].second)-1].push_back(i);
	}
	vector<bool> term(N);
	cout<<twoSAT(term, clause, mapping)<<endl;
	return 0;
}