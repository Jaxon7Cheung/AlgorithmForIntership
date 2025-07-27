//
//  main.cpp
//  lt&al
//
//  Created by 张旭洋 on 2024/10/7.
//

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

// 连续子串，考虑滑动窗口
// 谈到滑动窗口，我们一定需要注意的是，什么时候移动左窗口、右窗口
class Solution {
public:
    string minWindow(string s, string t) {
        int left = 0, right = 0;

        // 记录带返回子串的起始位置和长度，从而返回该最小子串
        int start = 0, minL = s.size() + 1;

        unordered_map<char, int> hash;

        int n = s.size(), m = t.size();
        // for (int i = 0; i < m; ++i) hash[t[i]]++;
        for (char ch : t) hash[ch]++;

        while (right < n) {
            if (hash[s[right]] > 0) m--;
            hash[s[right]]--;

            // m为0说明当前窗口已经包含了t串左右字母
            if (!m) {
                // 移动左窗口找到最小的包含t串字母的子串

                // hash[s[left]] < 0说明都是s串有的，而t串没有的
                // 因此左窗口直接向右移动
                while (hash[s[left]] < 0) {
                    hash[s[left]]++;
                    left++;
                }

                // 此时hash[s[left]] == 0
                // 滑动窗口中最小子串已维护好
                if (minL > right - left + 1) {
                    start = left;
                    minL = right - left + 1;
                }
//                cout << s.substr(start, minL) << endl;

                 // （这段可以不写，但循环次数会增加）
                // 这段的作用就是：left现在肯定指向t串所含字母
                // 然后让left++，寻找后面的最小子串
                // left++后的窗口内已不含那个字母，
                // 窗口含有的话，hash--、m--，所以不含有hash[left]++、m++复原加回去
                 hash[s[left]]++;
                 left++;
                 m++;
            }
            // 继续寻找最小子串
            right++;
        }

        // minL仍为初始值s串长度+1，则无满足条件的最小子串，返回空字符串
        // 否则肯定找到了并返回
        return (minL == s.size() + 1) ? "" : s.substr(start, minL);
    }
};
 
int main() {
    string s = "DOABEODBCEBANNC";
    string t = "ABCB";
    
    Solution solution;
    cout << solution.minWindow(s, t) << endl;
//    solution.minWindow(s, t);

    return 0;
}
