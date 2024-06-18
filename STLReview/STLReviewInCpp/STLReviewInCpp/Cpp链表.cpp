//
//  Cpp链表.cpp
//  STLReviewInCpp
//
//  Created by 张旭洋 on 2024/6/19.
//

#include <iostream>
using namespace std;
 
typedef struct ListNode {
    int val;
    struct ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
} ListNode;
 
inline void insertNodeAtTail(ListNode* dummyNode, int val) {
    ListNode* move = dummyNode;
    while (move->next) {
        move = move->next;
    }
    ListNode* newNode = new ListNode(val);
    move->next = newNode;
}

inline bool insertNodeAtIndex(ListNode* dummyNode, int index, int val) {
    if (index <= 0) return false;
    ListNode* move = dummyNode;
    while (--index) {
        move = move->next;
        if (!move) return false;
    }
    ListNode* newNode = new ListNode(val);
    newNode->next = move->next;
    move->next = newNode;
    return true;
}

inline bool deleteNodeAtIndex(ListNode* dummyNode, int index) {
    if (index <= 0) return false;
    ListNode* move = dummyNode;
    while (--index) {
        move = move->next;
        if (!move) return false;
    }
    if (!move->next) return false;
    ListNode* tmp = move->next;
    move->next = move->next->next;
    delete tmp;
    return true;
}
 
inline void printList(ListNode* dummyNode) {
     ListNode* move = dummyNode;
     
     while (move->next) {
         move = move->next;
         cout << move->val;
         if (move->next) {
             cout << ' ';
         } else {
             cout << endl;
         }
     }
 }
 
inline bool printNode(ListNode* dummyNode, int index) {
    if (index <= 0) return false;
    ListNode* move = dummyNode;
    while (index--) {
        move = move->next;
        if (!move) return false;
    }
    cout << move->val << endl;
    return true;
}



class Solution {
public:
    
};
