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
    int search(vector<int>& nums, int target) {
        int l = 0;
        int r = nums.size() - 1;
        while (l <= r) {
            // 先算出一个中间位置，l指针的值比中间值小，左区间一定是有序的
            // 反之亦然
            int mid = l + (r - l) / 2;
            if (nums[mid] == target) return mid;
            
            if (nums[l] <= nums[mid]) {
                // 左升序
                // 且target在这个区间
                (nums[l] <= target && target < nums[mid]) ? (r = mid - 1) : (l = mid + 1);
            } else {
                // 右升序
                // 且target在这个区间
                (nums[mid] < target && target <= nums[r]) ? (l = mid + 1) : (r = mid - 1);
            }
        }
        return -1;
    }
};
 
int main(void) {
    Solution solution;
    
    vector<int> nums = {4, 5, 6, 9, 0, 1, 2, 3};
    
    // 时间复杂度要求log N
    cout << solution.search(nums, 9) << endl;

    return 0;
}
