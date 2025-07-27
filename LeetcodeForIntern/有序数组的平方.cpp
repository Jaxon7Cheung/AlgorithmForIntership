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
    vector<int> sortedSquares(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);

        int left = 0, right = n - 1;
        int pos = n - 1;
        while (left <= right) {
            if (abs(nums[left]) > abs(nums[right])) {
                ans[pos] = nums[left] * nums[left];
                left++;
            } else {
                ans[pos] = nums[right] * nums[right];
                right--;
            }
            pos--;
        }
        return ans;
    }
};

 
int main() {
    
    Solution solution;
    vector<int> nums = {-4, -1, 0, 3, 10};
    vector<int> ans = solution.sortedSquares(nums);
    for (int a : ans) cout << a << ' ';
    
    return 0;
}
