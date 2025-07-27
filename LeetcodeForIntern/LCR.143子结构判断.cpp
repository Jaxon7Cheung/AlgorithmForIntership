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
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    // 判断以某node结点为根的树是否与B为根的树相似
    bool solve(TreeNode* node, TreeNode* B) {
        if (!node && !B) return true;
        if (node && !B) return true;
        if (!node && B) return false;
        // 都不为空就判断值是否相等
        if (node->val != B->val) return false;

        // if (!B) return true;
        // if (!node || (node->val != B->val)) return false;

        return solve(node->left, B->left) && solve(node->right, B->right);
    }
public:
    // 遍历A的每个结点，如果有哪个结点为根的树包含B，
    bool isSubStructure(TreeNode* A, TreeNode* B) {
        if (!A || !B) return false;
        if (solve(A, B)) return true;
        // rootA不相似，就往下遍历
        return isSubStructure(A->left, B) || isSubStructure(A->right, B);
        // return solve(A, B);
    }
};
 
int main(void) {
//    A[4,2,3,4,5,6,7,8,9]
//    B[4,8,9]
    TreeNode* A = new TreeNode(4);
    A->left = new TreeNode(2);A->right = new TreeNode(3);
    A->left->left = new TreeNode(4);A->left->right = new TreeNode(5);
    A->right->left = new TreeNode(6);A->right->right = new TreeNode(7);
    A->left->left->left = new TreeNode(8);A->left->left->right = new TreeNode(9);
    
    TreeNode* B = new TreeNode(4);
    B->left = new TreeNode(8);B->right = new TreeNode(9);
    
    Solution solution;
    cout << solution.isSubStructure(A, B) << endl;

    return 0;
}
