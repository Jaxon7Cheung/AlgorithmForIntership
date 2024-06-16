//
//  main.cpp
//  leetcodeHot100
//
//  Created by 张旭洋 on 2024/6/5.
//

#include <iostream>
#include "两数之和.cpp"

int main(int argc, const char * argv[]) {
    Solution solution;
    
    vector<int> nums = {2, 7, 11, 15};
    vector<int> result = solution.twoSum(nums, 26);
    
    cout << result[0] << ' ' << result[1] << endl;
    
    return 0;
}
