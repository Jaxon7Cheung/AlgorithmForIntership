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
    int reversePairs(vector<int>& record) {
        int n = record.size();
        vector<int> tmp(n, 0);
        return mergeSort(record, tmp, 0, n - 1);
    }

    int mergeSort(vector<int>& nums, vector<int>& tmp, int left, int right) {
        if (left >= right) return 0;

        int mid = left + (right - left) / 2;
        int count = mergeSort(nums, tmp, left, mid) + mergeSort(nums, tmp, mid + 1, right); // 分解

        int l = left, r = mid + 1;
        int pos = left;
        // 合并
        while (l <= mid && r <= right) {
            if (nums[l] > nums[r]) {
                tmp[pos++] = nums[r++];
                count += (mid - l + 1);
            } else {
                tmp[pos++] = nums[l++];
            }
        }
        while (l <= mid) tmp[pos++] = nums[l++];
        while (r <= right) tmp[pos++] = nums[r++];

        for (int i = left; i <= right; ++i) {
            nums[i] = tmp[i];
        }

        return count;
    }
};

 
int main() {
    vector<int> nums = {9, 7, 5, 4, 6};
    int n = nums.size();
    vector<int> tmp(n, 0);
    
    Solution solution;
    cout << solution.mergeSort(nums, tmp, 0, n - 1) << endl; // 8
    
    return 0;
}
