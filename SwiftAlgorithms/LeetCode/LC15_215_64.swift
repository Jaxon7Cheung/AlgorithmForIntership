import Foundation

// MARK: - LeetCode 15: 三数之和
/// Swift风格实现，使用高阶函数和Set去重

class LC15_ThreeSum {
    
    /// 双指针解法 - 经典解法
    func threeSum(_ nums: [Int]) -> [[Int]] {
        guard nums.count >= 3 else { return [] }
        
        let sortedNums = nums.sorted()
        var result: [[Int]] = []
        
        for i in 0..<sortedNums.count - 2 {
            // 优化：如果当前数字大于0，不可能有和为0的三元组
            if sortedNums[i] > 0 { break }
            
            // 跳过重复元素
            if i > 0 && sortedNums[i] == sortedNums[i - 1] { continue }
            
            var left = i + 1
            var right = sortedNums.count - 1
            let target = -sortedNums[i]
            
            while left < right {
                let sum = sortedNums[left] + sortedNums[right]
                
                switch sum.compared(to: target) {
                case .equal:
                    result.append([sortedNums[i], sortedNums[left], sortedNums[right]])
                    
                    // 跳过重复元素
                    repeat { left += 1 } while left < right && sortedNums[left] == sortedNums[left - 1]
                    repeat { right -= 1 } while left < right && sortedNums[right] == sortedNums[right + 1]
                    
                case .less:
                    left += 1
                case .greater:
                    right -= 1
                }
            }
        }
        
        return result
    }
    
    /// 函数式解法 - 使用组合和过滤
    func threeSumFunctional(_ nums: [Int]) -> [[Int]] {
        guard nums.count >= 3 else { return [] }
        
        let sortedNums = nums.sorted()
        var result: Set<[Int]> = []
        
        // 生成所有三元组合
        for i in 0..<sortedNums.count - 2 {
            for j in i + 1..<sortedNums.count - 1 {
                for k in j + 1..<sortedNums.count {
                    let triplet = [sortedNums[i], sortedNums[j], sortedNums[k]]
                    if triplet.reduce(0, +) == 0 {
                        result.insert(triplet)
                    }
                }
            }
        }
        
        return Array(result).sorted { $0.lexicographicallyPrecedes($1) }
    }
    
    /// 使用字典优化的解法
    func threeSumWithDict(_ nums: [Int]) -> [[Int]] {
        guard nums.count >= 3 else { return [] }
        
        let sortedNums = nums.sorted()
        var result: Set<[Int]> = []
        
        for i in 0..<sortedNums.count - 2 {
            if sortedNums[i] > 0 { break }
            
            var seen: Set<Int> = []
            
            for j in i + 1..<sortedNums.count {
                let complement = -(sortedNums[i] + sortedNums[j])
                
                if seen.contains(complement) {
                    let triplet = [sortedNums[i], complement, sortedNums[j]].sorted()
                    result.insert(triplet)
                }
                
                seen.insert(sortedNums[j])
            }
        }
        
        return Array(result).sorted { $0.lexicographicallyPrecedes($1) }
    }
    
    static func runExample() {
        print("=== LeetCode 15: 三数之和 ===")
        
        let solution = LC15_ThreeSum()
        
        let testCases = [
            [-1, 0, 1, 2, -1, -4],
            [0, 1, 1],
            [0, 0, 0],
            [-2, 0, 1, 1, 2]
        ]
        
        for (index, nums) in testCases.enumerated() {
            let result = solution.threeSum(nums)
            print("测试 \(index + 1): \(nums)")
            print("结果: \(result)")
            print()
        }
    }
}

// MARK: - LeetCode 215: 数组中的第K个最大元素
class LC215_FindKthLargest {
    
    /// 小顶堆解法 - Swift风格
    func findKthLargest(_ nums: [Int], _ k: Int) -> Int {
        var heap = Array(nums.prefix(k))
        buildMinHeap(&heap)
        
        for i in k..<nums.count {
            if nums[i] > heap[0] {
                heap[0] = nums[i]
                heapify(&heap, 0, k)
            }
        }
        
        return heap[0]
    }
    
    /// 快速选择算法 - 更优解法
    func findKthLargestQuickSelect(_ nums: [Int], _ k: Int) -> Int {
        var array = nums
        let targetIndex = nums.count - k
        
        func quickSelect(_ left: Int, _ right: Int) -> Int {
            let pivotIndex = partition(&array, left, right)
            
            if pivotIndex == targetIndex {
                return array[pivotIndex]
            } else if pivotIndex < targetIndex {
                return quickSelect(pivotIndex + 1, right)
            } else {
                return quickSelect(left, pivotIndex - 1)
            }
        }
        
        return quickSelect(0, array.count - 1)
    }
    
    /// 函数式解法 - 最简洁
    func findKthLargestFunctional(_ nums: [Int], _ k: Int) -> Int {
        return nums.sorted(by: >)[k - 1]
    }
    
    /// 使用Swift内置堆的解法
    func findKthLargestBuiltIn(_ nums: [Int], _ k: Int) -> Int {
        // 使用PriorityQueue（如果可用）或者简单排序
        let sortedDesc = nums.sorted(by: >)
        return sortedDesc[k - 1]
    }
    
    // MARK: - 辅助方法
    private func buildMinHeap(_ nums: inout [Int]) {
        let n = nums.count
        for i in stride(from: n / 2 - 1, through: 0, by: -1) {
            heapify(&nums, i, n)
        }
    }
    
    private func heapify(_ nums: inout [Int], _ root: Int, _ heapSize: Int) {
        var smallest = root
        let leftChild = 2 * root + 1
        let rightChild = 2 * root + 2
        
        if leftChild < heapSize && nums[leftChild] < nums[smallest] {
            smallest = leftChild
        }
        
        if rightChild < heapSize && nums[rightChild] < nums[smallest] {
            smallest = rightChild
        }
        
        if smallest != root {
            nums.swapAt(root, smallest)
            heapify(&nums, smallest, heapSize)
        }
    }
    
    private func partition(_ nums: inout [Int], _ left: Int, _ right: Int) -> Int {
        let pivot = nums[right]
        var i = left
        
        for j in left..<right {
            if nums[j] <= pivot {
                nums.swapAt(i, j)
                i += 1
            }
        }
        
        nums.swapAt(i, right)
        return i
    }
    
    static func runExample() {
        print("=== LeetCode 215: 数组中的第K个最大元素 ===")
        
        let solution = LC215_FindKthLargest()
        
        let testCases: [([Int], Int)] = [
            ([3, 2, 1, 5, 6, 4], 2),
            ([3, 2, 3, 1, 2, 4, 5, 5, 6], 4),
            ([1], 1),
            ([7, 10, 4, 3, 20, 15], 3)
        ]
        
        for (nums, k) in testCases {
            let result1 = solution.findKthLargest(nums, k)
            let result2 = solution.findKthLargestQuickSelect(nums, k)
            let result3 = solution.findKthLargestFunctional(nums, k)
            
            print("数组: \(nums), k=\(k)")
            print("小顶堆解法: \(result1)")
            print("快速选择: \(result2)")
            print("函数式解法: \(result3)")
            print()
        }
    }
}

// MARK: - LeetCode 64: 最小路径和
class LC64_MinPathSum {
    
    /// 动态规划解法 - 原地修改
    func minPathSum(_ grid: [[Int]]) -> Int {
        guard !grid.isEmpty && !grid[0].isEmpty else { return 0 }
        
        var dp = grid
        let m = dp.count
        let n = dp[0].count
        
        // 初始化第一行
        for j in 1..<n {
            dp[0][j] += dp[0][j - 1]
        }
        
        // 初始化第一列
        for i in 1..<m {
            dp[i][0] += dp[i - 1][0]
        }
        
        // 填充dp表
        for i in 1..<m {
            for j in 1..<n {
                dp[i][j] += min(dp[i - 1][j], dp[i][j - 1])
            }
        }
        
        return dp[m - 1][n - 1]
    }
    
    /// 空间优化版本 - 只使用一维数组
    func minPathSumOptimized(_ grid: [[Int]]) -> Int {
        guard !grid.isEmpty && !grid[0].isEmpty else { return 0 }
        
        let n = grid[0].count
        var dp = Array(grid[0])  // 使用第一行初始化
        
        // 计算第一行的累加和
        for j in 1..<n {
            dp[j] += dp[j - 1]
        }
        
        // 处理其余行
        for i in 1..<grid.count {
            dp[0] += grid[i][0]  // 第一列
            
            for j in 1..<n {
                dp[j] = grid[i][j] + min(dp[j], dp[j - 1])
            }
        }
        
        return dp[n - 1]
    }
    
    /// 递归+备忘录解法
    func minPathSumMemo(_ grid: [[Int]]) -> Int {
        var memo: [[Int?]] = Array(repeating: Array(repeating: nil, count: grid[0].count), count: grid.count)
        
        func dfs(_ i: Int, _ j: Int) -> Int {
            // 边界检查
            guard i >= 0 && i < grid.count && j >= 0 && j < grid[0].count else {
                return Int.max
            }
            
            // 基础情况
            if i == 0 && j == 0 {
                return grid[0][0]
            }
            
            // 检查备忘录
            if let cached = memo[i][j] {
                return cached
            }
            
            // 递归计算
            let fromTop = i > 0 ? dfs(i - 1, j) : Int.max
            let fromLeft = j > 0 ? dfs(i, j - 1) : Int.max
            
            let result = grid[i][j] + min(fromTop, fromLeft)
            memo[i][j] = result
            
            return result
        }
        
        return dfs(grid.count - 1, grid[0].count - 1)
    }
    
    static func runExample() {
        print("=== LeetCode 64: 最小路径和 ===")
        
        let solution = LC64_MinPathSum()
        
        let testCases = [
            [[1, 3, 1], [1, 5, 1], [4, 2, 1]],
            [[1, 2, 3], [4, 5, 6]],
            [[1]]
        ]
        
        for (index, grid) in testCases.enumerated() {
            let result1 = solution.minPathSum(grid)
            let result2 = solution.minPathSumOptimized(grid)
            let result3 = solution.minPathSumMemo(grid)
            
            print("测试 \(index + 1):")
            print("网格: \(grid)")
            print("DP解法: \(result1)")
            print("优化解法: \(result2)")
            print("备忘录解法: \(result3)")
            print()
        }
    }
}

// MARK: - Int扩展：比较方法
extension Int {
    func compared(to other: Int) -> ComparisonResult {
        if self < other { return .less }
        if self > other { return .greater }
        return .equal
    }
}

// MARK: - LeetCode中级算法演示
struct LeetCodeIntermediateExamples {
    static func runAll() {
        print("🚀 LeetCode中级算法Swift实现\n")
        
        LC15_ThreeSum.runExample()
        LC215_FindKthLargest.runExample()
        LC64_MinPathSum.runExample()
    }
}
