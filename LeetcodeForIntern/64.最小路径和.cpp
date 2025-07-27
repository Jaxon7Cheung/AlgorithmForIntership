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
    int minPathSum(vector<vector<int>>& grid) {
        // dp[i][j]表示走到(i, j)的最小路径和
        // 只能向右或向下(i, j - 1)或(i - 1, j)->(i, j)
        // dp[i][j] = min(dp[i][j - 1], dp[i - 1][j]) + grid[i][j];

        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> dp(n, vector<int>(m, 0));
        dp[0][0] = grid[0][0];

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (!i && !j) continue;
                if (!i) {  // 边界矩阵
                    dp[i][j] = dp[i][j - 1] + grid[i][j];
                } else if (!j) { // 边界矩阵
                    dp[i][j] = dp[i - 1][j] + grid[i][j];
                } else {
                    dp[i][j] = min(dp[i][j - 1], dp[i - 1][j]) + grid[i][j];
                }
            }
        }

        return dp[n - 1][m - 1];

    }
};
 
int main() {
    vector<vector<int>> grid = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}}; // 7
    vector<vector<int>> grid1 = {{1, 2, 3}, {4, 5, 6}}; // 12

    Solution solution;
    cout << solution.minPathSum(grid) << endl;
    cout << solution.minPathSum(grid1) << endl;
    

    return 0;
}
