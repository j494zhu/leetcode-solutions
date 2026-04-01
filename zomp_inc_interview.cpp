#include <iostream>
#include <string>
#include <unordered_map>
#include <set>
using namespace std;

struct TimeMap{
private: 
	unordered_map<string, set<pair<int, string>>> data;
public:
	void set_new(string key, string value, int timestamp) {
		data[key].insert(make_pair(timestamp, value));
	}
	
	string get(string key, int timestamp) {
		auto it = data[key].lower_bound({timestamp, ""});

		if (it != data[key].end() && (*it).first == timestamp) {
			return (*it).second;
		}
		if (it == data[key].begin()) {
			return "Not Found";
		}
		auto it2 = prev(it);
		return (*it2).second;
	}
	
}; 

int main() {
	TimeMap x;
	x.set_new("foo", "bar", 1);
	cout << x.get("foo", 1) << endl;
	cout << x.get("foo", 3) << endl;
	x.set_new("foo", "bar2", 4);
	cout << x.get("foo", 4) << endl;
	cout << x.get("foo", 5) << endl;
	
	return 0;
}
