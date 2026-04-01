#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;
class Solution {
public:
	bool canPartition(vector<int>& nums) {
		int sum = 0;
		for (const int & x : nums) sum += x;
		if ((sum & 1) == 1) return false;
		
		int size = sum / 2;
		vector<int> dp(size + 1);
		dp[0] = 1;
		
		for (const int & x : nums) {
			for (int i = size; i >= 0; i--) {
				if (i - x >= 0 && dp[i - x] == 1) {
					dp[i] = 1;
				}
			}
		}
		
		return dp[size];
	}
};

int main(void) {
	vector<int> vec = {1, 2, 5};
	Solution x;
	cout << x.canPartition(vec) << endl;
}

