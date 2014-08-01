// DP for Traveling Salesman Problem, time complexity O((2^n)(n^2)), space complexity O((n(C(n/2,n))

#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <cmath>
#include <cfloat>
using namespace std;

const int B = 24;

int combination(int k, int n) {
	if (n < k) return 0;
	if (n == k) return 1;
	k = max(k, n-k);
	long long p = 1, q = 1;
	for (int i=k+1; i<=n; ++i)  p *= i;
	for (int i=1; i<=n-k; ++i) q *= i;
	return p / q;
}

int toIdx(bitset<B> b, int k) {
	int idx = 0;
	for (int i=0, j=1; i<b.size() && j<=k; ++i) {
		if (b[i] == 1) idx += combination(j++, i);
	}
	return idx;
}

bool next_combination(unsigned long& x) // assume x has form x'01^a10^b in binary
{
	unsigned long u = x & -x; // extract rightmost bit 1; u =  0'00^a10^b
	unsigned long v = u + x; // set last non-trailing bit 0, and clear to the right; v=x'10^a00^b
	if (v==0) // then overflow in v, or x==0
		return false; // signal that next k-combination cannot be represented
	x = v +(((v^x)/u)>>2); // v^x = 0'11^a10^b, (v^x)/u = 0'0^b1^{a+2}, and x ¡û x'100^b1^a
	return true; // successful completion
}

bool nextComb(bitset<B> &b) {
	unsigned long x = b.to_ulong();
	if (!next_combination(x)) return false;
	if (x >= (1<<b.size())) return false;
	b = x;
	return true;
}

float TSP(const vector<vector<float>> &dists) {
	int N = dists.size();
	long long n = 1, d = 1;
	for (int i=2; i<=(N-1)/2; ++i) d *= i;
	for (int i=(N-1)-(N-1)/2+1; i<=N-1; ++i) n *= i;
	int M = n / d;
	vector<vector<vector<float>>> mem(2, vector<vector<float>>(M, vector<float>(N-1)));
	bitset<B> c;
	for (int i=1; i<N; ++i) mem[0][0][i-1] = dists[0][i];
	for (int m=1; m<N-1; ++m) {
		bitset<B> c;
		for (int i=0; i<m; ++i) c[i] = 1;
		int i = 0;
		do {
			for (int j=1; j<N; ++j) {
				mem[m%2][i][j-1] = FLT_MAX;
				for (int k=0; k<c.size(); ++k) {
					if (c[k] == 1) {
						c[k] = 0;
						mem[m%2][i][j-1] = min(mem[m%2][i][j-1], mem[(m-1)%2][toIdx(c,m)][k]+dists[k+1][j]);
						c[k] = 1;
					}
				}
			}
			++i;
		} while (nextComb(c));
	}
	float res = FLT_MAX;
	c.set();
	for (int i=1; i<N; ++i) {
		c[i-1] = 0;
		res = min(res, mem[(N-2)%2][toIdx(c,N-1)][i-1]+dists[i][0]);
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
	cout<<(int)TSP(dists)<<endl;
	return 0;
}