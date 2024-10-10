//
//  main.cpp
//  lt&al
//
//  Created by 张旭洋 on 2024/10/7.
//

#include <iostream>
#include <vector>
#include <stack>
using namespace std;


// 从宽度的角度

// 时间：O(2n)=O(n)每个下标最多只会入栈和出栈各一次、空间：O(n)栈的大小不会超过n
class Solution {
public:
    // 单调栈
    int trap(vector<int>& height) {
        // 维护一个存储数组下标单调栈
        // 栈底到栈顶对应的数组元素依次递减
        stack<int> stk;
        
        int ans = 0, n = height.size();
        for (int i = 0; i < n; ++i) { //结束条件
            while (!stk.empty()) {
                if (height[i] > height[stk.top()]) {
                    int top = stk.top();
                    stk.pop();

                    // 栈为空，去入栈（也处理起始条件）
                    if (stk.empty()) break;

                    int left = stk.top();
                    int curWidth = i - left - 1;
                    int curHeight = min(height[i], height[left]) - height[top];
                    ans += curHeight * curWidth;
                } else {
                    // height[i] ≤ height[top]就去将i入栈
                    break;
                }
            }
            stk.push(i);
        }
        return ans;
    }
};


// 从高度的角度

// 时间：O(3n)=O(n)计算数组 leftMax 和 rightMax 的元素值各需要遍历数组 height 一次，计算能接的雨水总量还需要遍历一次、空间：O(2n)=O(n)需要创建两个长度为 n 的数组 leftMax 和 rightMax
//class Solution {
//public:
//    // 动态规划
//    int trap(vector<int>& height) {
//        int n = height.size();
//
//        // 下标 i 及其左边的位置中，height 的最大高度
//        vector<int> leftMax(n, 0);
//        leftMax[0] = height[0];
//        for (int i = 1; i < n; ++i) {
//            leftMax[i] = max(height[i], leftMax[i - 1]);
//        }
//
//        // 下标 i 及其右边的位置中，height 的最大高度
//        vector<int> rightMax(n, 0);
//        rightMax[n - 1] = height[n - 1];
//        for (int i = n - 2; i >= 0; --i) {
//            rightMax[i] = max(height[i], rightMax[i + 1]);
//        }
//
//        int ans = 0;
//        // 下标 i 处能接的雨水量等于下标 i 处的水能到达的最大高度减去 height[i
//        for (int i = 0; i < n; ++i) {
//            ans += (min(leftMax[i], rightMax[i]) - height[i]);
//        }
//
//        return ans;
//    }
//};

// 时间：O(n)两个指针的移动总次数不超过n、空间：O(1)只需要使用常数的额外空间
//class Solution {
//public:
//    // 双指针
//    // 下标 i 处能接的雨水量由 leftMax[i] 和 rightMax[i] 中的最小值决定。由于数组 leftMax 是从左往右计算，数组 rightMax 是从右往左计算，因此可以使用双指针和两个变量代替两个数组
//    int trap(vector<int>& height) {
//        int left = 0, right = height.size() - 1;
//        int leftMax = 0, rightMax = 0;
//        int ans = 0;
//        while (left < right) {
//            if (height[left] < height[right]) {
//                // 必有 leftMax < rightMax
//
//                // 更新最大值
//                leftMax = max(leftMax, height[left]);
//                ans += leftMax - height[left];
//                left++;
//            } else {
//                // 必有 leftMax ≥ rightMax
//
//                // 更新最大值
//                rightMax = max(rightMax, height[right]);
//                ans += rightMax - height[right];
//                right--;
//            }
//        }
//        return ans;
//    }
//};
 
int main() {
    vector<int> nums = {4, 2, 0, 3, 2, 5};
    vector<int> numss = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    
    Solution solution;
    cout << solution.trap(nums) << endl;
    cout << solution.trap(numss) << endl;
    
    return 0;
}
