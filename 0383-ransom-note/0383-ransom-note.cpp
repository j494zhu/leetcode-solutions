class Solution {
public:
	bool canConstruct(string ransomNote, string magazine) {
		unordered_map<int, int> map1;
		unordered_map<int, int> map2;
		const int len1 = ransomNote.size();
		const int len2 = magazine.size();
		for (int i = 0; i < len1; i++) {
			map1[ransomNote[i]]++;
		}
		for (int i = 0; i < len2; i++) {
			map2[magazine[i]]++;
		}
		for (const auto & [key, value] : map1) {
			if (map2[key] < value) {
				return false;
			}
		}
		return true;
	}
};