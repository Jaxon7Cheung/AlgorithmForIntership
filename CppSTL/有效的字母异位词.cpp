//
//  有效的字母异位词.cpp
//  STLReviewInCpp
//
//  Created by 张旭洋 on 2024/7/20.
//

#include <iostream>
using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {
        unsigned long sLen = s.length();
        unsigned long tLen = t.length();

        if (sLen != tLen) return false;

        int hash[26] = {0};
        for (int i = 0; i < sLen; ++i) hash[s[i] - 'a']++;
        
        for (int i = 0; i < tLen; ++i) {
            hash[t[i] - 'a']--;
            // if (hash[t[i] - 'a'] < 0) return false;
        }

        for (int i = 0; i < 26; ++i) {
            if (hash[i]) return false;
        }

        return true;

    }

    bool isAnagram2(string s, string t) {
        unsigned long sLen = s.length();
        unsigned long tLen = t.length();

        if (sLen != tLen) return false;

        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        return s == t;

    }
};

int main(int argc, const char * argv[]) {
    Solution solution;
    cout << solution.isAnagram("anagram", "nagaram") << endl;
    cout << solution.isAnagram("rat", "cat") << endl;
    cout << solution.isAnagram2("anagram", "nagaram") << endl;
    cout << solution.isAnagram2("rat", "cat") << endl;
    return 0;
}
