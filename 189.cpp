#include <vector>
#include <iostream>
class Solution {
public:
	void rotate(std::vector<int>& nums, int k) {
		auto rotate = [&nums](int i, int j) {
			while (i < j) {
				std::swap(nums[i], nums[j]);
				i++;
				j--;
			}
		};
		int len = nums.size();
		if (len <= 1) return;
		k %= len;
		if (k == 0) return;
		rotate(0, len - 1);
		rotate(0, k - 1);
		rotate(k, len - 1);
		
	}
};

int main() {
	std::vector<int> vec = {1, 2, 3, 4, 5};
	Solution x;
	x.rotate(vec, 3);
	for (int & x : vec) {
		std::cout << x << " ";
	}
}
