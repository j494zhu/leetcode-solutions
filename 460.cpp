#include <unordered_map>
using namespace std;

/*


RIP: unable to get through the pointers. 2026-3-18
// will solve the problems using pointers in the future. 


*/




class LFUCache {
private:
	// linked list sorted from least recent to most recent
	// each part is sorted from least frequently used to
	// most frequently used
	
	// each bucket: sorted based on frequency
	// buckets are nodes in a linked list
	// inside each bucket:
	// sorted from least to most recently used
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
		Bucket() : freq(0), left(nullptr), right(nullptr), start(nullptr), stop(nullptr){}
	};
	Bucket* bkt_root;
	Bucket* bkt_rootn;
	Node* root;
	Node* rootn;
	int max_cap;
	unordered_map<int, Node*> mp; // key, node
	unordered_map<int, Bucket*> bkt; // freq, bucket
	
	void reconnect_bucket(Bucket* b_i) { // bucket not deleted in bkt yet
		Bucket* left_bkt = b_i->left;
		Bucket* right_bkt = b_i->right;
		left_bkt->right = right_bkt;
		right_bkt->left = left_bkt;
	}
	
	void reconnect_node(Node* node) { // node not deleted in mp yet
		int f0 = node->freq;
		Bucket* bi = bkt[f0];
		if (bi->start == bi->stop) {
			reconnect_bucket(bi);
			delete bi;
		} else if (bi->start == node) {
			bi->start = node->right;
		} else if (bi->stop == node) {
			bi->stop = node->left;
		}
		Node* left_node = node->left;
		Node* right_node = node->right;
		left_node->right = right_node;
		right_node->left = left_node;
	}
	
	void insert_bucket(Bucket* left_bkt, Bucket* right_bkt, Bucket* b) {
		left_bkt->right = b;
		b->left = left_bkt;
		b->right = right_bkt;
		right_bkt->left = b;
	}
	
	Bucket* insert_bucket_f0(Bucket* b) {
		if (bkt.find(0) != bkt.end()) {
			return nullptr;
		}
		b->freq = 0;
		insert_bucket(bkt_root, bkt_root->right, b);
		return b;
	}
	
	Bucket* insert_bucket_fn(int f0, Bucket* b) {
		b->freq = f0;
		insert_bucket(bkt_rootn->left, bkt_rootn, b);
		return b;
	}
	
	void reallocate_node(Node* node) {
		int f0 = node->freq;
		
	}
	
public:
	LFUCache(int capacity) {
		max_cap = capacity;
		root = new Node(0);
		rootn = new Node(0);
		root->right = rootn;
		rootn->left = root;
		bkt_root = new Bucket();
		bkt_rootn= new Bucket();
		bkt_root->right = bkt_rootn;
		bkt_rootn->left = bkt_root;
		bkt_root->start = root;
		bkt_root->stop = root;
		bkt_rootn->start = rootn;
		bkt_rootn->stop = rootn;
	}
	
	~LFUCache() {
		// complete it later
	}
	
	int get(int key) {
		
		
		// f0++;

		// move node
		// update maps
	}
	
	void put(int key, int value) {
		
	}
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
