//
//  句子缩写.cpp
//  STLReviewInCpp
//
//  Created by 张旭洋 on 2024/6/17.
//

#include <iostream>
#include <string>
using namespace std;


//  将函数定义为inline，这样可以避免重复定义符号的错误

char toUpper(char letter) {
    return letter - ('a' - 'A');
}
 
bool isUpper(char letter) {
    return (letter >= 'A' && letter <= 'Z') ? 1 : 0;
}

class Solution {
public:
    void sentenceSum(void) {
        //    int a, b;
        //    while (cin >> a >> b) {
        //        cout << a + b << endl;
        //    }
        int n;
        cin >> n;
        getchar();
             
             
        while (n--) {
            string s;
            getline(cin, s);
            int fast = 0, slow = 0;
            unsigned long len = s.size();
        //  printf("%ld\n", len);
            while (fast < len) {
                while (s[fast] != ' ' && fast < len) {
                    fast++;
        //          printf("fast1 = %d\n", fast);
                }
                     
            char ch = s[slow];
                if (isUpper(ch)) {
                    cout << ch;
                } else {
                    cout << toUpper(ch);
                }
                     
                if (fast == len) {
                    cout << endl;
                    break;
                }
                     
                while (s[fast] == ' ' && fast < len) {
                    fast++;
        //          printf("fast2 = %d\n", fast);
                }
                     
                slow = fast;
            }
        }

    }
};

//int main(int argc, const char * argv[]) {
//    Solution solution;
////    putchar('u');
//    solution.sentenceSum();
//    return 0;
//}
