#include "ListNode.h"
using namespace std;
class Solution {
private:
	void reverseList(ListNode* head) {
		if (!head) return;
		ListNode* rev = nullptr;
		while (head) {
			ListNode* next_node = head->next;
			head->next = rev;
			rev = head;
			head = next_node;
		}
	}
	ListNode* getK(ListNode* head, int k) {
		if (!head) return nullptr;
		ListNode* node = head;
		int len = 0;
		while (node) {
			len++;
			if (len >= k) return node;
			node = node->next;
		}
		return nullptr;
	}
public:
	ListNode* reverseKGroup(ListNode* head, int k) {
		ListNode* kth = getK(head, k);
		if (kth == nullptr) return head;
		ListNode* next_node = kth->next;
		kth->next = nullptr;
		reverseList(head);
		head->next = reverseKGroup(next_node, k);
		return kth;
	}
};

void printList_(ListNode* head) {
	ListNode* curr = head; // Use a temp pointer to traverse
	while (curr != nullptr) {
		std::cout << curr->val << " -> ";
		curr = curr->next;
	}
	std::cout << "nullptr" << std::endl;
}

int main(void) {
	vector<ListNode*> vec(7); 
	for (int i = 0; i < 7; i++) {
		vec[i] = new ListNode(i);
		if (i != 0) vec[i - 1]->next = vec[i];
	}
	printList_(vec[0]);
	Solution x;
	ListNode* node = x.reverseKGroup(vec[0], 1);
	printList_(node);
}
