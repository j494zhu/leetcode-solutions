class Solution {
public:
	bool wordPattern(string pattern, string s) {
		auto hashfunc = [](string str) -> uint64_t {
			uint64_t h = 1469598103934665603ULL;
			for (const char ch : str) {
				h ^= ch;
				h *= 1099511628211ULL;
			}
			return h;
		};
		vector<uint64_t> vec = {};
		const int lens = s.size();
		string word = "";
		for (int i = 0; i < lens; i++) {
			if (s[i] == ' ') {
				vec.emplace_back(hashfunc(word));
				word = "";
			} else {
				word += s[i];
				if (i == lens - 1) {
					vec.emplace_back(hashfunc(word));
				}
			}
		}
		const int lenp = pattern.size();
		if (lenp != vec.size()) return false;
		unordered_map<int, uint64_t> mp;
		for (int i = 0; i < lenp; i++) {
			if (mp.find(pattern[i]) == mp.end()) {
				mp[pattern[i]] = vec[i];
			} else if (mp[pattern[i]] == vec[i]) {
				continue;
			} else {
				return false;
			}
		}
		
		unordered_set<uint64_t> us;
		for (const auto & [key, value] : mp) {
			us.insert(value);
		}
		
		return us.size() == mp.size();
	}
};