//
//  main.cpp
//  lt&al
//
//  Created by 张旭洋 on 2024/10/7.
//

#include <iostream>
#include <vector>
using namespace std;
 
void mergeSort(vector<int>& nums, vector<int>& tmp, int left, int right) {
    if (left >= right) return;
    
    // 分解
    int mid = left + (right - left) / 2;
    mergeSort(nums, tmp, left, mid);
    mergeSort(nums, tmp, mid + 1, right);
    
    // 归并
    int l = left, r = mid + 1;
    int tmpPos = left;
    // 左右两部分分别进行比较
    while (l <= mid && r <= right) {
        if (nums[l] > nums[r]) {
            tmp[tmpPos++] = nums[r++];
        } else {
            tmp[tmpPos++] = nums[l++];
        }
    }
    // 合并剩余有序部分
    while (l <= mid) {
        tmp[tmpPos++] = nums[l++];
    }
    while (r <= right) {
        tmp[tmpPos++] = nums[r++];
    }
    
    // 临时数组赋给原数组
    for (int i = left; i <= right; i++) {
        nums[i] = tmp[i];
    }
//    copy(tmp.begin() + left, tmp.begin() + right + 1, nums.begin() + left);
}

 
int main() {
    vector<int> nums = {8, 1, 14, 3, 21, 5, 7, 10};
    int n = nums.size();
    vector<int> tmp(n, 0);
    mergeSort(nums, tmp, 0, n - 1);
    
    for (int num : nums) {
        cout << num << ' ';
    }
    
    return 0;
}
