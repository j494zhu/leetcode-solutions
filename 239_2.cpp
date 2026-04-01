#include <vector>
#include <queue>
#include <deque>
using namespace std;

class Solution {
private:
	struct maxQueue{
		queue<pair<int, int>> q;
		deque<pair<int, int>> maxdq;
		int index;
		maxQueue() : index(0) {}
		void push(int x) {
			q.push(make_pair(x, index));
			if (maxdq.empty()) {
				maxdq.push_back(make_pair(x, index));
			} else {
				while (!maxdq.empty() && maxdq.back().first <= x) {
					maxdq.pop_back();
				}
				maxdq.push_back(make_pair(x, index));
			}
			index++;
		}
		void pop() {
			auto [x, ord] = q.front();
			q.pop();
			while (!maxdq.empty() && maxdq.front().second <= ord) {
				maxdq.pop_front();
			}
		}
		int get_max() {
			return maxdq.empty() ? 1e9 : maxdq.front().first;
		}
	};
public:
	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		vector<int> result;
		int n = nums.size();
		if (n == 0 || n < k) {
			return result;
		}
		maxQueue mq;
		for (int i = 0; i < k; i++) {
			mq.push(nums[i]);
		}
		result.push_back(mq.get_max());
		for (int i = k; i < n; i++) {
			mq.push(nums[i]);
			mq.pop();
			result.push_back(mq.get_max());
		}
		return result;
	}
};
