/*
 * @lc app=leetcode.cn id=146 lang=cpp
 *
 * [146] LRU 缓存
 */

// @lc code=start
struct DNode {
    int val;
    DNode* pre;
    DNode* next;

    int key;
    DNode() : key(-1), val(-1), pre(nullptr), next(nullptr) {}
    DNode(int _key, int _val) : key(_key), val(_val), pre(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    int limit;
    unordered_map<int, DNode*> cache;
    DNode* head;
    DNode* tail;

    void deleteNode(int key) {
        DNode* node = cache[key];
        cache.erase(key);
        node->pre->next = node->next;
        node->next->pre = node->pre;
        delete node;
    }

    void addHeadNode(int key, int val) {
        DNode* node = new DNode(key, val);
        cache[key] = node;
        node->next = head->next;
        head->next->pre = node;
        node->pre = head;
        head->next = node;
    }

public:
    LRUCache(int capacity) {
        limit = capacity;
        head = new DNode();
        tail = new DNode();
        head->next = tail;
        tail->pre = head;
    }
    
    int get(int key) {
        if (!cache.count(key)) return -1;
        DNode* node = cache[key];
        int val = node->val;
        deleteNode(key);
        addHeadNode(key, val);
        return val;
    }
    
    void put(int key, int value) {
        if (cache.count(key)) {
            deleteNode(key);
            addHeadNode(key, value);
        } else {
            addHeadNode(key, value);
            if (cache.size() > limit) {
                deleteNode(tail->pre->key);
            }
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
// @lc code=end

