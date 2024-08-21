//
//  数字各个位偶数之和.cpp
//  STLReviewInCpp
//
//  Created by 张旭洋 on 2024/6/17.
//

#include <iostream>
using namespace std;

class Solution {
public:
    void doubleSum(void) {
        int num;
        while (cin >> num) {
            int sum = 0;
            while (num) {
                int tmp = num % 10;
                if (!(tmp % 2)) {
                    sum += tmp;
                }
                num /= 10;
            }
            cout << sum << endl << endl;
        }
    }
};

//int main(int argc, const char * argv[]) {
//    Solution solution;
////    putchar('u');
//    solution.doubleSum();
//    return 0;
//}
