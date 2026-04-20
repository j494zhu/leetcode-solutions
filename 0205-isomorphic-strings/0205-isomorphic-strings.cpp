class Solution {
public:
	bool isIsomorphic(string s, string t) {
		int len1 = s.size();
		int len2 = t.size();
		if (len1 != len2) return false;
		unordered_map<int, int> mp;
		
		for (int i = 0; i < len1; i++) {
			if (mp.find(s[i]) == mp.end()) {
				mp[s[i]] = t[i];
			} else if (mp[s[i]] == t[i]) {
				continue;
			} else {
				return false;
			}
		}
		unordered_set<int> mapping;
		for (const auto & [key, value] : mp) {
			mapping.insert(value);
		}
		
		return mp.size() == mapping.size();
	}
};