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
        // 出口条件
        // 只要当前根节点是p和q中的任意一个，就返回（因为不能比这个更深了，再深p和q中的一个就没了）
        if (!root || p == root || q == root) return root;

        // 根节点不是p和q中的任意一个，递归遍历在左右子树中找p,q
        TreeNode* leftRet = lowestCommonAncestor(root->left, p, q);
        TreeNode* rightRet = lowestCommonAncestor(root->right, p, q);

        // 到上一层进行回溯，当节点p,q在节点root的异侧时，当前root即为最近公共祖先

        // 返回结点都为空，p,q都不在root的左/右子树中
        if (!leftRet && !rightRet) return nullptr; // 可注释掉合并
        // 返回的只有左结点为空，返回右子树结果
        // p/q在root的右子树中，返回的是p/q
        // p,q都在root的右子树中，返回的是最近公共祖先
        if (!leftRet) return rightRet;
        // 返回的只有右结点为空，返回左子树结果
        // p/q在root的左子树中，返回的是p/q
        // p,q都在root的左子树中，返回的是最近公共祖先
        if (!rightRet) return leftRet;

        // 同时不为空，就说明p,q在当前root的异侧，root即为最近公共祖先
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
