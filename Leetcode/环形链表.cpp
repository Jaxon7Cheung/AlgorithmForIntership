//
//  main.cpp
//  lt&al
//
//  Created by 张旭洋 on 2024/10/7.
//

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 快慢指针
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (!head || !head->next) return false;
        ListNode* slow = head;
        ListNode* fast = head;

        while (true) {
            if (!fast || !fast->next) return false;
            slow = slow->next;
            fast = fast->next->next;
            if (fast == slow) return true;
        }

    }
};

// 哈希表
// class Solution {
// public:
//     bool hasCycle(ListNode *head) {
//         unordered_set<ListNode *> set;
//         ListNode* cur = head;
//         while (cur) {
//             if (set.count(cur)) return true;
//             set.insert(cur);
//             cur = cur->next;
//         }
//         return false;
//     }
// };

 
int main() {
    
    ListNode* node1 = new ListNode(3);
    ListNode* node2 = new ListNode(2);
    ListNode* node3 = new ListNode(0);
    ListNode* node4 = new ListNode(-4);
    node1->next = node2;node2->next = node3;node3->next = node4;node4->next = node2;
    
    Solution solution;
    cout << solution.hasCycle(node1) << endl;
    
    return 0;
}
