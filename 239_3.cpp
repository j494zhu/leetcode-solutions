#include <vector>
#include <stack>
using namespace std;

class Solution {
private:
	struct maxStack {
		stack<int> st;
		stack<int> maxst; 
		
		void push(int x) {
			st.push(x);
			if (maxst.empty() || x > maxst.top()) {
				maxst.push(x);
			} else {
				maxst.push(maxst.top());
			}
		}
		
		void pop(void) {
			if (st.empty()) return;
			st.pop();
			maxst.pop(); 
		}
		
		int get_max(void) {
			return maxst.empty() ? -1e9 : maxst.top();
		}
		
		int get_size(void) {
			return st.size();
		}
		
		int get_top(void) {
			return st.empty() ? -1e9 : st.top();
		}
	};
	
	struct maxQueue{
		maxStack stkin, stkout;
		void push(int x) {
			stkin.push(x);
		}
		void pop(void) {
			if (stkin.get_size() == 0 && stkout.get_size() == 0) return;
			if (stkout.get_size() == 0) {
				while (stkin.get_size() > 0) {
					int x = stkin.get_top();
					stkin.pop();
					stkout.push(x);
				}
			}
			stkout.pop();
		}
		int get_max(void) {
			return max(stkin.get_max(), stkout.get_max());
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

int main() {
	
}
