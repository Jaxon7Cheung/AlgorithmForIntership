import Foundation

// MARK: - LeetCode 347: 前K个高频元素
/// Swift风格实现，使用字典、高阶函数和堆

class LC347_TopKFrequent {
    
    /// 使用字典统计+排序的简洁解法
    func topKFrequent(_ nums: [Int], _ k: Int) -> [Int] {
        // 统计频次
        let frequencies = nums.reduce(into: [:]) { counts, num in
            counts[num, default: 0] += 1
        }
        
        // 按频次排序并取前k个
        return frequencies
            .sorted { $0.value > $1.value }
            .prefix(k)
            .map { $0.key }
    }
    
    /// 小顶堆解法 - 空间优化
    func topKFrequentHeap(_ nums: [Int], _ k: Int) -> [Int] {
        // 统计频次
        var frequencies: [Int: Int] = [:]
        for num in nums {
            frequencies[num, default: 0] += 1
        }
        
        // 使用小顶堆维护前k个高频元素
        var heap: [(value: Int, frequency: Int)] = []
        
        for (value, frequency) in frequencies {
            if heap.count < k {
                heap.append((value, frequency))
                if heap.count == k {
                    buildMinHeap(&heap)
                }
            } else if frequency > heap[0].frequency {
                heap[0] = (value, frequency)
                heapifyDown(&heap, 0)
            }
        }
        
        return heap.map { $0.value }
    }
    
    /// 桶排序解法 - 线性时间复杂度
    func topKFrequentBucket(_ nums: [Int], _ k: Int) -> [Int] {
        // 统计频次
        let frequencies = nums.reduce(into: [:]) { counts, num in
            counts[num, default: 0] += 1
        }
        
        // 创建桶，索引表示频次
        var buckets: [[Int]] = Array(repeating: [], count: nums.count + 1)
        
        // 将数字放入对应频次的桶中
        for (value, frequency) in frequencies {
            buckets[frequency].append(value)
        }
        
        // 从高频次桶开始收集结果
        var result: [Int] = []
        for i in stride(from: buckets.count - 1, through: 0, by: -1) {
            result.append(contentsOf: buckets[i])
            if result.count >= k {
                break
            }
        }
        
        return Array(result.prefix(k))
    }
    
    /// 使用优先队列的解法（模拟）
    func topKFrequentPriorityQueue(_ nums: [Int], _ k: Int) -> [Int] {
        let frequencies = Dictionary(nums.map { ($0, 1) }, uniquingKeysWith: +)
        
        // 创建最小优先队列（使用数组模拟）
        var priorityQueue = Array(frequencies.prefix(k))
        priorityQueue.sort { $0.value < $1.value }
        
        for (value, frequency) in frequencies.dropFirst(k) {
            if frequency > priorityQueue[0].value {
                priorityQueue[0] = (value, frequency)
                priorityQueue.sort { $0.value < $1.value }
            }
        }
        
        return priorityQueue.map { $0.key }
    }
    
    // MARK: - 堆操作辅助方法
    private func buildMinHeap(_ heap: inout [(value: Int, frequency: Int)]) {
        let n = heap.count
        for i in stride(from: n / 2 - 1, through: 0, by: -1) {
            heapifyDown(&heap, i)
        }
    }
    
    private func heapifyDown(_ heap: inout [(value: Int, frequency: Int)], _ index: Int) {
        let n = heap.count
        var smallest = index
        let leftChild = 2 * index + 1
        let rightChild = 2 * index + 2
        
        if leftChild < n && heap[leftChild].frequency < heap[smallest].frequency {
            smallest = leftChild
        }
        
        if rightChild < n && heap[rightChild].frequency < heap[smallest].frequency {
            smallest = rightChild
        }
        
        if smallest != index {
            heap.swapAt(index, smallest)
            heapifyDown(&heap, smallest)
        }
    }
    
    static func runExample() {
        print("=== LeetCode 347: 前K个高频元素 ===")
        
        let solution = LC347_TopKFrequent()
        
        let testCases: [([Int], Int)] = [
            ([1, 1, 1, 2, 2, 3], 2),
            ([1], 1),
            ([1, 2], 2),
            ([4, 1, -1, 2, -1, 2, 3], 2)
        ]
        
        for (nums, k) in testCases {
            let result1 = solution.topKFrequent(nums, k)
            let result2 = solution.topKFrequentHeap(nums, k)
            let result3 = solution.topKFrequentBucket(nums, k)
            
            print("输入: nums=\(nums), k=\(k)")
            print("排序解法: \(result1)")
            print("堆解法: \(result2)")
            print("桶排序: \(result3)")
            print()
        }
    }
}

// MARK: - LeetCode 112: 路径总和
class LC112_HasPathSum {
    
    /// 递归解法 - 简洁优雅
    func hasPathSum(_ root: TreeNode?, _ targetSum: Int) -> Bool {
        guard let root = root else { return false }
        
        // 叶子节点检查
        if root.left == nil && root.right == nil {
            return root.val == targetSum
        }
        
        // 递归检查左右子树
        let remainingSum = targetSum - root.val
        return hasPathSum(root.left, remainingSum) || hasPathSum(root.right, remainingSum)
    }
    
    /// 迭代解法 - 使用栈
    func hasPathSumIterative(_ root: TreeNode?, _ targetSum: Int) -> Bool {
        guard let root = root else { return false }
        
        var stack: [(node: TreeNode, sum: Int)] = [(root, targetSum)]
        
        while !stack.isEmpty {
            let (node, currentSum) = stack.removeLast()
            
            // 检查叶子节点
            if node.left == nil && node.right == nil {
                if node.val == currentSum {
                    return true
                }
                continue
            }
            
            // 添加子节点到栈中
            let remainingSum = currentSum - node.val
            if let left = node.left {
                stack.append((left, remainingSum))
            }
            if let right = node.right {
                stack.append((right, remainingSum))
            }
        }
        
        return false
    }
    
    /// 函数式解法 - 使用闭包
    func hasPathSumFunctional(_ root: TreeNode?, _ targetSum: Int) -> Bool {
        func traverse(_ node: TreeNode?, _ currentSum: Int) -> Bool {
            guard let node = node else { return false }
            
            let newSum = currentSum + node.val
            
            if node.isLeaf {
                return newSum == targetSum
            }
            
            return traverse(node.left, newSum) || traverse(node.right, newSum)
        }
        
        return traverse(root, 0)
    }
    
    static func runExample() {
        print("=== LeetCode 112: 路径总和 ===")
        
        let solution = LC112_HasPathSum()
        
        // 构建测试树: [5,4,8,11,null,13,4,7,2,null,null,null,1]
        let root = TreeNode(5)
        root.left = TreeNode(4)
        root.right = TreeNode(8)
        root.left?.left = TreeNode(11)
        root.left?.left?.left = TreeNode(7)
        root.left?.left?.right = TreeNode(2)
        root.right?.left = TreeNode(13)
        root.right?.right = TreeNode(4)
        root.right?.right?.right = TreeNode(1)
        
        let testTargets = [22, 26, 18]
        
        for target in testTargets {
            let result1 = solution.hasPathSum(root, target)
            let result2 = solution.hasPathSumIterative(root, target)
            let result3 = solution.hasPathSumFunctional(root, target)
            
            print("目标和: \(target)")
            print("递归解法: \(result1)")
            print("迭代解法: \(result2)")
            print("函数式解法: \(result3)")
            print()
        }
    }
}

// MARK: - LeetCode 69: x的平方根
class LC69_MySqrt {
    
    /// 二分查找解法
    func mySqrt(_ x: Int) -> Int {
        guard x > 1 else { return x }
        
        var left = 1
        var right = x
        var result = 0
        
        while left <= right {
            let mid = left + (right - left) / 2
            let square = mid * mid
            
            if square == x {
                return mid
            } else if square < x {
                result = mid
                left = mid + 1
            } else {
                right = mid - 1
            }
        }
        
        return result
    }
    
    /// 牛顿迭代法
    func mySqrtNewton(_ x: Int) -> Int {
        guard x > 1 else { return x }
        
        var r = x
        while r * r > x {
            r = (r + x / r) / 2
        }
        
        return r
    }
    
    /// 数学公式法
    func mySqrtMath(_ x: Int) -> Int {
        guard x > 0 else { return 0 }
        return Int(sqrt(Double(x)))
    }
    
    static func runExample() {
        print("=== LeetCode 69: x的平方根 ===")
        
        let solution = LC69_MySqrt()
        
        let testCases = [0, 1, 4, 8, 9, 16, 25, 100, 121, 144]
        
        for x in testCases {
            let result1 = solution.mySqrt(x)
            let result2 = solution.mySqrtNewton(x)
            let result3 = solution.mySqrtMath(x)
            
            print("√\(x): 二分查找=\(result1), 牛顿法=\(result2), 数学函数=\(result3)")
        }
    }
}

// MARK: - Dictionary扩展：合并操作
extension Dictionary where Value: Numeric {
    /// 合并字典，相同键的值相加
    static func + (lhs: [Key: Value], rhs: [Key: Value]) -> [Key: Value] {
        return lhs.merging(rhs, uniquingKeysWith: +)
    }
}

// MARK: - Array扩展：频次统计
extension Array where Element: Hashable {
    /// 统计元素频次
    var frequencies: [Element: Int] {
        return self.reduce(into: [:]) { counts, element in
            counts[element, default: 0] += 1
        }
    }
    
    /// 获取前k个高频元素
    func topKFrequent(_ k: Int) -> [Element] {
        return frequencies
            .sorted { $0.value > $1.value }
            .prefix(k)
            .map { $0.key }
    }
}

// MARK: - LeetCode高级算法演示
struct LeetCodeAdvancedExamples {
    static func runAll() {
        print("🚀 LeetCode高级算法Swift实现\n")
        
        LC347_TopKFrequent.runExample()
        LC112_HasPathSum.runExample()
        LC69_MySqrt.runExample()
        
        // 演示扩展方法
        print("=== 扩展方法演示 ===")
        let numbers = [1, 1, 1, 2, 2, 3]
        print("数组 \(numbers) 的频次统计: \(numbers.frequencies)")
        print("前2个高频元素: \(numbers.topKFrequent(2))")
    }
}
