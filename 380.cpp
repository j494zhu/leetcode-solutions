#include <ctime>
#include <cstdlib>
#include <vector>
#include <unordered_map>
using namespace std;

class RandomizedSet {
private:
	vector<int> vec;
	unordered_map<int, int> mp;
public:
	RandomizedSet() {
		srand(time(0));
	}
	
	bool insert(int val) {
		if (mp.find(val) != mp.end()) {
			return false;
		}
		vec.push_back(val);
		mp[val] = vec.size() - 1;
		return true;
	}
	
	bool remove(int val) {
		if (mp.find(val) == mp.end()) {
			return false;
		} 
		int index = mp[val];
		if (index == vec.size() - 1) {
			vec.pop_back();
		} else {
			vec[index] = vec[vec.size() - 1];
			vec.pop_back();
			mp[vec[index]] = index;
		}
		mp.erase(val);
		return true;
	}
	
	int getRandom() {
		int index = rand() % vec.size();
		return vec[index];
	}
};

int main() {}
