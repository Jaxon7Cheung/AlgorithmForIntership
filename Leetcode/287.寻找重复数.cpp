//
//  main.cpp
//  lt&al
//
//  Created by 张旭洋 on 2024/10/7.
//

#include <iostream>
#include <vector>
using namespace std;

// 快慢指针
class Solution {
public:
    // 要求空间O(1)，不考虑Hash

    // 根据这个数组的特点，数组当作一个链表来看，数组的下标就是指向元素的指针，把数组的元素也看作指针。如 0 是指针，指向 nums[0]，而 nums[0] 也是指针，指向 nums[nums[0]]
    // 强调：假设只有一个重复的整数，所以说必有环，返回入环点（2个指针指向同一个结点的位置）即可
    int findDuplicate(vector<int>& nums) {
        int slow = 0, fast = 0;
        while (true) {
            slow = nums[slow];
            fast = nums[nums[fast]];
            if (slow == fast) break;
        }

        fast = 0;
        while (fast != slow) {
            slow = nums[slow];
            fast = nums[fast];
        }

        return slow;

    }
};

// 二分 + 内层for循环 = O(NlogN)
// class Solution {
// public:
//     int findDuplicate(vector<int>& nums) {
//         // 1 ... n -> (n + 1)个，且题目已经假设只有一个重复的数
//         int n = nums.size() - 1;
//        
//         int left = 1, right = n;
//         while (left < right) {
//             // 浮点数赋给int，类型自动转换过程就会舍弃掉小数部分
//             // 相当于向下取整
//             int mid = left + (right - left) / 2;
//            
//            // nums中小于等于mid的元素个数
//            int cnt = 0;
//            for (int num : nums) {
//                // if (num <= mid) {
//                //     cnt++;
//                // }
//                cnt += (num <= mid);
//            }
//
//             if (cnt > mid) {
//                 right = mid;
//             } else {
//                 left = mid + 1;
//             }
//         }
//
//         return left;
//     }
// };

// 暴力超时
// class Solution {
// public:
//     int findDuplicate(vector<int>& nums) {
//         int n = nums.size();
//         for (int i = 0; i < n - 1; ++i) {
//             for (int j = i + 1; j < n; ++j) {
//                 int num = nums[j];
//                 if (nums[i] == num) return num;
//             }
//         }
//         return -1;
//     }
// };

 
int main() {
    vector<int> nums = {1, 3, 4, 2, 2};
    
    Solution solution;
    cout << solution.findDuplicate(nums) << endl;
    
    return 0;
}
