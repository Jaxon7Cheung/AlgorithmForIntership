//
//  main.cpp
//  lt&al
//
//  Created by 张旭洋 on 2024/10/7.
//

#include <iostream>
using namespace std;

// 开n次方（支持负数、小数），有精度要求
long double nth_root(long double num, int n) {
    if (num < 0 && n % 2 == 0) return -1; // 偶数次根不能是负数

    if (!num) return 0; // 0 的 n 次方根是 0

    long double left = (num < 1) ? num : 1;
    long double right = (num < 1) ? 1 : num;

    long double ans = 0;
    const long double precision = 1e-13; // 精度

    while (right - left > precision) {
        long double mid = left + (right - left) / 2;
        long double mid_power = 1;
        for (int i = 1; i <= n; ++i) mid_power *= mid;

        if (mid_power == num) {
            return mid;
        } else if (mid_power < num) {
            left = mid; // mid 可能是答案
            ans = mid; // 更新答案
        } else {
            right = mid; // mid 不是答案
//            ans = mid; // 更新答案
        }
    }
    
    return ans; // 返回近似值
}

int main(void) {
    cout << nth_root(-512, 9) << endl;
    cout << nth_root(8, 2) << endl;
    cout << nth_root(27, 3) << endl;
    cout << nth_root(0.04, 2) << endl;

    return 0;
}
