import Foundation

// MARK: - 链表节点定义
/// Swift风格的单链表节点，使用class支持引用语义
class ListNode {
    var val: Int
    var next: ListNode?
    
    init() {
        self.val = 0
        self.next = nil
    }
    
    init(_ val: Int) {
        self.val = val
        self.next = nil
    }
    
    init(_ val: Int, _ next: ListNode?) {
        self.val = val
        self.next = next
    }
}

// MARK: - ListNode扩展：Swift语法糖
extension ListNode: CustomStringConvertible {
    /// 自定义描述，方便调试
    var description: String {
        var result = "[\(val)"
        var current = next
        while let node = current {
            result += " -> \(node.val)"
            current = node.next
        }
        result += "]"
        return result
    }
    
    /// 计算属性：判断是否为尾节点
    var isLast: Bool {
        return next == nil
    }
    
    /// 获取链表长度（从当前节点开始）
    var length: Int {
        var count = 1
        var current = next
        while current != nil {
            count += 1
            current = current?.next
        }
        return count
    }
}

// MARK: - 二叉树节点定义
/// Swift风格的二叉树节点
class TreeNode {
    var val: Int
    var left: TreeNode?
    var right: TreeNode?
    
    init() {
        self.val = 0
        self.left = nil
        self.right = nil
    }
    
    init(_ val: Int) {
        self.val = val
        self.left = nil
        self.right = nil
    }
    
    init(_ val: Int, _ left: TreeNode?, _ right: TreeNode?) {
        self.val = val
        self.left = left
        self.right = right
    }
}

// MARK: - TreeNode扩展：Swift语法糖
extension TreeNode: CustomStringConvertible {
    /// 层序遍历描述
    var description: String {
        var result: [String] = []
        var queue: [TreeNode?] = [self]
        
        while !queue.isEmpty {
            let node = queue.removeFirst()
            if let node = node {
                result.append("\(node.val)")
                queue.append(node.left)
                queue.append(node.right)
            } else {
                result.append("null")
            }
        }
        
        // 移除尾部的null
        while result.last == "null" {
            result.removeLast()
        }
        
        return "[\(result.joined(separator: ", "))]"
    }
    
    /// 计算属性：判断是否为叶子节点
    var isLeaf: Bool {
        return left == nil && right == nil
    }
    
    /// 计算属性：获取树的高度
    var height: Int {
        let leftHeight = left?.height ?? 0
        let rightHeight = right?.height ?? 0
        return max(leftHeight, rightHeight) + 1
    }
}

// MARK: - 通用协议定义
/// 可比较的节点协议
protocol ComparableNode: Comparable {
    var val: Int { get }
}

extension ListNode: ComparableNode {
    static func < (lhs: ListNode, rhs: ListNode) -> Bool {
        return lhs.val < rhs.val
    }
    
    static func == (lhs: ListNode, rhs: ListNode) -> Bool {
        return lhs.val == rhs.val
    }
}

extension TreeNode: ComparableNode {
    static func < (lhs: TreeNode, rhs: TreeNode) -> Bool {
        return lhs.val < rhs.val
    }
    
    static func == (lhs: TreeNode, rhs: TreeNode) -> Bool {
        return lhs.val == rhs.val
    }
}

// MARK: - 便利构造器
extension Array where Element == Int {
    /// 从数组创建链表
    func toListNode() -> ListNode? {
        guard !isEmpty else { return nil }
        
        let dummy = ListNode()
        var current = dummy
        
        for value in self {
            current.next = ListNode(value)
            current = current.next!
        }
        
        return dummy.next
    }
}

extension ListNode {
    /// 从链表转换为数组
    func toArray() -> [Int] {
        var result: [Int] = []
        var current: ListNode? = self
        
        while let node = current {
            result.append(node.val)
            current = node.next
        }
        
        return result
    }
}

// MARK: - 二叉树构造器
extension Array where Element == Int? {
    /// 从数组创建二叉树（层序遍历方式）
    func toTreeNode() -> TreeNode? {
        guard !isEmpty, let rootVal = first, let rootVal = rootVal else { return nil }
        
        let root = TreeNode(rootVal)
        var queue: [TreeNode] = [root]
        var index = 1
        
        while !queue.isEmpty && index < count {
            let node = queue.removeFirst()
            
            // 处理左子节点
            if index < count, let leftVal = self[index] {
                node.left = TreeNode(leftVal)
                queue.append(node.left!)
            }
            index += 1
            
            // 处理右子节点
            if index < count, let rightVal = self[index] {
                node.right = TreeNode(rightVal)
                queue.append(node.right!)
            }
            index += 1
        }
        
        return root
    }
}
