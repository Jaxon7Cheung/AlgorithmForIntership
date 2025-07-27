//
//  两数之和.cpp
//  leetcodeHot100
//
//  Created by 张旭洋 on 2024/6/5.
//

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int i = 0, j = 0;
        for (i = 0; i < nums.size() - 1; ++i) {
            for (j = i + 1; j < nums.size(); ++j) {
                if (nums[i] + nums[j] == target) {
                    return {i, j};
                }
            }
        }
        return {i, j};
    }
};

int main(int argc, const char * argv[]) {
    Solution solution;
    
    vector<int> nums = {2, 7, 11, 15};
    vector<int> result = solution.twoSum(nums, 26);
    
    cout << result[0] << ' ' << result[1] << endl;
    
    return 0;
}
