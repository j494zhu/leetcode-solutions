#include <vector>
#include <unordered_map>
using namespace std;

class Node {
public:
	int val;
	vector<Node*> neighbors;
	Node() {
		val = 0;
		neighbors = vector<Node*>();
	}
	Node(int _val) {
		val = _val;
		neighbors = vector<Node*>();
	}
	Node(int _val, vector<Node*> _neighbors) {
		val = _val;
		neighbors = _neighbors;
	}
};

class Solution {
public:
	unordered_map<Node*, Node*> us;
	Node* cloneGraph(Node* node) {
		if (!node) {
			return nullptr;
		}
		if (us.find(node) != us.end()) {
			return us[node];
		}
		Node* x = new Node(node->val);
		us[node] = x;
		
		for (Node* y : node->neighbors) {
			if (us.find(y) == us.end()) {
				x->neighbors.emplace_back(cloneGraph(y));
			} else {
				x->neighbors.emplace_back(us[y]);
			}
		}
		return x;
	}
};
