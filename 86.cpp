#include "ListNode.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <stdio.h>

class Solution {
public:
	ListNode* partition(ListNode* head, int x) {
		ListNode l1;
		ListNode l2;
		ListNode * tail1 = &l1;
		ListNode * tail2 = &l2;
		
		while (head) {
			if (head->val < x) {
				tail1->next = head;
				tail1 = tail1->next;
			} else {
				tail2->next = head;
				tail2 = tail2->next;
			}
			head = head->next;
		}
		tail1->next = l2.next;
		tail2->next = nullptr;
		return l1.next;
	}
};
