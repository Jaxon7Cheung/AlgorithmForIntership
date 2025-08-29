import Foundation

// MARK: - 归并排序 (Merge Sort)
/// Swift风格的归并排序实现，充分利用高阶函数和数组分片

struct MergeSort {
    
    /// 归并排序主函数 - 使用泛型约束
    static func sort<T>(_ array: [T]) -> [T] where T: Comparable {
        guard array.count > 1 else { return array }
        return mergeSort(array)
    }
    
    /// 原地归并排序
    static func sortInPlace<T>(_ array: inout [T]) where T: Comparable {
        guard array.count > 1 else { return }
        var temp = Array(repeating: array[0], count: array.count)
        mergeSortInPlace(&array, temp: &temp, left: 0, right: array.count - 1)
    }
    
    /// 递归归并排序 - 函数式风格
    private static func mergeSort<T>(_ array: [T]) -> [T] where T: Comparable {
        guard array.count > 1 else { return array }
        
        let mid = array.count / 2
        
        // 使用数组分片 - Swift语法糖
        let leftArray = Array(array[..<mid])
        let rightArray = Array(array[mid...])
        
        // 递归分解
        let sortedLeft = mergeSort(leftArray)
        let sortedRight = mergeSort(rightArray)
        
        // 合并
        return merge(sortedLeft, sortedRight)
    }
    
    /// 合并两个有序数组 - 使用Swift的高级特性
    private static func merge<T>(_ left: [T], _ right: [T]) -> [T] where T: Comparable {
        var result: [T] = []
        var leftIndex = 0
        var rightIndex = 0
        
        // 使用Swift的条件判断语法糖
        while leftIndex < left.count && rightIndex < right.count {
            if left[leftIndex] <= right[rightIndex] {
                result.append(left[leftIndex])
                leftIndex += 1
            } else {
                result.append(right[rightIndex])
                rightIndex += 1
            }
        }
        
        // 使用数组分片添加剩余元素
        result.append(contentsOf: left[leftIndex...])
        result.append(contentsOf: right[rightIndex...])
        
        return result
    }
    
    /// 原地归并排序实现 - 使用inout参数
    private static func mergeSortInPlace<T>(_ array: inout [T], temp: inout [T], left: Int, right: Int) where T: Comparable {
        guard left < right else { return }
        
        let mid = left + (right - left) / 2
        
        // 递归分解
        mergeSortInPlace(&array, temp: &temp, left: left, right: mid)
        mergeSortInPlace(&array, temp: &temp, left: mid + 1, right: right)
        
        // 合并
        mergeInPlace(&array, temp: &temp, left: left, mid: mid, right: right)
    }
    
    /// 原地合并操作
    private static func mergeInPlace<T>(_ array: inout [T], temp: inout [T], left: Int, mid: Int, right: Int) where T: Comparable {
        var leftPtr = left
        var rightPtr = mid + 1
        var tempIndex = left
        
        // 比较并合并
        while leftPtr <= mid && rightPtr <= right {
            if array[leftPtr] <= array[rightPtr] {
                temp[tempIndex] = array[leftPtr]
                leftPtr += 1
            } else {
                temp[tempIndex] = array[rightPtr]
                rightPtr += 1
            }
            tempIndex += 1
        }
        
        // 复制剩余元素
        while leftPtr <= mid {
            temp[tempIndex] = array[leftPtr]
            leftPtr += 1
            tempIndex += 1
        }
        
        while rightPtr <= right {
            temp[tempIndex] = array[rightPtr]
            rightPtr += 1
            tempIndex += 1
        }
        
        // 将临时数组的结果复制回原数组
        for i in left...right {
            array[i] = temp[i]
        }
    }
}

// MARK: - Array扩展：为数组添加归并排序方法
extension Array where Element: Comparable {
    /// 返回归并排序后的新数组
    func mergeSorted() -> [Element] {
        return MergeSort.sort(self)
    }
    
    /// 原地归并排序
    mutating func mergeSort() {
        MergeSort.sortInPlace(&self)
    }
    
    /// 使用尾随闭包的自定义比较器归并排序
    func mergeSorted(by comparator: (Element, Element) -> Bool) -> [Element] {
        guard count > 1 else { return self }
        
        let mid = count / 2
        let left = Array(self[..<mid]).mergeSorted(by: comparator)
        let right = Array(self[mid...]).mergeSorted(by: comparator)
        
        return merge(left, right, by: comparator)
    }
    
    /// 使用自定义比较器的合并函数
    private func merge(_ left: [Element], _ right: [Element], by comparator: (Element, Element) -> Bool) -> [Element] {
        var result: [Element] = []
        var leftIndex = 0
        var rightIndex = 0
        
        while leftIndex < left.count && rightIndex < right.count {
            if comparator(left[leftIndex], right[rightIndex]) {
                result.append(left[leftIndex])
                leftIndex += 1
            } else {
                result.append(right[rightIndex])
                rightIndex += 1
            }
        }
        
        result.append(contentsOf: left[leftIndex...])
        result.append(contentsOf: right[rightIndex...])
        
        return result
    }
}

// MARK: - 分治算法协议
protocol DivideAndConquer {
    associatedtype Element
    static func divide(_ input: [Element]) -> ([Element], [Element])
    static func conquer(_ left: [Element], _ right: [Element]) -> [Element]
    static func solve(_ input: [Element]) -> [Element]
}

// MARK: - 归并排序的分治实现
struct MergeSortDivideAndConquer<T: Comparable>: DivideAndConquer {
    typealias Element = T
    
    static func divide(_ input: [T]) -> ([T], [T]) {
        let mid = input.count / 2
        return (Array(input[..<mid]), Array(input[mid...]))
    }
    
    static func conquer(_ left: [T], _ right: [T]) -> [T] {
        return MergeSort.merge(left, right)
    }
    
    static func solve(_ input: [T]) -> [T] {
        guard input.count > 1 else { return input }
        
        let (left, right) = divide(input)
        let sortedLeft = solve(left)
        let sortedRight = solve(right)
        
        return conquer(sortedLeft, sortedRight)
    }
}

// MARK: - 性能测试和示例
extension MergeSort {
    /// 性能测试
    static func performanceTest() {
        let sizes = [1000, 10000, 100000]
        
        for size in sizes {
            let randomArray = (0..<size).map { _ in Int.random(in: 0...1000) }
            
            // 测试函数式归并排序
            let startTime1 = CFAbsoluteTimeGetCurrent()
            let _ = MergeSort.sort(randomArray)
            let time1 = CFAbsoluteTimeGetCurrent() - startTime1
            
            // 测试原地归并排序
            var testArray = randomArray
            let startTime2 = CFAbsoluteTimeGetCurrent()
            testArray.mergeSort()
            let time2 = CFAbsoluteTimeGetCurrent() - startTime2
            
            print("数组大小: \(size)")
            print("函数式归并排序: \(String(format: "%.4f", time1))秒")
            print("原地归并排序: \(String(format: "%.4f", time2))秒")
            print("---")
        }
    }
    
    /// 示例演示
    static func runExample() {
        print("=== 归并排序示例 ===")
        
        // 整数数组排序
        let intArray = [8, 1, 14, 3, 21, 5, 7, 10]
        print("原数组: \(intArray)")
        print("归并排序后: \(intArray.mergeSorted())")
        
        // 字符串数组排序
        let stringArray = ["banana", "apple", "cherry", "date"]
        print("\n原字符串数组: \(stringArray)")
        print("归并排序后: \(stringArray.mergeSorted())")
        
        // 自定义比较器排序（降序）
        let descendingArray = intArray.mergeSorted { $0 > $1 }
        print("\n降序排序: \(descendingArray)")
        
        // 结构体排序示例
        struct Student {
            let name: String
            let score: Int
        }
        
        let students = [
            Student(name: "Alice", score: 85),
            Student(name: "Bob", score: 92),
            Student(name: "Charlie", score: 78)
        ]
        
        let sortedStudents = students.sorted { $0.score > $1.score }
        print("\n学生按分数降序:")
        sortedStudents.forEach { print("\($0.name): \($0.score)") }
    }
}
