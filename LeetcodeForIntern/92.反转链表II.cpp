//
//  main.cpp
//  lt&al
//
//  Created by 张旭洋 on 2024/10/7.
//

#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
private:
    ListNode* reverseList(ListNode* head) {
        ListNode* pre = nullptr;
        ListNode* cur = head;
        while (cur) {
            ListNode* tmp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = tmp;
        }
        return pre;
    }
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (left == right) return head;

        ListNode* dummyNode = new ListNode(0);
        dummyNode->next = head;

        int headLeft = left;
        ListNode* cur = dummyNode;
        while (--headLeft) cur = cur->next;
//        cout << cur->val << "##";
        // 前驱
        ListNode* pre = cur;
        ListNode* rHead = cur->next;

        int tailRight = right - left + 1;
        while (tailRight--) cur = cur->next;
//        cout << cur->val << "##";
        // 后继
        ListNode* next = cur->next;
        cur->next = nullptr;

        pre->next = reverseList(rHead);
        rHead->next = next;

        return dummyNode->next;
    }
    
    
};

void printList(ListNode* head) {
    ListNode* cur = head;
    while (cur) {
        cout << cur->val << ' ';
        cur = cur->next;
    }
}
 
int main(void) {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    head->next->next->next->next->next = new ListNode(6);
    head->next->next->next->next->next->next = new ListNode(7);

    Solution solution;
    solution.reverseBetween(head, 3, 6);
    printList(head);

    return 0;
}
