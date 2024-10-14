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
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:

    // 顺序合并，用一个变量 ans 来维护以及合并的链表，第 i 次循环把第 i 个链表和 ans 合并，答案保存到 ans 中。
    // ListNode* mergeKLists(vector<ListNode*>& lists) {
    //     ListNode* ans = nullptr;

    //     for (int i = 0; i < lists.size(); ++i) {
    //         ans = mergeTwoLists(ans, lists[i]);
    //     }
    //     return ans;
    // }

    // 分治、归并
     ListNode* mergeKLists(vector<ListNode*>& lists) {
         return solve(lists, 0, lists.size() - 1);
     }
     ListNode* solve(vector<ListNode*>& lists, int l, int r) {
         if (l == r) return lists[l];
         if (l > r) return nullptr;

         // int mid = (l + r) >> 1; // 太炫了
         int mid = l + (r - l) / 2;

         ListNode* a = solve(lists, l, mid);
         ListNode* b = solve(lists, mid + 1, r);

         return mergeTwoLists(a, b);
     }
    
    
    
    
    // 合并两个有序链表
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* dummyNode = new ListNode();
        ListNode* move = dummyNode;

        while (l1 && l2) {
            if (l1->val < l2->val) {
                move->next = l1;
                l1 = l1->next;
            } else {
                move->next = l2;
                l2 = l2->next;
            }
            move = move->next;
        }

        move->next = (!l1 ? l2 : l1);

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
 
int main() {
    ListNode* list1 = new ListNode(2);
    list1->next = new ListNode(6);
    list1->next->next = new ListNode(9);
    
    ListNode* list2 = new ListNode(-3);
    list2->next = new ListNode(6);
    list2->next->next = new ListNode(9);
    list2->next->next->next = new ListNode(10);
    list2->next->next->next->next = new ListNode(17);
    
    ListNode* list3 = new ListNode(3);
    list3->next = new ListNode(77);
    list3->next->next = new ListNode(99);
    
    vector<ListNode *> lists = {list1, list2, list3};
    
    Solution solution;
    ListNode* ansHead = solution.mergeKLists(lists);
    printList(ansHead);

    return 0;
}
