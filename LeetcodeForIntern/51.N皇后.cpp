//
//  main.cpp
//  lt&al
//
//  Created by 张旭洋 on 2024/10/7.
//

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
private:
    vector<vector<int>> result;
    vector<int> path; // 记录皇后在棋盘中的位置

    unordered_set<int> col; // 判断某行下某列的其他位置是否有皇后
    unordered_set<int> pos; // 判断某行下正斜线的其他位置是否有皇后，i-j相等
    unordered_set<int> neg; // 判断某行下反斜线的其他位置是否有皇后，i+j相等

public:
    // 回溯
    vector<vector<string>> solveNQueens(int n) {
        DFS(0, n);
        vector<vector<string>> ans(result.size(), vector<string>(n, string(n, '.')));
        
        for (int i = 0; i < result.size(); ++i) {
            for (int j = 0; j < result[0].size(); ++j) {
                ans[i][j][result[i][j]] = 'Q';
            }
        }
        return ans;
    }

    // 回溯通常采用深搜来遍历每一种可能的结果
    // 递归搜索过程中一直去维护正确的Path数组
    // 其实搜索皇后的位置，可以抽象为一棵树（N叉树）
    void DFS(int row, int n) {
         if (row == n) {
            // 搜索到最后一行Path也就维护完成了
            result.push_back(path);
            return;
         }

         // 回溯就是去尝试每一行的皇后位置
         
         
         for (int j = 0; j < n; ++j) {
            if (col.count(j) || pos.count(j - row) || neg.count(j + row)) {
                continue;
            }

            path.push_back(j);
            col.insert(j);
            pos.insert(j - row);
            neg.insert(j + row);
            DFS(row + 1, n);
            
            // 如果不能满足条件皇后放不到这个位置
            // 就恢复到上一行的状态去找上一行的其他列继续进行搜索
            // 如果无解最终pop数组元素就会恢复到最初状态，Path数组也就为空了，N = 3时无解
            path.pop_back();
            col.erase(j);
            pos.erase(j - row);
            neg.erase(j + row);
         }

        //  result.push_back(path);
    }
};

void printAns(vector<vector<string>> ans, int n) {
    for (vector<string> ansN : ans) {
        for (string s : ansN) {
            cout << s << endl;
        }
        cout << '#' << endl;
    }
    printf("%dx%d", n, n);
    cout << "有" << ans.size() << "种摆盘方式" << endl;
}
// [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
 
int main(void) {

    Solution solution;
//    printAns(solution.solveNQueens(1), 1);
//    printAns(solution.solveNQueens(2), 2); // 无解
//    printAns(solution.solveNQueens(3), 3); // 无解
    printAns(solution.solveNQueens(4), 4);
//    printAns(solution.solveNQueens(5), 5);
    

    return 0;
}
