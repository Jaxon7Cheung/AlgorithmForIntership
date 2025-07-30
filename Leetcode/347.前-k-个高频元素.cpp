/*
 * @lc app=leetcode.cn id=347 lang=cpp
 *
 * [347] 前 K 个高频元素
 */

// @lc code=start

struct Tuple {
    int index;
    int count;
    Tuple(int i, int c) : index(i), count(c) {}
};

class Solution {
private:
    void heapify(vector<Tuple>& nums, int root, int k) {
        int next = root;
        int lChild = root * 2 + 1;
        int rChild = root * 2 + 2;

        if (lChild < k && nums[lChild].count < nums[next].count) {
            next = lChild;
        }
        if (rChild < k && nums[rChild].count < nums[next].count) {
            next = rChild;
        }

        if (next != root) {
            swap(nums[next], nums[root]);
            heapify(nums, next, k);
        }
    }

    void buildHeap(vector<Tuple>& nums, int k) {
        for (int i = k / 2 - 1; i >= 0; --i) {
            heapify(nums, i, k);
        }
    }
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> hash;
        for (int num : nums) {
            hash[num]++;
        }

        vector<Tuple> heap;
        for (const auto& [index, count] : hash) {
            heap.push_back(Tuple(index, count));
        }

        buildHeap(heap, k);
        for (int i = k; i < heap.size(); ++i) {
            if (heap[0].count < heap[i].count) {
                swap(heap[0], heap[i]);
                heapify(heap, 0, k);
            }
        }
 
        vector<int> ans;
        for (int i = 0; i < k; ++i) {
            ans.push_back(heap[i].index);
        }

        return ans;
    }
};
// @lc code=end

