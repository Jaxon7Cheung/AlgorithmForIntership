import Foundation

// MARK: - 有效的字母异位词
/// Swift风格实现，充分利用语法糖和高阶函数

struct AnagramChecker {
    
    /// 方法1: 使用字典计数 - Swift语法糖版本
    static func isAnagram(_ s: String, _ t: String) -> Bool {
        // guard语句优雅处理边界条件
        guard s.count == t.count else { return false }
        
        // 使用Swift的字典和reduce高阶函数
        let sCount = s.reduce(into: [:]) { counts, char in
            counts[char, default: 0] += 1
        }
        
        let tCount = t.reduce(into: [:]) { counts, char in
            counts[char, default: 0] += 1
        }
        
        return sCount == tCount
    }
    
    /// 方法2: 使用数组计数 - 针对小写字母优化
    static func isAnagramOptimized(_ s: String, _ t: String) -> Bool {
        guard s.count == t.count else { return false }
        
        var counts = Array(repeating: 0, count: 26)
        
        // 使用zip函数同时遍历两个字符串
        for (sChar, tChar) in zip(s, t) {
            counts[Int(sChar.asciiValue! - Character("a").asciiValue!)] += 1
            counts[Int(tChar.asciiValue! - Character("a").asciiValue!)] -= 1
        }
        
        // 使用allSatisfy高阶函数检查
        return counts.allSatisfy { $0 == 0 }
    }
    
    /// 方法3: 排序比较 - 最简洁的函数式写法
    static func isAnagramBySorting(_ s: String, _ t: String) -> Bool {
        guard s.count == t.count else { return false }
        return s.sorted() == t.sorted()
    }
    
    /// 方法4: 使用Set检查是否包含相同字符（不考虑频次）
    static func hasSameCharacters(_ s: String, _ t: String) -> Bool {
        return Set(s) == Set(t)
    }
    
    /// 演示函数
    static func runExample() {
        print("=== 字母异位词检查示例 ===")
        
        let testCases = [
            ("anagram", "nagaram", true),
            ("rat", "cat", false),
            ("listen", "silent", true),
            ("hello", "bello", false)
        ]
        
        for (s, t, expected) in testCases {
            let result1 = isAnagram(s, t)
            let result2 = isAnagramOptimized(s, t)
            let result3 = isAnagramBySorting(s, t)
            
            print("测试: \"\(s)\" 和 \"\(t)\"")
            print("期望: \(expected), 字典方法: \(result1), 数组方法: \(result2), 排序方法: \(result3)")
            print("---")
        }
    }
}

// MARK: - String扩展：添加字母异位词检查方法
extension String {
    /// 检查是否与另一个字符串是字母异位词
    func isAnagram(of other: String) -> Bool {
        return AnagramChecker.isAnagram(self, other)
    }
    
    /// 获取所有字母异位词（从给定数组中）
    func anagrams(from strings: [String]) -> [String] {
        return strings.filter { self.isAnagram(of: $0) }
    }
}

// MARK: - 数字各位偶数之和
/// Swift风格实现，使用字符串操作和函数式编程

struct DigitProcessor {
    
    /// 计算数字各位中偶数的和
    static func sumOfEvenDigits(_ number: Int) -> Int {
        return String(abs(number))  // 转为字符串并取绝对值
            .compactMap { $0.wholeNumberValue }  // 转换为数字数组
            .filter { $0 % 2 == 0 }  // 筛选偶数
            .reduce(0, +)  // 求和
    }
    
    /// 批量处理多个数字
    static func processNumbers(_ numbers: [Int]) -> [Int] {
        return numbers.map { sumOfEvenDigits($0) }
    }
    
    /// 交互式处理（模拟原C++的while循环输入）
    static func interactiveProcess() {
        print("=== 数字各位偶数之和计算器 ===")
        print("请输入数字（输入 'quit' 退出）:")
        
        while true {
            guard let input = readLine(), input.lowercased() != "quit" else {
                print("程序结束")
                break
            }
            
            if let number = Int(input) {
                let sum = sumOfEvenDigits(number)
                print("数字 \(number) 各位偶数之和: \(sum)\n")
            } else {
                print("请输入有效的数字\n")
            }
        }
    }
    
    /// 演示函数
    static func runExample() {
        print("=== 数字各位偶数和示例 ===")
        
        let testNumbers = [1234, 5678, 13579, 2468, 0, -1234]
        
        for number in testNumbers {
            let sum = sumOfEvenDigits(number)
            print("数字 \(number) 的各位偶数和: \(sum)")
        }
        
        print("\n批量处理结果: \(processNumbers(testNumbers))")
    }
}

// MARK: - Int扩展：为整数添加数位操作方法
extension Int {
    /// 获取各个数位
    var digits: [Int] {
        return String(abs(self)).compactMap { $0.wholeNumberValue }
    }
    
    /// 各位偶数之和
    var evenDigitsSum: Int {
        return DigitProcessor.sumOfEvenDigits(self)
    }
    
    /// 各位奇数之和
    var oddDigitsSum: Int {
        return digits.filter { $0 % 2 != 0 }.reduce(0, +)
    }
    
    /// 数位个数
    var digitCount: Int {
        return digits.count
    }
    
    /// 是否为回文数
    var isPalindrome: Bool {
        let digitArray = digits
        return digitArray == digitArray.reversed()
    }
}

// MARK: - 示例运行器
struct BasicAlgorithmsExample {
    static func runAll() {
        print("🚀 Swift基础算法示例\n")
        
        AnagramChecker.runExample()
        print()
        DigitProcessor.runExample()
        
        // 演示扩展方法
        print("\n=== 扩展方法演示 ===")
        print("\"listen\".isAnagram(of: \"silent\"): \(\"listen\".isAnagram(of: \"silent\"))")
        print("1234.evenDigitsSum: \(1234.evenDigitsSum)")
        print("1234.oddDigitsSum: \(1234.oddDigitsSum)")
        print("12321.isPalindrome: \(12321.isPalindrome)")
    }
}
