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
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, 0));

        dp[0][0] = 1;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (!i && !j) continue;
                if (i && j) {
                    dp[i][j] = dp[i][j - 1] + dp[i - 1][j];
                } else {
                    dp[i][j] = 1;
                }
            }
        }
        return dp[m - 1][n - 1];
    }
};
 
int main(void) {
    
    Solution solution;
    cout << solution.uniquePaths(3, 7) << endl;
    cout << solution.uniquePaths(3, 2) << endl;
    

    return 0;
}
