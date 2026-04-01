#include <vector>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unordered_set>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;

class Solution {
public:
	vector<int> partitionLabels(string s) {
		vector<int> vec(26, 0);
		vector<int> result = {};
		int len = s.size();
		for (int i = 0; i < len; i++) {
			vec[s[i] - 'a'] = i;
		}
		int i = 0; 
		int j = vec[s[0] - 'a'];
		unordered_set<int> us;
		while (i < len) {
			int k = i;
			while (i < j) {
				i++;
				j = max(j, vec[s[i] - 'a']);
			}
			result.push_back(j - k + 1);
			i++;
			if (i >= len) {
				break;
			}
			j = vec[s[i] - 'a'];
		}
		
		return result;
	}
};

int main() {
	string s = "ababcbacadefegdehijhklij";
	Solution x;
	auto print_vec = [](vector<int> & vec) {
		for (const int & x : vec) {
			cout << x << " ";
		}
		cout << endl;
	};
	auto v = x.partitionLabels(s);
	print_vec(v);
}
