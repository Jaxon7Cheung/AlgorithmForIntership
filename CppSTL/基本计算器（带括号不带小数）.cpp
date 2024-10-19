//
//  main.cpp
//  lt&al
//
//  Created by 张旭洋 on 2024/10/7.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
using namespace std;

typedef struct Node {
    int val;
    char ope;
    bool isOpe; // 判断是否是符号方便后缀的计算，因为计算后缀的栈只存数字
} Node;

class Solution {
private:
    // 后缀用队列存起来方便用栈计算
    stack<int> calStk;
    queue<Node> q;
    // 符号栈
    stack<Node> stk;
    

    // 中缀转后缀
    // 哈希map用于判断符号优先级
    queue<Node> inToPost(string s, unordered_map<char, int> map) {
        int i = 0;
        int n = s.size();

        // 处理一元运算 "-(2 +3)"
        char pre = '0';

        while (i < n) {
            char ch = s[i];
            Node cur;
            cur.isOpe = true;
            if (ch == ' ') {
                i++;
                continue;
            }
            if (ch == '(') {
                pre = '(';
                cur.ope = '(';
                stk.push(cur);
                i++;
            } else if (ch == ')') {
                pre = ')';
                while (!stk.empty() && stk.top().ope != '(') {
                    q.push(stk.top());
                    stk.pop();
                }
                // 这会儿是左括号，也要出栈
                stk.pop();
                i++;
            } else if (ch >= '0' && ch <= '9') {
                pre = '1';

                int num = 0;
                while (i < n && (s[i] >= '0' && s[i] <= '9')) {
                    num = num * 10 + (s[i] - '0');
                    i++;
                }
                cur.val = num;
                cur.isOpe = false;
                q.push(cur);
            } else {
                // 符号

                // 处理一元运算 "-(2 +3)"
                if (pre == '0' || pre == '(') {
                    Node node;
                    node.val = 0;
                    node.isOpe = false;
                    q.push(node);
                }

                while (!stk.empty() && map[ch] <= map[stk.top().ope]) {
                    q.push(stk.top());
                    stk.pop();
                }
                cur.ope = ch;
                stk.push(cur);
                i++;
            }
            // i++;
        }

        // 符号栈的符号入栈
        while (!stk.empty()) {
            q.push(stk.top());
            stk.pop();
        }
        return q;
    }

    // 计算后缀
    int calculatePost(string s) {
        // 哈希map用于判断符号优先级
        unordered_map<char, int> map = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'(', 0}};
        queue<Node> q = inToPost(s, map);

        while (!q.empty()) {
            Node cur = q.front();
            q.pop();
            if (!cur.isOpe) {
                calStk.push(cur.val);
            } else {
                int num2 = calStk.top();
                calStk.pop();
                int num1 = calStk.top();
                calStk.pop();

                int tmp;
                char ope;
                ope = cur.ope;
                if (ope == '+') {
                    tmp = num1 + num2;
                } else if (ope == '-') {
                    tmp = num1 - num2;
                } else if (ope == '*') {
                    tmp = num1 * num2;
                } else if (ope == '/') {
                    tmp = num1 / num2;
                }
                calStk.push(tmp);
            }
        }
        return calStk.top();
    }

public:
    int calculate(string s) {
        return calculatePost(s);
    }
};
 
int main(void) {
    string s = "-1 +  (-(4+5+2)*3) + 6/ 2";
//    string s = "1+4+5+2*3+6/2";
//    string s = "1+6";
    
    Solution solution;
    cout << solution.calculate(s) << endl;
    

    return 0;
}
