#include <string>
#include <iostream>
#include <stack>
using namespace std;
class Solution {
public:
	string decodeString(string s) {
		stack<pair<string, int>> st;
		string cur;
		int k = 0;
		
		auto is_digit = [](char ch) -> bool {
			return '0' <= ch && ch <= '9';
		};
		
		for (char c : s) {
			if (is_digit(c)) {
				k = 10 * k + (c - '0');
			} else if (c == '[') {
				st.push({move(cur), k});
				cur.clear();
				k = 0;
			} else if (c == ']') {
				auto [prev, rep] = st.top();
				st.pop();
				prev.reserve(prev.size() + rep * cur.size());
				while (rep --) prev += cur;
				cur = move(prev);
			} else {
				cur += c;
			}
		}
		return cur;
	}
};
