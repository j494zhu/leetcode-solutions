#include "ListNode.h"
#include <vector>
using namespace std;

class Solution {
private:
	ListNode * ver2(ListNode* head) {
		if (!head) {
			return nullptr;
		}
		ListNode * tail = nullptr;
		ListNode * mov = head;
		while (head) {
			ListNode * nxt = head->next;
			mov->next = tail;
			tail = mov;
			head = nxt;
			mov = head;
		}
		return tail;
	}

public:
	ListNode* reverseList(ListNode* head) {
		if (!head) {
			return nullptr;
		}
		vector<ListNode*> vec;
		while (head) {
			vec.push_back(head);
			head = head->next;
		}
		for (int i = vec.size() - 1; i >= 1; i--) {
			vec[i]->next = vec[i - 1];
		}
		vec[0]->next = nullptr;
		return vec[vec.size() - 1];
	}
};

