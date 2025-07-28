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
        ListNode* dummy = new ListNode(0, head);
        ListNode* pre = dummy;
        ListNode* cur = head;

        while (cur) {
            for (int i = 1; i < k; ++i) {
                cur = cur->next;
                if (!cur) return dummy->next;
            }

            ListNode* next = cur->next;
            cur->next = nullptr;

            ListNode* sHead = pre->next;
            pre->next = reverseGroup(sHead);
            sHead->next = next;

            pre = sHead;
            cur = next;
        }

        return dummy->next;
    }
};
// @lc code=end

