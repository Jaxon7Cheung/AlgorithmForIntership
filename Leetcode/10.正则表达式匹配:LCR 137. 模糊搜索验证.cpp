//
//  main.cpp
//  lt&al
//
//  Created by 张旭洋 on 2024/10/7.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 首先没有特殊字符的话，长度不一样肯定不匹配，返回false
// *表示前面的字符可出现0次/多次，也可说是可有可无

// 例子：s:"aab" p:"c*a*b"
// 从左往右扫的话，字符后面是否跟着星号会影响结果，
// a与c不匹配，还要看c有没有跟着'*'，分析起来有点复杂

// 从右往左扫，星号的前面肯定有一个字符，星号也只影响这一个字符，
// 每次只用考虑末尾字符的匹配问题，剩下的子串匹配就是子问题，考虑用动态规划解决
// 也就是说，s,p是否匹配取决于：1.最右端是否匹配 2.剩余的子串是否匹配

// bool dp[i][j]表示 i个字符的s串 是否匹配 j个字符的p串

class Solution {
private:
    bool matches(string s, string p,  int i, int j) {
        if (!i) return false; // 如果 s 是空的，不能匹配
        if (p[j - 1] == '.') return true; // '.' 可以匹配任意字符
        return s[i - 1] == p[j - 1]; // 字符匹配
    }
public:
    bool isMatch(string s, string p) {
        int m = s.size();
        int n = p.size();

        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        dp[0][0] = true;
        for (int i = 0; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (p[j - 1] == '*') {
                    // '*'可以匹配0次前面的字符，故可以跳过前面的字符和'*'
                    dp[i][j] = dp[i][j - 2];

                    // 如果s的当前字符与'*'前的字符匹配，则可以考虑'*'匹配多个字符（N个）
                    // if (matches(s, p, i, j - 1)) dp[i][j] = dp[i][j] || dp[i - 1][j];
                    if (matches(s, p, i, j - 1)) {
                        // 如果匹配，检查去掉s中最后一个字符后的情况
                        // 设置为 true，如果前面的状态匹配
                        if (dp[i - 1][j] == true) dp[i][j] = true;
                    }
                } else {
                    // 模式当前字符是'.'或普通字符
                    // 直接匹配当前字符，只有在 matches 为 true 时才更新 dp[i][j]
                    if (matches(s, p, i, j)) dp[i][j] = dp[i - 1][j - 1];
                }
            }
        }

        // 返回s和p是否完全匹配的结果
        return dp[m][n];
    }
};
 
int main(void) {
    Solution solution;
    
    string s1 = "abvsbc";
    string p1 = "ab*bvss*bc";
    cout << solution.isMatch(s1, p1) << endl;
    
    string s2 = "ccaaab";
    string s22 = "ccb";
    string p2 = "c*a*b";
    cout << solution.isMatch(s2, p2) << endl;

    return 0;
}
