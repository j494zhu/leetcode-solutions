#include <vector>
#include <string>
#include <unordered_map>
#include <set>

class KVStore {
public:
	virtual void set(std::string key, std::string value, int timestamp) = 0;
	virtual std::string get(std::string key, int timestamp) = 0;
	virtual std::string name() = 0;
	virtual ~KVStore() = default;
};

class LatestStore : public KVStore {
private:
	std::unordered_map<std::string, std::set<std::pair<int, std::string>>> data;

public:
	void set(std::string key, std::string value, int timestamp) override {
		data[key].insert(std::make_pair(timestamp, value));
	}
	
	std::string get(std::string key, int timestamp) override {
		if (data.find(key) == data.end()) {
			return ""; // key does not exist
		}
		auto it = data[key].end();
		auto last = prev(it);
		return (*last).second; // always returns the last
	}
	
	std::string name(void) override {
		return "LatestStore";
	}
};

class TimeStore : public KVStore{
private:
	std::unordered_map<std::string, std::set<std::pair<int, std::string>>> data;

protected:
	std::pair<std::string, int> get_with_timestamp(std::string key, int timestamp) {
		if (data.find(key) == data.end()) {
			return std::make_pair("", -1); // not found
		}
		std::pair<int, std::string> datum = std::make_pair(timestamp, "");
		auto it = data[key].lower_bound(datum);
		if (it != data[key].end() && (*it).first == timestamp) {
			return std::make_pair((*it).second, timestamp); // return value stored at the exact timestamp
		}
		if (it != data[key].begin()) {
			auto left = std::prev(it);
			return std::make_pair((*left).second, (*left).first); // return the value at the closest but earlier timestamp
		}
		return std::make_pair("", -1); // there is no earlier timestamp
	}
	
public:
	void set(std::string key, std::string value, int timestamp) override {
		data[key].insert(std::make_pair(timestamp, value));
	}
	
	std::string get(std::string key, int timestamp) override {
		auto [value, exact_time] = get_with_timestamp(key, timestamp);
		return value;
	}
	
	std::string name(void) override {
		return "TimeStore";
	}
};

class ExpiringStore : public TimeStore {
private:
	int ttl = 0;
	
public:
	ExpiringStore(int ttl) : ttl(ttl) {}
	
	void set(std::string key, std::string value, int timestamp) override {
		TimeStore::set(key, value, timestamp);
	}
	
	std::string get(std::string key, int timestamp) override {
		auto [value, exact_time] = TimeStore::get_with_timestamp(key, timestamp);
		if (value == "" || timestamp - exact_time > ttl) {
			return "";
		}
		return value;
	}
};

class StoreRouter {
private:
	struct TrieNode {
		std::unordered_map<char, TrieNode*> children;
		KVStore* store = nullptr;
		bool is_end = false;
	};
	TrieNode* root = nullptr;
	
	KVStore* get_type(std::string key) {
		TrieNode* node = root;
		KVStore* prefix = nullptr;
		for (char ch : key) {
			if (node->children.find(ch) == node->children.end()) {
				break;
			}
			node = node->children[ch];
			if (node->is_end) {
				prefix = node->store;
			}
		}
		return prefix;
	}
	
public:
	StoreRouter() {
		root = new TrieNode();
	}
	
	void addRoute(std::string prefix, KVStore* store) {
		TrieNode* node = root;
		
		for (char c : prefix) {
			if (node->children.find(c) == node->children.end()) {
				node->children[c] = new TrieNode();
			}
			node = node->children[c];
		}
		node->is_end = true;
		node->store = store;
	}
	
	std::string get(std::string key, int timestamp) {
		KVStore* store_type = get_type(key);
		if (!store_type) return "";
		return store_type->get(key, timestamp);
	}
	
	void set(std::string key, std::string value, int timestamp) {
		KVStore* store_type = get_type(key);
		if (!store_type) return;
		store_type->set(key, value, timestamp);
	}	
};
