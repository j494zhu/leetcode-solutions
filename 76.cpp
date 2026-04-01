#include <string>
#include <unordered_map>
#include <iostream>
using namespace std;

class Solution {
public:
	string minWindow(string s, string t) {
		unordered_map<char, int> mp;
		for (auto & ch : t) {
			mp[ch]--;
		}
		int cnt = mp.size();
		int geq = 0;
		pair<int, int> pos = {-1, -1};
		
		int i = 0; 
		int j = 0;
		while (i < s.size()) {
			while (geq < cnt && j < s.size()) {
				if (mp.find(s[j]) != mp.end()) {
					if (mp[s[j]] == -1) {
						geq++;
					}
					mp[s[j]]++;
				}
				j++;
			}
			if (geq < cnt) {
				break;
			}
			if ((pos.first == -1 && pos.second == -1) || (pos.second - pos.first) > (j - i)) {
				pos = {i, j};
			}
			if (mp.find(s[i]) != mp.end()) {
				if (mp[s[i]] == 0) {
					geq--;
				}
				mp[s[i]]--;
			} 
			i++;
		}
		if (pos.first == -1 && pos.second == -1) {
			return "";
		} else {
			return s.substr(pos.first, pos.second - pos.first);
		}
	}
};

int main() {
	string s1;
	string s2;
	Solution x;
	cin >> s1 >> s2;
	cout << x.minWindow(s1, s2) << endl;
}
