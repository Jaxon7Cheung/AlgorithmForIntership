//
//  main.cpp
//  lt&al
//
//  Created by 张旭洋 on 2024/10/7.
//

#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || p == root || q == root) return root;
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        if (!left && !right) return nullptr;
        if (!left) return right;
        if (!right) return left;
        // if (left && right) return root;
        return root;
    }
};
 
int main(void) {
    TreeNode* root = new TreeNode(0);
    root->left = new TreeNode(11);root->right = new TreeNode(22);
    
    root->left->left = new TreeNode(3);root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(5);root->right->right = new TreeNode(6);
    
    root->left->right->left = new TreeNode(7);root->left->right->right = new TreeNode(8);
    
    TreeNode* p = root->left->left; // 4
    TreeNode* q = root->left->right->right; // 9
    Solution solution;
    TreeNode* ans = solution.lowestCommonAncestor(root, p, q);
    cout << ans->val << endl; // 11
    
    TreeNode* p1 = root->left->right->left; // 8
    TreeNode* q1 = root->right->left; // 6
    TreeNode* ans1 = solution.lowestCommonAncestor(root, p1, q1);
    cout << ans1->val << endl; // 0
    

    return 0;
}
