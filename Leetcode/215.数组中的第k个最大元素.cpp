/*
 * @lc app=leetcode.cn id=215 lang=cpp
 *
 * [215] 数组中的第K个最大元素
 */

// @lc code=start
class Solution {
private:
    void heapify(vector<int>& nums, int root, int k) {
        int next = root;
        int lChild = 2 * root + 1;
        int rChild = 2 * root + 2;

        if (lChild < k && nums[lChild] < nums[next]) {
            next = lChild;
        }
        if (rChild < k && nums[rChild] < nums[next]) {
            next = rChild;
        }

        if (next != root) {
            swap(nums[next], nums[root]);
            heapify(nums, next, k);
        }
    }

    void buildHeap(vector<int>& nums, int k) {
        for (int i = k / 2 - 1; i >= 0; --i) {
            heapify(nums, i, k);
        }
    }

public:
    int findKthLargest(vector<int>& nums, int k) {
        buildHeap(nums, k);

        for (int i = k; i < nums.size(); ++i) {
            if (nums[0] < nums[i]) {
                swap(nums[0], nums[i]);
                heapify(nums, 0, k);
            }
        }

        return nums[0];
    }
};
// @lc code=end

