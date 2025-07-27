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

// 快慢指针：主要是公式的推导
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (!head || !head->next) return nullptr;
        ListNode* slow = head;
        ListNode* fast = head;

        while (true) {
            if (!fast || !fast->next) return nullptr;
            slow = slow->next;
            fast = fast->next->next;
            if (fast == slow) break;
        }
        
        fast = head;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
        
    }
};

// 哈希表
// class Solution {
// public:
//     ListNode *detectCycle(ListNode *head) {
//         unordered_set<ListNode *> set;
//         ListNode* cur = head;
//         while (cur) {
//             if (set.count(cur)) return cur;
//             set.insert(cur);
//             cur = cur->next;
//         }
//         return nullptr;
//     }
// };

 
int main() {
    
    ListNode* node1 = new ListNode(3);
    ListNode* node2 = new ListNode(2);
    ListNode* node3 = new ListNode(0);
    ListNode* node4 = new ListNode(-4);
    node1->next = node2;node2->next = node3;node3->next = node4;node4->next = node2;
    
    Solution solution;
    cout << solution.detectCycle(node1) << " == " << node2 << endl;
    
    return 0;
}
