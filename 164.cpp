#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

const int dne = 2e9;
class Solution {
private:
	int find_max(vector<int>& nums) {
		int len = nums.size();
		if (len == 0) {
			return dne;
		}
		int maxi = nums[0];
		for (int i = 1; i < len; i++) {
			maxi = max(maxi, nums[i]);
		}
		return maxi;
	}
	int find_min(vector<int>& nums) {
		int len = nums.size();
		if (len == 0) {
			return dne;
		}
		int mini = nums[0];
		for (int i = 1; i < len; i++) {
			mini = min(mini, nums[i]);
		}
		return mini;
	}
	
	
public:
	int maximumGap(vector<int>& nums) {
		int len = nums.size();
		if (len < 2) {
			return 0;
		}
		int maxi = find_max(nums);
		int mini = find_min(nums);
		if (maxi == mini) {
			return 0;
		}
		if (len == 2) {
			return maxi - mini;
		}
		int bucket_size = max(1, (maxi - mini) / (len - 1));
		int bucket_nums = len + 1;
		vector<vector<int>> buckets(bucket_nums);
		
		for (int i = 0; i < len; i++) {
			int bucket_id = (nums[i] - mini) / bucket_size;
			bucket_id = min(bucket_id, bucket_nums - 1);
			buckets[bucket_id].push_back(nums[i]);
		}
		
		vector<int> bucket_min(bucket_nums);
		vector<int> bucket_max(bucket_nums);
		
		for (int i = 0; i < bucket_nums; i++) {
			bucket_min[i] = find_min(buckets[i]);
			bucket_max[i] = find_max(buckets[i]);
		}
		int result = 0;
		vector<int> valid_index;
		for (int i = 0; i < bucket_nums; i++) {
			if (bucket_min[i] != dne) {
				valid_index.push_back(i);
			}
		}
		for (int i = 0; i < (int) valid_index.size() - 1; i++) {
			result = max(result, bucket_min[valid_index[i + 1]] - bucket_max[valid_index[i]]);
		}
		return result;
		return 0;
	}
};

int main(void) {
	Solution x;
	
	int n;
	cin >> n;
	vector<int> vec(n);
	for (int i = 0; i < n; i++) {
		cin >> vec[i];
	}
	cout << x.maximumGap(vec) << endl;
}
