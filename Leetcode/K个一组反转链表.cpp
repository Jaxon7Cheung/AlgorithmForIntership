//
//  main.cpp
//  lt&al
//
//  Created by 张旭洋 on 2024/10/7.
//

#include <iostream>
#include <vector>
#include <queue>
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
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* dummyNode = new ListNode(0, head);
        ListNode* pre = dummyNode;
        ListNode* tail = head;

        // 每次循环进行一次反转操作
        while (tail) {
            // 找到待反转链表的尾结点
            int count = k;
            while (count > 1) {
                tail = tail->next;
                count--;
                // 处理链表长度不是k的整数倍的情况
                if (!tail) return dummyNode->next;
            }
            
            // 进行反转
            // next记录下一组头结点
            // pre永远是组内头结点的前驱，即pre->next指向每组的头结点
            ListNode* next = tail->next;
            tail->next = nullptr;

            ListNode* sHead = pre->next;
            pre->next = reverseGroup(sHead); // 反转并连接组内头结点
            
            // 反转后tail变组内头结点，sHead变组内尾结点
            sHead->next = next; // 连接下一组头结点
            pre = sHead;
            tail = next; // 更新
        }
        return dummyNode->next;
    }

    ListNode* reverseGroup(ListNode* head) {
        ListNode* tmp = nullptr;
        ListNode* cur = head;
        while (cur) {
            ListNode* next = cur->next;
            cur->next = tmp;
            tmp = cur;
            cur = next;
        }
        return tmp;
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
    ListNode* node1 = new ListNode(3);
    ListNode* node2 = new ListNode(2);node1->next = node2;
    ListNode* node3 = new ListNode(1);node2->next = node3;
    ListNode* node4 = new ListNode(7);node3->next = node4;
    ListNode* node5 = new ListNode(6);node4->next = node5;
    ListNode* node6 = new ListNode(5);node5->next = node6;
    ListNode* node7 = new ListNode(77);node6->next = node7;
    ListNode* node8 = new ListNode(66);node7->next = node8;
    
    Solution solution;
    ListNode* head = solution.reverseKGroup(node1, 4); // 7 1 2 3 66 77 5 6
//    ListNode* head = solution.reverseKGroup(node1, 3);  // 1 2 3 5 6 7 77 66
    printList(head);
    
    
    return 0;
}
