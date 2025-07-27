//
//  main.cpp
//  lt&al
//
//  Created by 张旭洋 on 2024/10/7.
//

#include <iostream>
#include <vector>
#include <stack>
using namespace std;


// 使用一个辅助栈，与元素栈同步插入与删除，用于存储与每个元素对应的最小值

/*
当一个元素要入栈时，我们取当前辅助栈的栈顶存储的最小值，与当前元素比较得出最小值，将这个最小值插入辅助栈中；

当一个元素要出栈时，我们把辅助栈的栈顶元素也一并弹出；

在任意一个时刻，栈内元素的最小值就存储在辅助栈的栈顶元素中。
 */

class MinStack {
private:
    stack<int> stk;
    stack<int> min_stk;

public:
    MinStack() {
        // 因为要比较大小，所以初始化辅助栈的底为INT_MAX
        min_stk.push(INT_MAX);
    }
    
    void push(int val) {
        int min_top = min_stk.top();

        // 哪个小，push哪个

        // if (min_top > val) {
        //     min_stk.push(val);
        // } else {
        //     min_stk.push(min_top);
        // }

        // int tmp = (min_top > val) ? val : min_top;
        // min_stk.push(tmp);

        min_stk.push(min(val, min_stk.top()));
        

        stk.push(val);
    }
    
    void pop() {
        stk.pop();
        min_stk.pop();
    }
    
    int top() {
        return stk.top();
    }
    
    int getMin() {
        return min_stk.top();
    }
};
 
int main() {
    MinStack minStack = *new MinStack();
    cout << "null" << ' ';minStack.push(-2);
    cout << "null" << ' ';minStack.push(0);
    cout << "null" << ' ';minStack.push(-3);
    cout << minStack.getMin() << ' ';   // --> 返回 -3.
    cout << "null" << ' ';minStack.pop();
    cout << minStack.top() << ' ';      // --> 返回 0.
    cout << minStack.getMin() << ' ';   // --> 返回 -2.
    return 0;
}
