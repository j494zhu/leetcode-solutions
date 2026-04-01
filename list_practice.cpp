#include <stack>
#include <iostream>
using namespace std;

struct maxStack{
	stack<int> st;
	stack<pair<int, int>> maxst; // number, occurrence
	void push(int x) {
		st.push(x);
		if (maxst.empty() || x > maxst.top().first) maxst.push(make_pair(x, 1));
		else if (x == maxst.top().first) ++maxst.top().second;
	}
	void pop(void) {
		if (st.empty() || maxst.empty()) return;
		int x = st.top();
		st.pop();
		if (maxst.top().first == x && maxst.top().second == 1) maxst.pop();
		else --maxst.top().second;
	}
	int get_max(void) {
		return maxst.empty() ? -1e9 : maxst.top().first;
	}
};

int main() {
	maxStack x;
	x.push(1);
	x.push(2);
	x.push(1);
	auto print = [](int x) {cout << x << endl;};
	print(x.get_max());
}
