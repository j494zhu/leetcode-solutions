#include <vector>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

class Solution {
public:
	int coinChange(vector<int>& coins, int amount) {
		const int dne = 1e9;
		vector<int> dp(amount + 1, dne);
		dp[0] = 0;
		
		for (int i = 1; i <= amount; i++) {
			for (const int & x : coins) {
				if (i - x >= 0) {
					dp[i] = min(dp[i], dp[i - x] + 1);
				}
			}
		}
		
		return (dp[amount] == dne) ? -1 : dp[amount];
	}
};

int main() {
	
}
