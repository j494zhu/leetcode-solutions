#include <stack>
using namespace std;

class MinStack {
private:
	stack<int> st;
	stack<int> minst;
	
public:
	MinStack() {}
	
	void push(int val) {
		st.push(val);
		if (minst.size() == 0 || val <= minst.top()) {
			minst.push(val);
		}
	}
	
	void pop() {
		int x = st.top();
		st.pop();
		if (minst.size() > 0 && x == minst.top()) {
			minst.pop();
		}
	}
	
	int top() {
		return st.top();
	}
	
	int getMin() {
		return minst.top();
	}
};
