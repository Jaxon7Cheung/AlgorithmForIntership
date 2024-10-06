//
//  main.cpp
//  lt&al
//
//  Created by 张旭洋 on 2024/10/7.
//

#include <iostream>
#include <vector>
using namespace std;
 
// 递归方式构建大根堆(len是arr的长度，i是第一个非叶子节点的下标)
void heapify(vector<int> &arr, int n, int i) {
    int largest = i; // 初始化最大元素为根
    int left = 2 * i + 1; // 左子节点
    int right = 2 * i + 2;  // 右子节点
    // 如果左子节点大于根节点
    if (left < n && arr[left] > arr[largest])
        largest = left;
        
    // 如果右子节点大于目前的最大值
    if (right < n && arr[right] > arr[largest])
        largest = right;
        
    // 如果最大值不是根节点
    if (largest != i) {
        swap(arr[i], arr[largest]); // 交换根与最大值
        heapify(arr, n, largest);  // 递归地对受影响的子树进行heapify
    }
}
 
// 堆排序
void heapSort(vector<int> &arr, int n) {
    // 先使用下滤操作构建大根堆，O（N），从最后一个非叶子节点开始！
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // 逐个从堆中取出元素
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]); // 将当前根（最大值）移到数组末尾
        heapify(arr, i, 0); // 对剩余的堆进行heapify
    }
}
 
int main() {
    vector<int> arr = {8, 1, 14, 3, 21, 5, 7, 10};
    heapSort(arr, arr.size());
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << ' ';
    return 0;
}
