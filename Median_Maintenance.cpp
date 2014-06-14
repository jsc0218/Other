// Median Maintenance, time complexity O(nlog(n)), space complexity O(n)

#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

int main() {
	int N = 10000, res = 0;
	priority_queue<int> maxHeap;
	priority_queue<int, vector<int>, greater<int>> minHeap;
	ifstream fin("C:\\Users\\Administrator\\Desktop\\Median.txt");
	for (int i=0, x; i<N; ++i) {
		fin >> x;
		if (!minHeap.empty() && x>=minHeap.top()) minHeap.push(x);
		else maxHeap.push(x);
		if (maxHeap.size() == minHeap.size()+2) {
			minHeap.push(maxHeap.top());
			maxHeap.pop();
		} else if (minHeap.size() == maxHeap.size()+1) {
			maxHeap.push(minHeap.top());
			minHeap.pop();
		}
		res += maxHeap.top();
	}
	fin.close();
	cout << res % N;
	return 0;
}