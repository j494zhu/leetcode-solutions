#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

class Solution {
private:
	vector<vector<int>> result;
	vector<pair<int, int>> count;
	int size = 1;
public:
	vector<vector<int>> subsets(vector<int>& nums) {
		result = {};
		count = {};
		sort(nums.begin(), nums.end());
		for (int x : nums) {
			if (count.size() == 0 || x != count[count.size() -1].first) {
				count.push_back(make_pair(x, 1));
			} else {
				count[count.size() - 1].second++;
			}
		}
		size = 1;
		for (pair<int, int> p : count) {
			size *= (p.second + 1);
		}
		result.resize(size);
		
		int k = size;
		for (const pair<int, int> & p : count) {
			int num = p.first;
			int cnt = p.second;
			int cycle = k / (cnt + 1);
			int id = 0;
			
			for (int patch = 0; patch < (size / k); patch++) {
				for (int i = 0; i <= cnt; i++) {
					for (int j = 0; j < cycle; j++) {
						for (int rep = 0; rep < i; rep++) {
							result[id].push_back(num);
						}
						id++;
					}
				}
			}
			
			
			k /= (cnt + 1);
		}
		
		return result;
	}
};

int main(void) {
	auto print_vv = [](const vector<vector<int>> &vvec) {
		for (const auto & vec : vvec) {
			for (int x : vec) {
				cout << x << " ";
			}
			cout << endl;
		}
	};
	vector<int> vec = {1, 2, 3};
	Solution x;
	vector<vector<int>> result = x.subsets(vec);
	print_vv(result);

}
