import Foundation

// MARK: - LeetCode 25: K个一组翻转链表
/// Swift风格实现，使用optional chaining和函数式编程

class LC25_ReverseKGroup {
    
    /// K个一组翻转链表的主函数
    func reverseKGroup(_ head: ListNode?, _ k: Int) -> ListNode? {
        guard let head = head, k > 1 else { return head }
        
        let dummy = ListNode(0)
        dummy.next = head
        var pre: ListNode? = dummy
        var current = head
        
        while current != nil {
            // 检查剩余节点是否足够k个
            var temp = current
            for _ in 1..<k {
                temp = temp?.next
                guard temp != nil else { return dummy.next }
            }
            
            // 保存下一组的起点
            let nextGroupStart = temp?.next
            temp?.next = nil
            
            // 反转当前组
            let groupHead = pre?.next
            pre?.next = reverseLinkedList(groupHead)
            groupHead?.next = nextGroupStart
            
            // 移动指针到下一组
            pre = groupHead
            current = nextGroupStart
        }
        
        return dummy.next
    }
    
    /// 反转链表的辅助函数
    private func reverseLinkedList(_ head: ListNode?) -> ListNode? {
        var prev: ListNode? = nil
        var current = head
        
        while let node = current {
            let next = node.next
            node.next = prev
            prev = node
            current = next
        }
        
        return prev
    }
    
    /// 函数式风格的解法（使用Swift高阶函数）
    func reverseKGroupFunctional(_ head: ListNode?, _ k: Int) -> ListNode? {
        guard let head = head, k > 1 else { return head }
        
        // 将链表转换为数组
        let values = head.toArray()
        
        // 分组并反转
        let reversedValues = values.chunked(into: k)
            .map { chunk in
                chunk.count == k ? chunk.reversed() : chunk
            }
            .flatMap { $0 }
        
        // 重新构建链表
        return reversedValues.toListNode()
    }
    
    /// 演示函数
    static func runExample() {
        print("=== LeetCode 25: K个一组翻转链表 ===")
        
        let solution = LC25_ReverseKGroup()
        
        // 测试用例1: [1,2,3,4,5], k = 2
        let test1 = [1, 2, 3, 4, 5].toListNode()
        let result1 = solution.reverseKGroup(test1, 2)
        print("输入: [1,2,3,4,5], k=2")
        print("输出: \(result1?.toArray() ?? [])")
        
        // 测试用例2: [1,2,3,4,5], k = 3
        let test2 = [1, 2, 3, 4, 5].toListNode()
        let result2 = solution.reverseKGroup(test2, 3)
        print("\n输入: [1,2,3,4,5], k=3")
        print("输出: \(result2?.toArray() ?? [])")
        
        // 函数式风格测试
        let test3 = [1, 2, 3, 4, 5, 6].toListNode()
        let result3 = solution.reverseKGroupFunctional(test3, 3)
        print("\n函数式解法 - 输入: [1,2,3,4,5,6], k=3")
        print("输出: \(result3?.toArray() ?? [])")
    }
}

// MARK: - LeetCode 21: 合并两个有序链表
class LC21_MergeTwoSortedLists {
    
    /// 递归解法 - Swift风格
    func mergeTwoLists(_ list1: ListNode?, _ list2: ListNode?) -> ListNode? {
        guard let l1 = list1 else { return list2 }
        guard let l2 = list2 else { return list1 }
        
        if l1.val <= l2.val {
            l1.next = mergeTwoLists(l1.next, l2)
            return l1
        } else {
            l2.next = mergeTwoLists(l1, l2.next)
            return l2
        }
    }
    
    /// 迭代解法 - 使用guard语句
    func mergeTwoListsIterative(_ list1: ListNode?, _ list2: ListNode?) -> ListNode? {
        let dummy = ListNode(0)
        var current = dummy
        var l1 = list1
        var l2 = list2
        
        while let node1 = l1, let node2 = l2 {
            if node1.val <= node2.val {
                current.next = node1
                l1 = node1.next
            } else {
                current.next = node2
                l2 = node2.next
            }
            current = current.next!
        }
        
        // 使用nil-coalescing操作符
        current.next = l1 ?? l2
        
        return dummy.next
    }
    
    /// 函数式解法
    func mergeTwoListsFunctional(_ list1: ListNode?, _ list2: ListNode?) -> ListNode? {
        let array1 = list1?.toArray() ?? []
        let array2 = list2?.toArray() ?? []
        
        return (array1 + array2).sorted().toListNode()
    }
    
    static func runExample() {
        print("\n=== LeetCode 21: 合并两个有序链表 ===")
        
        let solution = LC21_MergeTwoSortedLists()
        
        let list1 = [1, 2, 4].toListNode()
        let list2 = [1, 3, 4].toListNode()
        
        let result = solution.mergeTwoLists(list1, list2)
        print("输入: list1=[1,2,4], list2=[1,3,4]")
        print("输出: \(result?.toArray() ?? [])")
    }
}

// MARK: - LeetCode 146: LRU缓存
class LRUCache {
    
    // 双向链表节点
    private class DListNode {
        var key: Int
        var value: Int
        var prev: DListNode?
        var next: DListNode?
        
        init(_ key: Int = 0, _ value: Int = 0) {
            self.key = key
            self.value = value
        }
    }
    
    private let capacity: Int
    private var cache: [Int: DListNode] = [:]
    private let head = DListNode()  // 虚拟头节点
    private let tail = DListNode()  // 虚拟尾节点
    
    init(_ capacity: Int) {
        self.capacity = capacity
        head.next = tail
        tail.prev = head
    }
    
    func get(_ key: Int) -> Int {
        guard let node = cache[key] else { return -1 }
        
        // 移动到头部（最近使用）
        moveToHead(node)
        return node.value
    }
    
    func put(_ key: Int, _ value: Int) {
        if let existingNode = cache[key] {
            // 更新现有节点
            existingNode.value = value
            moveToHead(existingNode)
        } else {
            // 添加新节点
            let newNode = DListNode(key, value)
            cache[key] = newNode
            addToHead(newNode)
            
            // 检查容量
            if cache.count > capacity {
                guard let removed = removeTail() else { return }
                cache.removeValue(forKey: removed.key)
            }
        }
    }
    
    // MARK: - 私有辅助方法
    private func addToHead(_ node: DListNode) {
        node.prev = head
        node.next = head.next
        head.next?.prev = node
        head.next = node
    }
    
    private func removeNode(_ node: DListNode) {
        node.prev?.next = node.next
        node.next?.prev = node.prev
    }
    
    private func moveToHead(_ node: DListNode) {
        removeNode(node)
        addToHead(node)
    }
    
    private func removeTail() -> DListNode? {
        guard let lastNode = tail.prev, lastNode !== head else { return nil }
        removeNode(lastNode)
        return lastNode
    }
}

// MARK: - Array扩展：分组方法
extension Array {
    /// 将数组按指定大小分组
    func chunked(into size: Int) -> [[Element]] {
        return stride(from: 0, to: count, by: size).map {
            Array(self[$0..<Swift.min($0 + size, count)])
        }
    }
}

// MARK: - LeetCode算法演示
struct LeetCodeBasicExamples {
    static func runAll() {
        print("🚀 LeetCode基础算法Swift实现\n")
        
        LC25_ReverseKGroup.runExample()
        LC21_MergeTwoSortedLists.runExample()
        
        // LRU缓存演示
        print("\n=== LeetCode 146: LRU缓存 ===")
        let lru = LRUCache(2)
        lru.put(1, 1)
        lru.put(2, 2)
        print("get(1): \(lru.get(1))")  // 返回 1
        lru.put(3, 3)  // 该操作会使得关键字 2 作废
        print("get(2): \(lru.get(2))")  // 返回 -1 (未找到)
        lru.put(4, 4)  // 该操作会使得关键字 1 作废
        print("get(1): \(lru.get(1))")  // 返回 -1 (未找到)
        print("get(3): \(lru.get(3))")  // 返回 3
        print("get(4): \(lru.get(4))")  // 返回 4
    }
}
