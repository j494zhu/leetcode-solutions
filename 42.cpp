#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
	int trap(vector<int>& height) {
		int n = height.size();
		int start = 0;
		int stop = n - 1;
		int result = 0;
		for (; start < n - 1; start++) {
			if (height[start + 1] >= height[start]) {
				continue;
			} else break;
		}
		for (; stop >= 1; stop--) {
			if (height[stop - 1] >= height[stop]) {
				continue;
			} else break;
		}
		if (start >= stop) return 0;
		vector<bool> is_tallest(n);
		is_tallest[stop] = true;
		int h = height[stop];
		for (int i = stop - 1; i >= start; i--) {
			if (height[i] > h) {
				is_tallest[i] = true;
				h = height[i];
			}
		}
		int i = start;
		while (i < stop) {
			if (height[i] <= height[i + 1]) {
				i++;
				continue;
			}
			int j = i + 1;
			int ans = 0;
			while (j <= stop) {
				if (height[j] >= height[i] || is_tallest[j]) {
					break;
				}
				ans += height[j];
				j++;
			}
			result += (j - i - 1) * min(height[i], height[j]) - ans;
			i = j;
			// increment
		}
		return result;
	}
};

int main() {
	vector<int> vec = {4, 2, 0, 3, 2, 5};
	Solution x;
	cout << x.trap(vec) << endl;
}
