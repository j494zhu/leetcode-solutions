#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
	int largestRectangleArea(vector<int>& heights) {
		heights.emplace_back(0);
		int n = heights.size();
		// calculate maximum area on the right
		vector<int> right(n);
		vector<pair<int, int>> st;
		for (int i = 0; i < n; i++) {
			while (!st.empty() && st[st.size() - 1].second > heights[i]) {
				auto [index, h] = st[st.size() - 1];
				st.pop_back();
				right[index] = i - 1;
			}
			if (i == n - 1) {
				right[i] = n - 1;
			} else {
				st.emplace_back(make_pair(i, heights[i]));
			}
		}
		
		// calculate maximum area on the left
		vector<int> left(n);
		st.resize(0);
		for (int i = n - 1; i >= 0; i--) {
			while (!st.empty() && st[st.size() - 1].second > heights[i]) {
				auto [index, h] = st[st.size() - 1];
				st.pop_back();
				left[index] = i + 1;
			}
			if (i == 0) {
				left[i] = 0;
			} else {
				st.emplace_back(make_pair(i, heights[i]));
			}
		}
		
		int max_area = 0;
		for (int i = 0; i < n; i++) {
			int l = left[i];
			int r = right[i];
			cout << heights[i] << " " << l << " " << r << endl;
			max_area = max(max_area, (r - l + 1) * heights[i]);
		}
		return max_area;
	}
};

int main() {
	vector<int> vec = {2, 3, 0};
	Solution x;
	cout << x.largestRectangleArea(vec) << endl;
}
