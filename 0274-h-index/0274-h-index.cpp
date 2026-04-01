#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
	int hIndex(vector<int>& citations) {
		// aim for O(N)
		int n = citations.size();
		vector<int> cnt(n + 1);
		for (const int x : citations) {
			if (x >= n) cnt[n]++;
			else cnt[x]++;
		}
		int ans = 0;
		for (int i = n; i >= 0; i--) {
			ans += cnt[i];
			if (ans >= i) return i;
		}
		return 0;
	}
};