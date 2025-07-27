//
//  main.cpp
//  lt&al
//
//  Created by 张旭洋 on 2024/10/7.
//

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if (!root) return ans;

        queue<TreeNode *> queue;
        queue.push(root);
        while (!queue.empty()) {
            int n = queue.size();
            vector<int> tmp;
            for (int i = 0; i < n; ++i) {
                TreeNode* node = queue.front();
                tmp.push_back(node->val);
                queue.pop();

                if (node->left) queue.push(node->left);
                if (node->right) queue.push(node->right);
            }
            ans.push_back(tmp);
        }
        return ans;
    }
};

 
int main() {
    TreeNode* node5 = new TreeNode(4);TreeNode* node4 = new TreeNode(5);
    TreeNode* node3 = new TreeNode(3, nullptr, node5);TreeNode* node2 = new TreeNode(2, nullptr, node4);
    TreeNode* node1 = new TreeNode(1, node2, node3);
    
    Solution solution;
    vector<vector<int>> numss = solution.levelOrder(node1);
    for (vector<int> nums : numss) {
        for (int num : nums) cout << num << ' ';
        cout << '|';
    }
    
    return 0;
}
