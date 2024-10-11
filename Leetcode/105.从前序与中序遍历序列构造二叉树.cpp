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



struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


 // 根->递归划分区间到每一个结点->递归调用向上建立树
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return solve(preorder, inorder, 0, preorder.size() - 1, 0, inorder.size() - 1);
    }

    TreeNode* solve(vector<int>& preorder, vector<int>& inorder, int preS, int preE, int inS, int inE) {
        // 递归终止条件：子树区间为0
        if (preS > preE) return nullptr;
        // if (inS > inE) return nullptr;

        int rootVal = preorder[preS];
        TreeNode* root = new TreeNode(rootVal);
        // 树无重复元素，所以可以通过前序数组第一个元素确定
        // 中序数组中根结点的位置，进而确定左右子树的区间
        int rootIndex = -1;
        for (int i = inS; i <= inE; ++i) {
            if (inorder[i] == root->val) {
                rootIndex = i;
                break;
            }
        }
        int leftSize = rootIndex - inS;
        root->left = solve(preorder, inorder, preS + 1, preS + leftSize, inS, rootIndex - 1);
        root->right = solve(preorder, inorder, preS + 1 + leftSize, preE, rootIndex + 1, inE);
        return root;
    }
};

void preOrder(TreeNode* root) {
    if (!root) return;
    cout << root->val << ' ';
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(TreeNode* root) {
    if (!root) return;
    inOrder(root->left);
    cout << root->val << ' ';
    inOrder(root->right);
}
 
int main() {
    vector<int> preorder = {3, 9, 20, 15, 7};
    vector<int> inorder = {9, 3, 15, 20, 7};
    
    Solution solution;
    
    TreeNode* root = solution.buildTree(preorder, inorder);
    preOrder(root);cout << endl;
    inOrder(root);

    return 0;
}
