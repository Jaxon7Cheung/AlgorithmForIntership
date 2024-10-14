//
//  main.cpp
//  lt&al
//
//  Created by 张旭洋 on 2024/10/7.
//

#include <iostream>
#include <string>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* curA = headA;
        ListNode* curB = headB;

        while (curA != curB) {
            if (!curA) curA = headB;
            else curA = curA->next;

            if (!curB) curB = headA;
            else curB = curB->next;
        }

        // 不相交迟早指向同时空，从上面的循环中跳出来
        return curA;
    }
};

// class Solution {
// public:
//     ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
//         unordered_set<ListNode *> set;

//         ListNode* curA = headA;
//         while (curA) {
//             set.insert(curA);
//             curA = curA->next;
//         }

//         ListNode* curB = headB;
//         while (curB) {
//             if (set.count(curB)) return curB;
//             curB = curB->next;
//         }

//         return nullptr;
//     }
// };



void printList(ListNode* head) {
    ListNode* cur = head;
    while (cur) {
        cout << cur->val << ' ';
        cur = cur->next;
    }
}
 
int main() {
    ListNode* list1 = new ListNode(2);
    list1->next = new ListNode(6);
    list1->next->next = new ListNode(9);
    
    ListNode* list2 = new ListNode(-3);
    list2->next = new ListNode(6);
    list2->next->next = new ListNode(9);
    list2->next->next->next = new ListNode(10);
    list2->next->next->next->next = new ListNode(17);
    
    list1->next->next->next = list2->next;
    
    
    Solution solution;
    ListNode* ansHead = solution.getIntersectionNode(list1, list2);
    printList(ansHead);

    return 0;
}
