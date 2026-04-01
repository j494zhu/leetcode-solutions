#include <unordered_map>
using namespace std;

class LFUCache {
private:
	struct Node {
		int key;
		int val;
		int freq;
		Node* left;
		Node* right;
		Node(int key) : key(key), val(0), freq(0), left(nullptr), right(nullptr) {}
	};
	struct Bucket{
		int freq;
		Bucket* left;
		Bucket* right;
		Node* start;
		Node* stop;
		Bucket(int freq) : freq(freq), left(nullptr), right(nullptr), start(nullptr), stop(nullptr){}
	};
	Bucket* bkt_0;
	Bucket* bkt_n;
	Node* node_0;
	Node* node_n;
	unordered_map<int, Node*> mp;
	unordered_map<int, Bucket*> bktmp;
	int max_cap;
	int count;
	
	void insert_bucket(Bucket* b1, Bucket* new_bucket) {
		// will insert a new bucket to the right of the given bucket
		Bucket* b2 = b1->right;
		b1->right = new_bucket;
		new_bucket->left = b1;
		new_bucket->right = b2;
		b2->left = new_bucket;
	}
	
	void reconnect_bucket(Bucket* bucket) {
		Bucket* b1 = bucket->left;
		Bucket* b2 = bucket->right;
		b1->right = b2;
		b2->left = b1;
	}
	
	void reconnect_node(Node* node) {
		int f0 = node->freq;
		Bucket* b = bktmp[f0];
		if (b->start == b->stop) {
			reconnect_bucket(b);
			delete b;
			bktmp.erase(f0);
		} else if (b->start == node) {
			b->start = node->right;
		} else if (b->stop == node) {
			b->stop = node->left;
		}
		
		Node* n1 = node->left;
		Node* n2 = node->right;
		n1->right = n2;
		n2->left = n1;
		// check if we need to reconnect bucket
	}
	
	void pop_node() {
		Bucket* b1 = bkt_0->right;
		Node* node = b1->start;
		reconnect_node(node);
		// int f0 = node->freq;
		// ERRORL: mp.erase(f0); ; mp key is int key, not freq
		mp.erase(node->key);
		delete node;
	}
	
	// inserts a new node after a given node, node pointers adjusted; bucket pointers are not changed. 
	void insert_node(Node* n1, Node* node) {
		Node* n2 = n1->right;
		n1->right = node;
		node->left = n1;
		node->right = n2;
		n2->left = node;
	}
	
	// move a node from its current location to the end of next bucket
	// fixed node connections
	// fixed bucket connections 
	void move_node(Node* node) {
		int f0 = node->freq;
		Bucket* b = bktmp[f0];
		// ERROR: Bucket* new_bkt = new Bucket(f0 + 1); // unsafe; define separately in if-else blocks
		if (bktmp.find(f0 + 1) == bktmp.end()) {
			Bucket* new_bkt = new Bucket(f0 + 1);
			insert_bucket(b, new_bkt);
			bktmp[f0 + 1] = new_bkt;
			reconnect_node(node); // fix node connections in the previous location
			new_bkt->start = node; // set up range for the new bucket
			new_bkt->stop = node; // bucket connections not completed yet
			insert_node(new_bkt->right->start->left, node); // make sure bucket is not freed yet
		} else {
			reconnect_node(node); 
			Bucket* new_bkt = bktmp[f0 + 1]; // locate to the desired bucket
			insert_node(new_bkt->right->start->left, node); 
			new_bkt->stop = node; // update bucket range
		}
		node->freq++; // update node frequency
	}
	
	void insert_at_start(Node* node) {
		insert_node(bkt_0->stop, node);
		bkt_0->stop = node;
	}
	
public:
	LFUCache(int capacity) {
		bkt_0 = new Bucket(0);
		bkt_n = new Bucket(0);
		node_0 = new Node(0);
		node_n = new Node(0);
		node_0->right = node_n;
		node_n->left = node_0;
		bkt_0->right = bkt_n;
		bkt_n->left = bkt_0;
		bkt_0->start = node_0;
		bkt_0->stop = node_0;
		bkt_n->start = node_n;
		bkt_n->stop = node_n;
		max_cap = capacity;
		count = 0;
		
		// ERROR: bkt_0, bkt_n not initialized in bktmp
		bktmp[0] = bkt_0;
		bktmp[1e9] = bkt_n;
	}
	
	int get(int key) {
		if (mp.find(key) == mp.end()) {
			return -1;
		}
		move_node(mp[key]);	
		return mp[key]->val;
	}
	
	void put(int key, int value) {
		// update cnt and check for max_cap
		if (mp.find(key) == mp.end()) { // insert new value
			count++;
			if (count > max_cap) { // ERROR: this should only happen for new key
				pop_node(); // update mp and bktmp when popping
				count--;
			}
			Node* new_node = new Node(key);
			// new_node freq will default to 0
			// will utilize move_node function property to update freq to 1
			insert_at_start(new_node);
			move_node(new_node);
			mp[key] = new_node;
		} else { // update existing value, update map in both cases; 
			Node* node = mp[key];
			move_node(node);
		}
		// ERROR: value not updated
		mp[key]->val = value;
	}

	~LFUCache() {
		Node* node = node_0;
		while (node) {
			Node* next_node = node->right;
			delete node;
			node = next_node;
		}
		Bucket* b = bkt_0;
		while (b) {
			Bucket* next_b = b->right;
			delete b;
			b = next_b;
		}
	}
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main() {}

// 时隔一天就完成了指针版本的lfu
