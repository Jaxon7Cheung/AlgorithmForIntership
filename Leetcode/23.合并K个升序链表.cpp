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
//     ListNode* mergeKLists(vector<ListNode*>& lists) {
//         return solve(lists, 0, lists.size() - 1);
//     }
//     ListNode* solve(vector<ListNode*>& lists, int l, int r) {
//         if (l == r) return lists[l];
//         if (l > r) return nullptr;
//
//         // int mid = (l + r) >> 1; // 太炫了
//         int mid = l + (r - l) / 2;
//
//         ListNode* a = solve(lists, l, mid);
//         ListNode* b = solve(lists, mid + 1, r);
//
//         return mergeTwoLists(a, b);
//     }
    
    // 用小顶堆来维护链表头结点的最小值
    // 维护一个小顶堆
        ListNode* mergeKLists(std::vector<ListNode*>& lists) {

            // 建堆所用数组
            vector<ListNode*> heap;
            for (ListNode* head : lists) {
                // 过滤掉空链表
                if (head) heap.push_back(head);
            }

            // 维护堆的个数
            int k = heap.size();
            if (!k) return nullptr;

            // 建立小顶堆
            buildHeap(heap, k);

            ListNode* dummyNode = new ListNode();
            ListNode* tail = dummyNode;

            while (k > 0) {
                ListNode* top = heap[0];
                // 取出堆顶元素（当前最小值）
                tail->next = top;
                tail = tail->next;

                // 如果被取出的节点还有下一个元素，将其加入堆中
                // 如果没有下一个元素，就直接堆化，将堆的最后一个元素移到堆顶
                heap[0] = (top->next) ? (top->next) : (heap[(k--) - 1]);

                // 对堆顶元素进行堆化
                if (k > 0) heapify(heap, 0, k);
            }

            return dummyNode->next;
        }
        // 建堆
        void buildHeap(vector<ListNode *>& nums, int k) {
            for (int i = k / 2 - 1; i >= 0; --i) {
                heapify(nums, i, k);
            }
        }
        // 堆化
        void heapify(vector<ListNode *>& nums, int root, int k) {
            
            int next = root;
            int lChild = 2 * root + 1;
            int rChild = 2 * root + 2;

            if (lChild < k && nums[next]->val > nums[lChild]->val) {
                next = lChild;
            }
            if (rChild < k && nums[next]->val > nums[rChild]->val) {
                next = rChild;
            }

            if (root != next) {
                swap(nums[next], nums[root]);
                heapify(nums, next, k);
            }
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
