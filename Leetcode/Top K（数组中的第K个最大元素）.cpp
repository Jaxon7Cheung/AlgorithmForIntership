//
//  main.cpp
//  lt&al
//
//  Created by 张旭洋 on 2024/10/7.
//

#include <iostream>
#include <vector>
using namespace std;
 
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        // 维护一个结点数为K的小顶堆
        buildHeap(nums, k);

        for (int i = k; i < nums.size(); i++) {
            if (nums[0] < nums[i]) {
                swap(nums[0], nums[i]);
                heapify(nums, 0, k);
            }
        }
        return nums[0];
    }

    // 自下而上建立小顶堆
    void buildHeap(vector<int>& nums, int k) {
        for (int i = k / 2 - 1; i >= 0; i--) {
            heapify(nums, i, k);
        }
    }

    // 下滤进行堆化
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
};
 
int main() {
    vector<int> nums = {8, 1, 14, 3, 21, 5, 7, 10};
    
    Solution solution;
    cout << solution.findKthLargest(nums, 1) << endl;
    cout << solution.findKthLargest(nums, 2) << endl;
    cout << solution.findKthLargest(nums, 3) << endl;
    cout << solution.findKthLargest(nums, 4) << endl;
    cout << solution.findKthLargest(nums, 5) << endl;
    cout << solution.findKthLargest(nums, 6) << endl;
    cout << solution.findKthLargest(nums, 7) << endl;
    
    return 0;
}
