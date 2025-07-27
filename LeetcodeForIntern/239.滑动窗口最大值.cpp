//
//  main.cpp
//  lt&al
//
//  Created by 张旭洋 on 2024/10/7.
//

#include <iostream>
#include <vector>
#include <deque>
using namespace std;


class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> ans;

        // 遍历数组时，维护一个单调递减双端队列
        deque<int> deque;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            // 有窗口元素大于队尾就出栈
            while (!deque.empty() && nums[i] > deque.back()) {
                deque.pop_back();
            }
            deque.push_back(nums[i]);

            // 跳出滑动窗口的值如果是队首（即上一个窗口的最大值），就pop出队列
            if (i >= k && nums[i - k] == deque.front()) deque.pop_front();

            if (i >= k - 1) ans.push_back(deque.front());
        }
        return ans;
    }
};

// class Solution {
// public:
//     vector<int> maxSlidingWindow(vector<int>& nums, int k) {
//         int n = nums.size();
//         vector<int> ans;

//         // 遍历数组时，维护一个单调递减双端队列
//         deque<int> deque;

//         int startFront = INT_MIN;
//         for (int i = 0; i < k; ++i) {
//             startFront = max(startFront, nums[i]);
//         }

//         deque.push_back(startFront);
//         ans.push_back(deque.front());

//         for (int i = k; i < n; ++i) {

//             int front = deque.front();
//             while (!deque.empty() && nums[i] >= front) {
//                 deque.pop_front();
//             }
//             deque.push_back(nums[i]);
//             ans.push_back(deque.front());

//             // if (i >= k && deque.front() == nums[i - k]) deque.pop_front();
//         }
//         return ans;
//     }
// };
 
int main() {
    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    
    Solution solution;
    vector<int> ans =  solution.maxSlidingWindow(nums, 3);
    for (int a : ans) {
        cout << a << ' ';
    }

    return 0;
}
