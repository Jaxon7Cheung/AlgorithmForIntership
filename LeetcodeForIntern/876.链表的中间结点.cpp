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
    ListNode* middleNode(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
};
 
int main() {
    ListNode* node = new ListNode(2);
    node->next = new ListNode(6);
    node->next->next = new ListNode(-77);
    node->next->next->next = new ListNode(8);
    node->next->next->next->next = new ListNode(17);
    
    Solution solution;
    ListNode* ans = solution.middleNode(node);
    cout << ans->val;

    return 0;
}
