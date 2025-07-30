/*
 * @lc app=leetcode.cn id=112 lang=cpp
 *
 * [112] 路径总和
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    // 从targetSum开始，不断地减去路径上的节点值，如果走到叶子节点发现 targetSum == 0，就说明我们找到了一条符合题目要求的路径
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (!root) return false;
        targetSum -= root->val;

        // 🍃叶子
        if (!root->left && !root->right) {
            return targetSum == 0;
        }

        return hasPathSum(root->left, targetSum)
            || hasPathSum(root->right, targetSum);;
    }
};
// @lc code=end

