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
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 迭代
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* dummyNode = new ListNode();
        ListNode* move = dummyNode;

        while (list1 && list2) {
            if (list1->val < list2->val) {
                move->next = list1;
                list1 = list1->next;
            } else {
                move->next = list2;
                list2 = list2->next;
            }
            move = move->next;
        }

        move->next = (!list1 ? list2 : list1);

        return dummyNode->next;;
    }
};

// 递归
//class Solution {
//public:
//    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
//        if (l1 == nullptr) {
//            return l2;
//        } else if (l2 == nullptr) {
//            return l1;
//        } else if (l1->val < l2->val) {
//            l1->next = mergeTwoLists(l1->next, l2);
//            return l1;
//        } else {
//            l2->next = mergeTwoLists(l1, l2->next);
//            return l2;
//        }
//    }
//};

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
    
    
    Solution solution;
    ListNode* ansHead = solution.mergeTwoLists(list1, list2);
    printList(ansHead);

    return 0;
}
