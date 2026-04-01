#include <vector>
#include <stdio.h>
#include <iostream>
#include <stdio.h>
using namespace std;

class Solution {
public:
	int lengthOfLIS(vector<int>& nums) {
		int len = nums.size();
		if (len == 0) {
			return 0;
		}
		vector<int> dp(len);
		dp[len - 1] = 1;
		vector<pair<int, int>> lst = {{nums[len - 1], 1}};
		
		int result = 1;
		for (int i = len - 2; i >= 0; i--) {
			int best = 0;
			for (const pair<int, int> & p : lst) {
				if (p.first > nums[i]) {
					best = max(best, p.second);
				}
			}
			best++;
			result = max(result, best);
			lst.push_back({nums[i], best});
		}
		return result;
	}
};

int main() {
	
}
