// 2-Sum, time complexity O(n^2), space complexity O(n)

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main() {
	int N = 1000000, res = 0;
	vector<long long> v(N);
	ifstream fin("C:\\Users\\Administrator\\Desktop\\2sum.txt");
	for (int i=0; i<N; ++i) fin >> v[i];
	fin.close();
	sort(v.begin(), v.end());
	set<int> s;
	for (int i=0; i<N; ++i) {
		long long lb = -10000 - v[i], up = 10000 - v[i];
		int l = i + 1, r = N - 1, j = -1;
		while (l <= r) {
			int m = (l + r) >> 1;
			if (lb < v[m]) r = m - 1;
			else if (lb > v[m]) l = m + 1;
			else j = m;
		}
		if (j == -1) j = l;
		for (; j<N && v[j]<=up; ++j) {
			if (v[j]!=v[i] && s.find(v[i]+v[j])==s.end()) {
				s.insert(v[i]+v[j]);
			}
		}
	}
	cout << s.size();
	return 0;
}