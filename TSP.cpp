// DP for Traveling Salesman Problem, time complexity O((2^n)(n^2)), space complexity O(n(2^n))

#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <cmath>
#include <cfloat>
using namespace std;

const int B = 24;

bitset<B> getComb(const vector<int> &comb) {
	bitset<B> bitcombs;
	for (int i=0; i<comb.size(); ++i) bitcombs.set(comb[i], true);
	return bitcombs;
}

bool nextComb(vector<int> &comb, int n) {
	int k = comb.size(), i = k - 1;
	++comb[i];
	while (i>=1 && comb[i]>=n-k+1+i) ++comb[--i];
	if (comb[0] > n-k) return false; 
	for (++i; i<k; ++i) comb[i] = comb[i-1] + 1;
	return true;
}

float TSP(const vector<vector<float>> &dists) {
	int N = dists.size(), M = pow(2.0, N-1);
	float **mem = new float *[M];
	for (int i=0; i<M; ++i) mem[i] = new float[N-1];
	for (int i=1; i<N; ++i) mem[0][i-1] = dists[0][i];
	for (int m=1; m<N-1; ++m) {
		vector<int> comb(m);
		for (int i=0; i<m; ++i) comb[i] = i;
		do {
			bitset<B> c = getComb(comb);
			int i = c.to_ulong();
			for (int j=1; j<N; ++j) {
				mem[i][j-1] = FLT_MAX;
				for (int k=0; k<c.size(); ++k) {
					if (c[k] == 1) {
						c[k] = 0;
						mem[i][j-1] = min(mem[i][j-1], mem[c.to_ulong()][k]+dists[k+1][j]);
						c[k] = 1;
					}
				}
			}
		} while (nextComb(comb, N-1));
	}
	float res = FLT_MAX;
	bitset<B> c;
	c.set();
	for (int i=1; i<N; ++i) {
		c[i-1] = 0;
		res = min(res, mem[c.to_ulong()][i-1]+dists[i][0]);
		c[i-1] = 1;
	}
	for (int i=0; i<M; ++i) delete[] mem[i];
	delete[] mem;
	return res;
}

int main() {
	ifstream fin("C:\\Users\\Administrator\\Desktop\\tsp.txt");
	int N;
	fin>>N;
	struct City {
		float x;
		float y;
	};
	vector<City> cities(N);
	float x, y;
	for (int i=0; i<N; ++i) {
		fin>>x>>y;
		cities[i].x = x;
		cities[i].y = y;
	}
	fin.close();
	vector<vector<float>> dists(N, vector<float>(N));
	for (int i=0; i<N; ++i) {
		for (int j=0; j<N; ++j) {
			x = (cities[i].x-cities[j].x);
			y = (cities[i].y-cities[j].y);
			dists[i][j] = sqrt(x*x + y*y);
		}
	}
	cout<<(int)TSP(dists)<<endl;
	return 0;
}