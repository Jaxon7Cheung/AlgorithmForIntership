import Foundation

// MARK: - 堆排序 (Heap Sort)
/// Swift风格的堆排序实现，使用泛型和协议约束

struct HeapSort {
    
    /// 堆排序主函数 - 使用泛型和where约束
    static func sort<T>(_ array: inout [T]) where T: Comparable {
        guard array.count > 1 else { return }
        
        let n = array.count
        
        // 构建大根堆：从最后一个非叶子节点开始
        for i in stride(from: n / 2 - 1, through: 0, by: -1) {
            heapify(&array, heapSize: n, rootIndex: i)
        }
        
        // 逐个从堆中取出元素
        for i in stride(from: n - 1, to: 0, by: -1) {
            // 将当前根（最大值）移到数组末尾
            array.swapAt(0, i)
            // 对剩余的堆进行堆化
            heapify(&array, heapSize: i, rootIndex: 0)
        }
    }
    
    /// 堆化操作 - 维护大根堆性质
    private static func heapify<T>(_ array: inout [T], heapSize: Int, rootIndex: Int) where T: Comparable {
        var largest = rootIndex
        let leftChild = 2 * rootIndex + 1
        let rightChild = 2 * rootIndex + 2
        
        // 使用Swift的guard语句优化边界检查
        if leftChild < heapSize && array[leftChild] > array[largest] {
            largest = leftChild
        }
        
        if rightChild < heapSize && array[rightChild] > array[largest] {
            largest = rightChild
        }
        
        // 如果最大值不是根节点，交换并递归堆化
        if largest != rootIndex {
            array.swapAt(rootIndex, largest)
            heapify(&array, heapSize: heapSize, rootIndex: largest)
        }
    }
}

// MARK: - Array扩展：为数组添加堆排序方法
extension Array where Element: Comparable {
    /// 原地堆排序
    mutating func heapSort() {
        HeapSort.sort(&self)
    }
    
    /// 返回堆排序后的新数组
    func heapSorted() -> [Element] {
        var copy = self
        copy.heapSort()
        return copy
    }
}

// MARK: - 最小堆实现
struct MinHeap<T: Comparable> {
    private var elements: [T] = []
    
    /// 计算属性：是否为空
    var isEmpty: Bool {
        return elements.isEmpty
    }
    
    /// 计算属性：堆大小
    var count: Int {
        return elements.count
    }
    
    /// 查看堆顶元素（不移除）
    var peek: T? {
        return elements.first
    }
    
    /// 插入元素
    mutating func insert(_ element: T) {
        elements.append(element)
        siftUp(from: elements.count - 1)
    }
    
    /// 移除并返回堆顶元素
    @discardableResult
    mutating func removeMin() -> T? {
        guard !isEmpty else { return nil }
        
        if elements.count == 1 {
            return elements.removeLast()
        }
        
        let min = elements[0]
        elements[0] = elements.removeLast()
        siftDown(from: 0)
        return min
    }
    
    /// 上浮操作
    private mutating func siftUp(from index: Int) {
        let parentIndex = (index - 1) / 2
        guard index > 0 && elements[index] < elements[parentIndex] else { return }
        
        elements.swapAt(index, parentIndex)
        siftUp(from: parentIndex)
    }
    
    /// 下沉操作
    private mutating func siftDown(from index: Int) {
        let leftChild = 2 * index + 1
        let rightChild = 2 * index + 2
        var smallest = index
        
        if leftChild < elements.count && elements[leftChild] < elements[smallest] {
            smallest = leftChild
        }
        
        if rightChild < elements.count && elements[rightChild] < elements[smallest] {
            smallest = rightChild
        }
        
        guard smallest != index else { return }
        
        elements.swapAt(index, smallest)
        siftDown(from: smallest)
    }
}

// MARK: - MinHeap扩展：CustomStringConvertible
extension MinHeap: CustomStringConvertible {
    var description: String {
        return "MinHeap(\(elements))"
    }
}

// MARK: - 示例和测试
extension HeapSort {
    /// 测试堆排序功能
    static func runExample() {
        print("=== 堆排序示例 ===")
        
        // 测试整数数组
        var intArray = [8, 1, 14, 3, 21, 5, 7, 10]
        print("原数组: \(intArray)")
        intArray.heapSort()
        print("堆排序后: \(intArray)")
        
        // 测试字符串数组
        var stringArray = ["banana", "apple", "cherry", "date"]
        print("\n原字符串数组: \(stringArray)")
        stringArray.heapSort()
        print("堆排序后: \(stringArray)")
        
        // 测试最小堆
        print("\n=== 最小堆示例 ===")
        var minHeap = MinHeap<Int>()
        [8, 1, 14, 3, 21, 5, 7, 10].forEach { minHeap.insert($0) }
        print("构建最小堆: \(minHeap)")
        
        var sortedResult: [Int] = []
        while !minHeap.isEmpty {
            if let min = minHeap.removeMin() {
                sortedResult.append(min)
            }
        }
        print("从最小堆取出的有序序列: \(sortedResult)")
    }
}
