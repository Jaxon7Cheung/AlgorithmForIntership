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
private:
    // 快慢指针找中间结点
    ListNode* middleNode(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        
        // 奇数结点 && 偶数结点
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }
    
    // 反转链表
    ListNode* reverseListNode(ListNode* head) {
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
    // 双指针链表重排（头尾交叉）
    void reorderList(ListNode* head) {
        ListNode* middle = middleNode(head);
        middle = reverseListNode(middle);

        ListNode* l = head;
        ListNode* r = middle;

        while (r->next) {
            ListNode* nextL = l->next;
            ListNode* nextR = r->next;
            l->next = r;
            r->next = nextL;
            l = nextL;
            r = nextR;
        }
        
    }
};

void printListNode(ListNode* head) {
    ListNode* move = head;
    while (move) {
        cout << move->val << ' ';
        move = move->next;
    }
}
 
int main() {
    ListNode* node = new ListNode(2);
    node->next = new ListNode(6);
    node->next->next = new ListNode(77);
    node->next->next->next = new ListNode(8);
    node->next->next->next->next = new ListNode(17);
    
    Solution solution;
    solution.reorderList(node);
    printListNode(node);

    return 0;
}
