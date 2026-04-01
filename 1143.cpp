#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
	int longestCommonSubsequence(string text1, string text2) {
		int len1 = text1.size();
		int len2 = text2.size();
		
		vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));

		for (int i = 1; i <= len1; i++) {
			for (int j = 1; j <= len2; j++) {
				int extend = (text1[i - 1] == text2[j - 1]) ? 1 : 0;
				dp[i][j] = max({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1] + extend});
			}
		}
		
		return dp[len1][len2];
	}
};
