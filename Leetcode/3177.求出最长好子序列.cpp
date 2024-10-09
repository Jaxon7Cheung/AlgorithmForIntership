//
//  main.cpp
//  lt&al
//
//  Created by 张旭洋 on 2024/10/7.
//

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int maximumLength(vector<int>& nums, int k) {
        // 上面的方法中，要找到最大值，就要枚举i之前的所有位置j

        // 可以直接用长度为k+1的数组record[l]记录在nums[i]之前每个l的最大值，就不用枚举了
        vector<int> record(k + 1, 0);
        // 用哈希表维护以元素nums[i]结尾不同l的最大值
        unordered_map<int, vector<int>> dp;

        for (int num : nums) {
            if (!dp.count(num)) {
                // 首次处理元素num，将其状态数组进行初始化
                dp[num] = vector<int> (k + 1, 0);
            }

            // 新状态在后面，所以要逆序进行更新，避免record在使用前更新
            for (int l = k; l >= 0; --l) {
                int preL = 0;
                if (l - 1 >= 0) preL = record[l - 1];
                // 处理l = 0时的越界情况

                // 要么从相同元素结尾的存在l个下标满足不等条件的最长好子序列转移过来
                // 要么从之前存在l-1个下标满足不等条件的最长好子序列转移过来
                dp[num][l] = max(dp[num][l], preL) + 1;
                // 更新record[l]
                record[l] = max(record[l], dp[num][l]);
            }
        }
        // record[k]当前存在k个下标满足不等条件的最长好子序列（不超过k个，那么k个一定是最长的）
        return record[k];
    }
};

 
int main() {
    vector<int> nums = {1, 2, 1, 1, 5};
    
    Solution solution;
    cout << solution.maximumLength(nums, 2) << endl;
    
    return 0;
}
