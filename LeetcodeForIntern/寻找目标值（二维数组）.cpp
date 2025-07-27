//
//  寻找目标值（二维数组）.cpp
//  Algorithm&Leetcode
//
//  Created by 张旭洋 on 2024/8/21.
//

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool findTargetIn2DPlants(vector<vector<int>>& plants, int target) {
        int j = 0, i = plants.size() - 1;
        while (j < plants[0].size() && i >= 0) {
            if (target > plants[i][j]) {
                j++;
            } else if (target < plants[i][j]) {
                i--;
            } else {
                return true;
            }
        }
        return false;
    }
};

int main() {
    vector<vector<int>> plants = {
        {1, 4, 7, 11, 15},
        {2, 5, 8, 12, 19},
        {3, 6, 9, 16, 22},
        {10, 13, 14, 17, 24},
        {18, 21, 23, 26, 30}
    };
    int target = 17;

    
    Solution solution;
    bool result = solution.findTargetIn2DPlants(plants, target);

    cout << result << endl;
    
    return 0;
}

