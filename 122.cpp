#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

class Solution {
public:
	int maxProfit(vector<int>& prices) {
		int len = prices.size();
		if (len <= 1) {
			return 0;
		}
		int trades = 0;
		int hold_price = 0;
		int cur_profit = 0;
		bool has_stock = false;
		prices.push_back(prices[prices.size() - 1]);
		for (int i = 0; i < len; i++) {
			if (!has_stock && prices[i] < prices[i + 1]) {
				trades++;
				hold_price = prices[i];
				cur_profit -= prices[i];
				has_stock = true;
				continue;
			} else if (!has_stock) {
				continue;
			}
			
			if (prices[i] >= hold_price) {
				trades++;
				hold_price = 0;
				cur_profit += prices[i];
				has_stock = false;
			}
			if (!has_stock && prices[i] < prices[i + 1]) {
				trades++;
				hold_price = prices[i];
				cur_profit -= prices[i];
				has_stock = true;
				continue;
			}
		}
		return cur_profit;
	}
};

int main () {
	Solution x;
	vector<int> vec = {1, 2, 3, 4, 5};
	cout << x.maxProfit(vec) << endl;
}
