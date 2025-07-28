/*
 * @lc app=leetcode.cn id=23 lang=cpp
 *
 * [23] 合并 K 个升序链表
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
    // 法一：顺序合并
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* dummy = new ListNode();
        ListNode* p = dummy;
        while (list1 && list2) {
            if (list1->val < list2->val) {
                p->next = list1;
                list1 = list1->next;
            } else {
                p->next = list2;
                list2 = list2->next;
            }
            p = p->next;
        }
        p->next = list1 ? list1 : list2;
        return dummy->next;
    }
    ListNode* mergeKListsV1(vector<ListNode*>& lists) {
        ListNode* list = nullptr;
        for (int i = 0; i < lists.size(); ++i) {
            list = mergeTwoLists(list, lists[i]);
        }
        return list;
    }

    // 法二：小顶堆
    ListNode* mergeKListsV2(vector<ListNode*>& lists) {
        vector<ListNode*> heap;
        for (auto list : lists) {
            if (list) heap.push_back(list);
        }

        int k = heap.size();
        if (!k) return nullptr;
        buildHeap(heap, k);

        ListNode* dummy = new ListNode();
        ListNode* cur = dummy;

        while (k) {
            ListNode* top = heap[0];
            cur->next = top;
            cur = cur->next;

            heap[0] = top->next ? top->next : heap[k-- - 1];
            if (k) heapify(heap, 0, k);
        }

        return dummy->next;
    }

    // 自下而上建堆
    void buildHeap(vector<ListNode*>& nums, int k) {
        for (int i = k / 2 - 1; i >= 0; --i) {
            heapify(nums, i, k);
        }
    }

    void heapify(vector<ListNode*>& nums, int root, int k) {
        int next = root;
        int lChild = 2 * root + 1;
        int rChild = 2 * root + 2;

        if (lChild < k && nums[lChild]->val < nums[next]->val) {
            next = lChild;
        }
        if (rChild < k && nums[rChild]->val < nums[next]->val) {
            next = rChild;
        }

        if (next != root) {
            swap(nums[next], nums[root]);
            heapify(nums, next, k);
            return;
        }
    }

    // 法三：分治、归并
    ListNode* mergeKListsV3(vector<ListNode*>& lists) {
        return solve(lists, 0, lists.size() - 1);
    }

    ListNode* solve(vector<ListNode*>& lists, int l, int r) {
        if (l == r) return lists[l];
        if (l > r) return nullptr;
        
        int mid = l + (r - l) / 2;
        ListNode* a = solve(lists, l, mid);
        ListNode* b = solve(lists, mid + 1, r);

        return mergeTwoLists(a, b);
    }

public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        return mergeKListsV3(lists);
    }
};
// @lc code=end

