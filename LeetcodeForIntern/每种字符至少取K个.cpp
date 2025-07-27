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
    int takeCharacters(string s, int k) {
        // 正难则反，考虑到每次操作都是一个连续的过程
        // 维护一个滑动窗口，里面是不需要被取走的字母，最后取窗口最大值
        vector<int> countABC(3, 0);
        for (char ch : s) {
            countABC[ch - 'a']++;
        }
        if (countABC[0] < k || countABC[1] < k || countABC[2] < k) {
            return -1;
        }

        int left = 0, right = 0;
        int maxLen = 0, n = s.size();
        while (right < n) {
            char r = s[right];
            countABC[r - 'a']--; // 不需要被取走，放到窗口里right++
            while (left <= right && countABC[r - 'a'] < k) {
                char l = s[left++];
                countABC[l - 'a']++; // 需要被取走，拿出窗口left++
            }
            maxLen = max(maxLen, right - left + 1); // 将每次满足条件维护好的窗口长度记录下来，最后取最大值返回
            right++;
        }
        return n - maxLen;
    }
};

 
int main() {
    
    Solution solution;
    string s = "aabaaaacaabc";
    cout << solution.takeCharacters(s, 3) << endl;
    cout << solution.takeCharacters(s, 2) << endl;
    
    
    return 0;
}
