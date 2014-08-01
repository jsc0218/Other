// DP for Traveling Salesman Problem, time complexity O((2^n)(n^2)), space complexity O((n(C(n/2,n))

#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <unordered_map>
#include <cmath>
#include <cfloat>
#include <ctime>
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
	int N = dists.size();
	long long n = 1, d = 1;
	for (int i=2; i<=(N-1)/2; ++i) d *= i;
	for (int i=(N-1)-(N-1)/2+1; i<=N-1; ++i) n *= i;
	int M = n / d;
	vector<vector<vector<float>>> mem(2, vector<vector<float>>(M, vector<float>(N-1)));
	unordered_map<bitset<B>, int> hash[2];
	bitset<B> c;
	hash[0][c] = 0;
	for (int i=1; i<N; ++i) mem[0][0][i-1] = dists[0][i];
	for (int m=1; m<N-1; ++m) {
		vector<int> comb(m);
		for (int i=0; i<m; ++i) comb[i] = i;
		int i = 0;
		do {
			c = getComb(comb);
			hash[m%2][c] = i;
			for (int j=1; j<N; ++j) {
				mem[m%2][i][j-1] = FLT_MAX;
				for (int k=0; k<c.size(); ++k) {
					if (c[k] == 1) {
						c[k] = 0;
						mem[m%2][i][j-1] = min(mem[m%2][i][j-1], mem[(m-1)%2][hash[(m-1)%2][c]][k]+dists[k+1][j]);
						c[k] = 1;
					}
				}
			}
			++i;
		} while (nextComb(comb, N-1));
		hash[(m-1)%2].clear();
	}
	float res = FLT_MAX;
	c.set();
	for (int i=1; i<N; ++i) {
		c[i-1] = 0;
		res = min(res, mem[(N-2)%2][hash[(N-2)%2][c]][i-1]+dists[i][0]);
		c[i-1] = 1;
	}
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
	clock_t start = clock();
	cout<<(int)TSP(dists)<<endl;
	clock_t end = clock();
	return 0;
}