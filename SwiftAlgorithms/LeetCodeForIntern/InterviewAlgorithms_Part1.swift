import Foundation

// MARK: - LeetCode 155: 最小栈
/// Swift风格的最小栈实现，使用多种解法

class MinStack {
    
    // MARK: - 解法1：辅助栈
    private var dataStack: [Int] = []
    private var minStack: [Int] = []
    
    init() {
        // Swift中不需要预设置最大值，使用可选类型处理空栈情况
    }
    
    func push(_ val: Int) {
        dataStack.append(val)
        
        // 使用nil-coalescing操作符简化最小值计算
        let currentMin = minStack.last ?? Int.max
        minStack.append(min(val, currentMin))
    }
    
    func pop() {
        guard !dataStack.isEmpty else { return }
        dataStack.removeLast()
        minStack.removeLast()
    }
    
    func top() -> Int {
        return dataStack.last ?? 0
    }
    
    func getMin() -> Int {
        return minStack.last ?? 0
    }
}

// MARK: - 优化版最小栈
/// 使用更少的空间存储最小值
class MinStackOptimized {
    
    private var stack: [Int] = []
    private var minValue: Int = 0
    
    func push(_ val: Int) {
        if stack.isEmpty {
            stack.append(0)
            minValue = val
        } else {
            // 存储与最小值的差值
            stack.append(val - minValue)
            if val < minValue {
                minValue = val
            }
        }
    }
    
    func pop() {
        guard let top = stack.popLast() else { return }
        
        if top < 0 {
            // 说明被pop的元素是最小值，需要恢复之前的最小值
            minValue = minValue - top
        }
    }
    
    func top() -> Int {
        guard let stackTop = stack.last else { return 0 }
        
        return stackTop < 0 ? minValue : minValue + stackTop
    }
    
    func getMin() -> Int {
        return minValue
    }
}

// MARK: - 泛型最小栈
/// 支持任意可比较类型的最小栈
class GenericMinStack<T: Comparable> {
    
    private var dataStack: [T] = []
    private var minStack: [T] = []
    
    var isEmpty: Bool {
        return dataStack.isEmpty
    }
    
    var count: Int {
        return dataStack.count
    }
    
    func push(_ element: T) {
        dataStack.append(element)
        
        if let currentMin = minStack.last {
            minStack.append(min(element, currentMin))
        } else {
            minStack.append(element)
        }
    }
    
    @discardableResult
    func pop() -> T? {
        guard !dataStack.isEmpty else { return nil }
        
        minStack.removeLast()
        return dataStack.removeLast()
    }
    
    func top() -> T? {
        return dataStack.last
    }
    
    func getMin() -> T? {
        return minStack.last
    }
    
    func peek() -> T? {
        return dataStack.last
    }
}

// MARK: - LeetCode 160: 相交链表
/// Swift风格的链表相交检测

class LC160_IntersectionLinkedList {
    
    /// 双指针解法 - 最优雅
    func getIntersectionNode(_ headA: ListNode?, _ headB: ListNode?) -> ListNode? {
        guard headA != nil && headB != nil else { return nil }
        
        var pA = headA
        var pB = headB
        
        // 当两个指针相遇时，要么在交点相遇，要么都是nil
        while pA !== pB {
            pA = (pA == nil) ? headB : pA?.next
            pB = (pB == nil) ? headA : pB?.next
        }
        
        return pA
    }
    
    /// 哈希表解法
    func getIntersectionNodeHashSet(_ headA: ListNode?, _ headB: ListNode?) -> ListNode? {
        guard let headA = headA, let headB = headB else { return nil }
        
        var visitedNodes = Set<ObjectIdentifier>()
        var current: ListNode? = headA
        
        // 遍历链表A，记录所有节点
        while let node = current {
            visitedNodes.insert(ObjectIdentifier(node))
            current = node.next
        }
        
        // 遍历链表B，检查是否有相同节点
        current = headB
        while let node = current {
            if visitedNodes.contains(ObjectIdentifier(node)) {
                return node
            }
            current = node.next
        }
        
        return nil
    }
    
    /// 差值解法
    func getIntersectionNodeDifference(_ headA: ListNode?, _ headB: ListNode?) -> ListNode? {
        guard let headA = headA, let headB = headB else { return nil }
        
        let lengthA = getLength(headA)
        let lengthB = getLength(headB)
        
        var pA: ListNode? = headA
        var pB: ListNode? = headB
        
        // 让较长的链表先走差值步
        if lengthA > lengthB {
            for _ in 0..<(lengthA - lengthB) {
                pA = pA?.next
            }
        } else {
            for _ in 0..<(lengthB - lengthA) {
                pB = pB?.next
            }
        }
        
        // 同时移动，直到相遇
        while pA != nil && pB != nil {
            if pA === pB {
                return pA
            }
            pA = pA?.next
            pB = pB?.next
        }
        
        return nil
    }
    
    private func getLength(_ head: ListNode) -> Int {
        var count = 0
        var current: ListNode? = head
        
        while current != nil {
            count += 1
            current = current?.next
        }
        
        return count
    }
    
    static func runExample() {
        print("=== LeetCode 160: 相交链表 ===")
        
        // 创建测试链表
        // A: 4 -> 1 -> 8 -> 4 -> 5
        // B: 5 -> 6 -> 1 -> 8 -> 4 -> 5
        // 相交点是 8
        
        let intersection = ListNode(8)
        intersection.next = ListNode(4)
        intersection.next?.next = ListNode(5)
        
        let headA = ListNode(4)
        headA.next = ListNode(1)
        headA.next?.next = intersection
        
        let headB = ListNode(5)
        headB.next = ListNode(6)
        headB.next?.next = ListNode(1)
        headB.next?.next?.next = intersection
        
        let solution = LC160_IntersectionLinkedList()
        
        let result1 = solution.getIntersectionNode(headA, headB)
        let result2 = solution.getIntersectionNodeHashSet(headA, headB)
        let result3 = solution.getIntersectionNodeDifference(headA, headB)
        
        print("链表A: \(headA.toArray())")
        print("链表B: \(headB.toArray())")
        print("双指针解法: \(result1?.val ?? -1)")
        print("哈希表解法: \(result2?.val ?? -1)")
        print("差值解法: \(result3?.val ?? -1)")
    }
}

// MARK: - LeetCode 42: 接雨水
class LC42_TrappingRainWater {
    
    /// 双指针解法 - 最优时空复杂度
    func trap(_ height: [Int]) -> Int {
        guard height.count > 2 else { return 0 }
        
        var left = 0
        var right = height.count - 1
        var leftMax = 0
        var rightMax = 0
        var result = 0
        
        while left < right {
            if height[left] < height[right] {
                if height[left] >= leftMax {
                    leftMax = height[left]
                } else {
                    result += leftMax - height[left]
                }
                left += 1
            } else {
                if height[right] >= rightMax {
                    rightMax = height[right]
                } else {
                    result += rightMax - height[right]
                }
                right -= 1
            }
        }
        
        return result
    }
    
    /// 动态规划解法
    func trapDP(_ height: [Int]) -> Int {
        guard height.count > 2 else { return 0 }
        
        let n = height.count
        var leftMax = Array(repeating: 0, count: n)
        var rightMax = Array(repeating: 0, count: n)
        
        // 计算每个位置左边的最大高度
        leftMax[0] = height[0]
        for i in 1..<n {
            leftMax[i] = max(leftMax[i - 1], height[i])
        }
        
        // 计算每个位置右边的最大高度
        rightMax[n - 1] = height[n - 1]
        for i in stride(from: n - 2, through: 0, by: -1) {
            rightMax[i] = max(rightMax[i + 1], height[i])
        }
        
        // 计算雨水量
        var result = 0
        for i in 0..<n {
            let waterLevel = min(leftMax[i], rightMax[i])
            if waterLevel > height[i] {
                result += waterLevel - height[i]
            }
        }
        
        return result
    }
    
    /// 单调栈解法
    func trapStack(_ height: [Int]) -> Int {
        var stack: [Int] = []
        var result = 0
        
        for i in 0..<height.count {
            while !stack.isEmpty && height[i] > height[stack.last!] {
                let top = stack.removeLast()
                
                if stack.isEmpty {
                    break
                }
                
                let distance = i - stack.last! - 1
                let boundedHeight = min(height[i], height[stack.last!]) - height[top]
                result += distance * boundedHeight
            }
            
            stack.append(i)
        }
        
        return result
    }
    
    /// 函数式解法
    func trapFunctional(_ height: [Int]) -> Int {
        guard height.count > 2 else { return 0 }
        
        let n = height.count
        let leftMax = height.enumerated().map { index, _ in
            height[0...index].max()!
        }
        
        let rightMax = height.enumerated().map { index, _ in
            height[index..<n].max()!
        }
        
        return zip(leftMax, rightMax).enumerated().reduce(0) { result, element in
            let (index, (left, right)) = element
            let waterLevel = min(left, right)
            return result + max(0, waterLevel - height[index])
        }
    }
    
    static func runExample() {
        print("\n=== LeetCode 42: 接雨水 ===")
        
        let solution = LC42_TrappingRainWater()
        
        let testCases = [
            [0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1],
            [4, 2, 0, 3, 2, 5],
            [3, 0, 2, 0, 4]
        ]
        
        for (index, heights) in testCases.enumerated() {
            let result1 = solution.trap(heights)
            let result2 = solution.trapDP(heights)
            let result3 = solution.trapStack(heights)
            
            print("测试 \(index + 1): \(heights)")
            print("双指针: \(result1), DP: \(result2), 单调栈: \(result3)")
        }
    }
}

// MARK: - 面试算法演示
struct InterviewAlgorithmsExamples {
    static func runAll() {
        print("🚀 面试算法Swift实现\n")
        
        // 最小栈演示
        print("=== LeetCode 155: 最小栈 ===")
        let minStack = MinStack()
        
        print("push(-2)")
        minStack.push(-2)
        print("push(0)")
        minStack.push(0)
        print("push(-3)")
        minStack.push(-3)
        print("getMin(): \(minStack.getMin())")  // -3
        print("pop()")
        minStack.pop()
        print("top(): \(minStack.top())")        // 0
        print("getMin(): \(minStack.getMin())")  // -2
        
        // 泛型最小栈演示
        print("\n=== 泛型最小栈 ===")
        let genericStack = GenericMinStack<String>()
        ["c", "a", "b"].forEach { genericStack.push($0) }
        print("最小值: \(genericStack.getMin() ?? "nil")")  // "a"
        
        LC160_IntersectionLinkedList.runExample()
        LC42_TrappingRainWater.runExample()
    }
}
