#include <vector>
#include <iostream>
class Solution {
public:
	int findDuplicate2(std::vector<int>& nums) {
		int slow = nums[0];
		int fast = nums[nums[0]];
		while (slow != fast) {
			slow = nums[slow];
			fast = nums[nums[fast]];
		}
		slow = 0;
		while (slow != fast) {
			slow = nums[slow];
			fast = nums[fast];
		}
		return slow;
	}
	void recover(std::vector<int> & nums) {
		for (int & x : nums) {
			x = abs(x);
		}
	}
	int findDuplicate(std::vector<int> & nums) {
		int start= 0;
		while (1) {
			if (nums[start] < 0) {
				recover(nums);
				return start;
			}
			nums[start] = -nums[start];
			start = -nums[start];
		}
	}
	
	int local_hash(std::vector<int> nums) {
		int n= nums.size() - 1;
		for (int i = 1; i <= n; i++) {
			while (nums[i] != i) {
				if (nums[nums[i]] == nums[i]) return nums[i];
				std::swap(nums[i], nums[nums[i]]);
			}
		}
		return nums[0];
	}
};

int main() {
	std::vector<int> vec = {1, 3, 4, 2, 2};
	Solution x;
	std::cout << x.findDuplicate(vec) << std::endl;
	std::cout << x.local_hash(vec) << std::endl;
}
