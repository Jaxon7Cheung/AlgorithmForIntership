//
//  main.cpp
//  lt&al
//
//  Created by 张旭洋 on 2024/10/7.
//

#include <iostream>
using namespace std;

// 开方（非负整数）
int sqrtt(int num) {
    if (num < 0) return -1;
    if (!num || num == 1) return num;
    int left = 1;
    int right = num;
    int ans = 0;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (mid * mid == num) return mid;
        
        if (mid * mid < num) {
            left = mid + 1;
            ans = mid;
        } else {
            right = mid - 1;
        }
    }
    return ans;
}
 
int main(void) {
    cout << sqrtt(81) << endl;
    cout << sqrtt(16) << endl;
    cout << sqrtt(8) << endl;
    

    return 0;
}
