/*
 * @lc app=leetcode.cn id=25 lang=cpp
 *
 * [25] K 个一组翻转链表
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
private:
    ListNode* reverseGroup(ListNode* head) {
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
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* dummy = new ListNode();
        dummy->next = head;

        ListNode* cur = head;
        ListNode* pre = dummy;

        while (cur) {
            for (int i = 1; i < k; ++i) {
                cur = cur->next;
                if (!cur) return dummy->next;
            }
            
            ListNode* next = cur->next;
            cur->next = nullptr;

            ListNode* h = pre->next;
            pre->next = reverseGroup(h);

            pre = h;
            h->next = next;
            cur = next;
        }
        return dummy->next;
    }
};
// @lc code=end

