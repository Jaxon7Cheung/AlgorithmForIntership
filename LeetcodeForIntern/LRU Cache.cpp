//
//  main.cpp
//  lt&al
//
//  Created by 张旭洋 on 2024/10/6.
//

#include <iostream>
#include <unordered_map>
using namespace std;

// 双向链表
typedef struct DlinkNode {
    int key;
    int val;
    struct DlinkNode* next;
    struct DlinkNode* pre;
    DlinkNode() : key(-1), val(-1), next(nullptr), pre(nullptr) {}
    DlinkNode(int _key, int _val) : key(_key), val(_val), next(nullptr), pre(nullptr) {}
} DlinkNode;

class LRUCache {
private:
    int limit;
    unordered_map<int, DlinkNode*> cache; // 哈希表
    DlinkNode* head; // 哑结点方便操作指针
    DlinkNode* tail;

public:
    // 初始化操作
    LRUCache(int capacity) {
        limit = capacity;
        head = new DlinkNode();
        tail = new DlinkNode();
        head->next = tail;
        tail->pre = head;
    }
    
    int get(int key) {
        if (!cache.count(key)) return -1;
        DlinkNode* res = cache[key];
        int val = res->val;
        deleteNode(key);
        addHNode(key, val);  // 更新双向链表
        return val;
    }
    
    void put(int key, int value) {
        if (cache.count(key)) { // 缓存有key
            deleteNode(key);
            addHNode(key, value); // 正常更新
        } else {
            if (cache.size() == limit) { // 超过容量
                deleteNode(tail->pre->key); // 删除尾结点
                addHNode(key, value);
            } else {
                addHNode(key, value); // 没超过容量且无缓存，直接加入
            }
        }
    }
    
    // 头插结点，更新哈希表
    void addHNode(int key, int val) {
        if (cache.count(key)) return;
        DlinkNode* cur = new DlinkNode(key, val);
        cache[key] = cur;
        cur->next = head->next;
        head->next->pre = cur;
        head->next = cur;
        cur->pre = head;
    }
    
    // 删除指定结点
    void deleteNode(int key) {
        if (!cache.count(key)) return;
        DlinkNode* cur = cache[key];
        cache.erase(key);
        DlinkNode* front = cur->pre;
        DlinkNode* back = cur->next;
        front->next = back;
        back->pre = front;
        cur->next = nullptr;
        cur->pre = nullptr;
    }
};

int main(int argc, const char * argv[]) {
    LRUCache lRUCache = *new LRUCache(2);
    cout << "null" << endl;lRUCache.put(1, 1); // 缓存是 {1=1}
    cout << "null" << endl;lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
    cout << lRUCache.get(1) << endl;    // 返回 1
    cout << "null" << endl;lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
    cout << lRUCache.get(2) << endl;    // 返回 -1 (未找到)
    cout << "null" << endl;lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
    cout << lRUCache.get(1) << endl;    // 返回 -1 (未找到)
    cout << lRUCache.get(3) << endl;    // 返回 3
    cout << lRUCache.get(4) << endl;    // 返回 4
    return 0;
}
