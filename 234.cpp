#include "ListNode.h"
#include <vector>
using namespace std;
class Solution {
public:
	bool isPalindrome(ListNode* head) {
		if (!head) return true;
		vector<ListNode*> vec;
		while (head) {
			vec.push_back(head);
			head = head->next;
		}
		int len = vec.size();
		for (int i = 0; i < len / 2; i++) {
			if (vec[i]->val != vec[len - 1 - i]->val) return false;
		}
		return true;
	}
};
