#include "TreeNode.h"
using namespace std;

class Solution {
public:
	int sumNumbers(TreeNode* root) {
		int result = 0;
		auto rec = [&result](auto self, TreeNode * node, int base) -> void {
			if (!node) return;
			if (!node->left && !node->right) {
				result += (base * 10 + node->val);
				return;
			} 
			if (node->left) self(self, node->left, base * 10 + node->val);
			if (node->right) self(self, node->right, base * 10 + node->val);
			return;
		};
		rec(rec, root, 0);
		return result;
	}
};

int main(void) {
	auto add = [](int a, int b) {return a + b;};
	cout << (add(3, 9)) << endl;
	
	auto factorial = [](auto self, int n) -> int {
		return (n <= 1) ? 1 : n * self(self, n - 1);
	};
	
	cout << factorial(factorial, 5) << endl;
}

