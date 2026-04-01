#include <vector>
#include <map>
#include <iostream>
using namespace std;

class Solution {
private:
	map<int, int> mp;
public:
	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		int n = nums.size();
		vector<int> result;
		result.reserve(n);
		for (int i = 0; i < k; i++) {
			mp[nums[i]]++;
		}
		result.push_back((*--mp.end()).first);
		for (int i = k; i < n; i++) {
			mp[nums[i]]++;
			mp[nums[i - k]]--;
			if (mp[nums[i - k]] == 0) {
				mp.erase(nums[i - k]);
			}
			result.push_back((*--mp.end()).first);
		}
		return result;
	}
};

int main() {
	vector<int> vec = {1,3,-1,-3,5,3,6,7};
	Solution x;
	auto print = [](vector<int> & vec) {
		for (int x : vec) cout << x << endl;
	};
	vector<int> result = x.maxSlidingWindow(vec, 3);
	print(result);
}
