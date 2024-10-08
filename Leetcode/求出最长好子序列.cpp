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
    // 动态规划：dp[i][l] 表示以nums[i]结尾，存在l个下标满足不等条件的最长好子序列
    // 初始状态：对于任意nums[i]，自己作为一个子序列，就有dp[i][0] = 1
    // 状态转移方程：dp[i][l] = dp[j][l] + 1, nums[i] = nums[j]
    //                        dp[j][l - 1] + 1, nums[i] ≠ nums[j]
    int maximumLength(vector<int>& nums, int k) {
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(k + 1, 1));

        int res = 1;
        for (int i = 0; i < n; ++i) {
            dp[i][0] = 1;
            // 枚举l~(0, k]
            for (int l = 0; l <= min(i, k); ++l) {
                // 将nums[i]追加到前面的nums[j]结尾的最长好子序列
                for (int j = 0; j < i; ++j) {
                    bool flag = (nums[i] != nums[j]);
                    if (l - flag >= 0) { // 防止越界
                        // 取最长的子序列
                        dp[i][l] = max(dp[i][l], dp[j][l - flag] + 1);
                    }
                }
                // 最内层for循环出来之后，dp已经维护好，取l <= k条件下的最大值即可
                res = max(res, dp[i][l]);
            }
        }
        return res;
    }
};

 
int main() {
    
    Solution solution;
    vector<int> nums = {1, 2, 1, 1, 3};
    cout << solution.maximumLength(nums, 2) << endl;
    
    return 0;
}
