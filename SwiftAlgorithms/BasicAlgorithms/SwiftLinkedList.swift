import Foundation

// MARK: - Swift链表实现
/// 完整的链表数据结构实现，使用Swift风格和语法糖

class SwiftLinkedList<T> {
    
    // MARK: - 私有节点类
    private class Node {
        var value: T
        var next: Node?
        
        init(_ value: T) {
            self.value = value
            self.next = nil
        }
    }
    
    // MARK: - 私有属性
    private var head: Node?
    private var tail: Node?
    private var _count: Int = 0
    
    // MARK: - 公共属性
    /// 链表长度
    var count: Int {
        return _count
    }
    
    /// 是否为空
    var isEmpty: Bool {
        return _count == 0
    }
    
    /// 第一个元素（可选）
    var first: T? {
        return head?.value
    }
    
    /// 最后一个元素（可选）
    var last: T? {
        return tail?.value
    }
    
    // MARK: - 初始化
    init() {}
    
    init<S: Sequence>(_ sequence: S) where S.Element == T {
        for element in sequence {
            append(element)
        }
    }
    
    // MARK: - 尾部插入
    /// 在链表尾部添加元素
    func append(_ value: T) {
        let newNode = Node(value)
        
        if isEmpty {
            head = newNode
            tail = newNode
        } else {
            tail?.next = newNode
            tail = newNode
        }
        
        _count += 1
    }
    
    // MARK: - 头部插入
    /// 在链表头部添加元素
    func prepend(_ value: T) {
        let newNode = Node(value)
        
        if isEmpty {
            head = newNode
            tail = newNode
        } else {
            newNode.next = head
            head = newNode
        }
        
        _count += 1
    }
    
    // MARK: - 指定位置插入
    /// 在指定索引位置插入元素
    func insert(_ value: T, at index: Int) -> Bool {
        guard index >= 0 && index <= count else { return false }
        
        if index == 0 {
            prepend(value)
            return true
        }
        
        if index == count {
            append(value)
            return true
        }
        
        guard let prevNode = node(at: index - 1) else { return false }
        
        let newNode = Node(value)
        newNode.next = prevNode.next
        prevNode.next = newNode
        _count += 1
        
        return true
    }
    
    // MARK: - 删除操作
    /// 删除指定索引的元素
    @discardableResult
    func remove(at index: Int) -> T? {
        guard index >= 0 && index < count else { return nil }
        
        if index == 0 {
            return removeFirst()
        }
        
        guard let prevNode = node(at: index - 1),
              let nodeToRemove = prevNode.next else { return nil }
        
        prevNode.next = nodeToRemove.next
        
        // 如果删除的是尾节点，更新tail指针
        if nodeToRemove === tail {
            tail = prevNode
        }
        
        _count -= 1
        return nodeToRemove.value
    }
    
    /// 删除第一个元素
    @discardableResult
    func removeFirst() -> T? {
        guard let head = head else { return nil }
        
        if count == 1 {
            self.head = nil
            self.tail = nil
        } else {
            self.head = head.next
        }
        
        _count -= 1
        return head.value
    }
    
    /// 删除最后一个元素
    @discardableResult
    func removeLast() -> T? {
        guard count > 0 else { return nil }
        
        if count == 1 {
            return removeFirst()
        }
        
        guard let prevNode = node(at: count - 2),
              let lastNode = prevNode.next else { return nil }
        
        prevNode.next = nil
        tail = prevNode
        _count -= 1
        
        return lastNode.value
    }
    
    /// 删除所有元素
    func removeAll() {
        head = nil
        tail = nil
        _count = 0
    }
    
    // MARK: - 查找操作
    /// 获取指定索引的元素
    func element(at index: Int) -> T? {
        return node(at: index)?.value
    }
    
    /// 查找第一个匹配的元素索引
    func firstIndex(of value: T) -> Int? where T: Equatable {
        var currentIndex = 0
        var currentNode = head
        
        while let node = currentNode {
            if node.value == value {
                return currentIndex
            }
            currentNode = node.next
            currentIndex += 1
        }
        
        return nil
    }
    
    /// 检查是否包含指定元素
    func contains(_ value: T) -> Bool where T: Equatable {
        return firstIndex(of: value) != nil
    }
    
    // MARK: - 私有辅助方法
    private func node(at index: Int) -> Node? {
        guard index >= 0 && index < count else { return nil }
        
        var currentNode = head
        var currentIndex = 0
        
        while currentIndex < index, let node = currentNode {
            currentNode = node.next
            currentIndex += 1
        }
        
        return currentNode
    }
}

// MARK: - 下标访问
extension SwiftLinkedList {
    /// 下标访问（只读）
    subscript(index: Int) -> T? {
        return element(at: index)
    }
}

// MARK: - Sequence协议
extension SwiftLinkedList: Sequence {
    func makeIterator() -> LinkedListIterator<T> {
        return LinkedListIterator(head: head)
    }
}

// MARK: - 迭代器
struct LinkedListIterator<T>: IteratorProtocol {
    private var currentNode: SwiftLinkedList<T>.Node?
    
    fileprivate init(head: SwiftLinkedList<T>.Node?) {
        currentNode = head
    }
    
    mutating func next() -> T? {
        guard let node = currentNode else { return nil }
        currentNode = node.next
        return node.value
    }
}

// MARK: - CustomStringConvertible
extension SwiftLinkedList: CustomStringConvertible {
    var description: String {
        let elements = map { "\($0)" }
        return "[\(elements.joined(separator: " -> "))]"
    }
}

// MARK: - Collection协议支持
extension SwiftLinkedList: Collection {
    var startIndex: Int { return 0 }
    var endIndex: Int { return count }
    
    func index(after i: Int) -> Int {
        return i + 1
    }
}

// MARK: - 函数式编程支持
extension SwiftLinkedList {
    /// 映射转换
    func map<U>(_ transform: (T) -> U) -> SwiftLinkedList<U> {
        let newList = SwiftLinkedList<U>()
        for element in self {
            newList.append(transform(element))
        }
        return newList
    }
    
    /// 过滤元素
    func filter(_ predicate: (T) -> Bool) -> SwiftLinkedList<T> {
        let newList = SwiftLinkedList<T>()
        for element in self {
            if predicate(element) {
                newList.append(element)
            }
        }
        return newList
    }
    
    /// 归约操作
    func reduce<Result>(_ initialResult: Result, _ nextPartialResult: (Result, T) -> Result) -> Result {
        var result = initialResult
        for element in self {
            result = nextPartialResult(result, element)
        }
        return result
    }
}

// MARK: - 链表工具类
struct LinkedListUtils {
    /// 从数组创建链表
    static func createList<T>(from array: [T]) -> SwiftLinkedList<T> {
        return SwiftLinkedList(array)
    }
    
    /// 将链表转换为数组
    static func toArray<T>(_ list: SwiftLinkedList<T>) -> [T] {
        return Array(list)
    }
    
    /// 反转链表
    static func reverse<T>(_ list: SwiftLinkedList<T>) -> SwiftLinkedList<T> {
        let reversedList = SwiftLinkedList<T>()
        for element in list {
            reversedList.prepend(element)
        }
        return reversedList
    }
    
    /// 合并两个有序链表
    static func mergeSorted<T: Comparable>(_ list1: SwiftLinkedList<T>, _ list2: SwiftLinkedList<T>) -> SwiftLinkedList<T> {
        let mergedList = SwiftLinkedList<T>()
        var array1 = Array(list1)
        var array2 = Array(list2)
        
        var i = 0, j = 0
        
        while i < array1.count && j < array2.count {
            if array1[i] <= array2[j] {
                mergedList.append(array1[i])
                i += 1
            } else {
                mergedList.append(array2[j])
                j += 1
            }
        }
        
        // 添加剩余元素
        while i < array1.count {
            mergedList.append(array1[i])
            i += 1
        }
        
        while j < array2.count {
            mergedList.append(array2[j])
            j += 1
        }
        
        return mergedList
    }
}

// MARK: - 演示和测试
extension SwiftLinkedList {
    /// 运行链表示例
    static func runExample() {
        print("=== Swift链表实现示例 ===")
        
        // 创建链表
        let list = SwiftLinkedList<Int>()
        
        // 添加元素
        print("添加元素: 1, 2, 3, 4, 5")
        [1, 2, 3, 4, 5].forEach { list.append($0) }
        print("链表: \(list)")
        print("长度: \(list.count)")
        
        // 插入元素
        print("\n在索引2插入元素99")
        list.insert(99, at: 2)
        print("链表: \(list)")
        
        // 删除元素
        print("\n删除索引1的元素")
        if let removed = list.remove(at: 1) {
            print("删除的元素: \(removed)")
        }
        print("链表: \(list)")
        
        // 查找元素
        print("\n查找元素99的索引: \(list.firstIndex(of: 99) ?? -1)")
        
        // 访问元素
        print("索引2的元素: \(list[2] ?? -1)")
        
        // 函数式编程
        print("\n=== 函数式编程示例 ===")
        let mappedList = list.map { $0 * 2 }
        print("每个元素乘以2: \(mappedList)")
        
        let filteredList = list.filter { $0 % 2 == 0 }
        print("过滤偶数: \(filteredList)")
        
        let sum = list.reduce(0, +)
        print("所有元素的和: \(sum)")
        
        // 迭代
        print("\n使用for-in循环遍历:")
        for (index, value) in list.enumerated() {
            print("索引\(index): \(value)")
        }
        
        // 工具方法演示
        print("\n=== 工具方法示例 ===")
        let arrayList = LinkedListUtils.createList(from: [10, 20, 30])
        print("从数组创建: \(arrayList)")
        
        let reversedList = LinkedListUtils.reverse(arrayList)
        print("反转链表: \(reversedList)")
        
        let list1 = LinkedListUtils.createList(from: [1, 3, 5])
        let list2 = LinkedListUtils.createList(from: [2, 4, 6])
        let mergedList = LinkedListUtils.mergeSorted(list1, list2)
        print("合并有序链表: \(mergedList)")
    }
    
    /// 性能测试
    static func performanceTest() {
        print("\n=== 性能测试 ===")
        
        let list = SwiftLinkedList<Int>()
        let testSize = 10000
        
        // 测试添加性能
        let startTime1 = CFAbsoluteTimeGetCurrent()
        for i in 0..<testSize {
            list.append(i)
        }
        let time1 = CFAbsoluteTimeGetCurrent() - startTime1
        
        // 测试查找性能
        let startTime2 = CFAbsoluteTimeGetCurrent()
        for i in 0..<1000 {
            _ = list.element(at: i)
        }
        let time2 = CFAbsoluteTimeGetCurrent() - startTime2
        
        print("添加\(testSize)个元素耗时: \(String(format: "%.4f", time1))秒")
        print("查找1000次元素耗时: \(String(format: "%.4f", time2))秒")
        
        // 与Array对比
        var array = [Int]()
        let startTime3 = CFAbsoluteTimeGetCurrent()
        for i in 0..<testSize {
            array.append(i)
        }
        let time3 = CFAbsoluteTimeGetCurrent() - startTime3
        
        print("Array添加\(testSize)个元素耗时: \(String(format: "%.4f", time3))秒")
        print("链表vs数组添加性能比: \(String(format: "%.2f", time1 / time3))")
    }
}
