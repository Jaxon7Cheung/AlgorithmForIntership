import Foundation

// MARK: - 开方算法
/// Swift风格的开方实现，支持多种精度和类型

struct MathOperations {
    
    // MARK: - 整数平方根
    /// 计算非负整数的平方根（向下取整）
    static func integerSquareRoot(of number: Int) -> Int? {
        guard number >= 0 else { return nil }
        guard number > 1 else { return number }
        
        var left = 1
        var right = number
        var result = 0
        
        while left <= right {
            let mid = left + (right - left) / 2
            let square = mid * mid
            
            switch square.compare(to: number) {
            case .equal:
                return mid
            case .less:
                left = mid + 1
                result = mid  // 保存可能的答案
            case .greater:
                right = mid - 1
            }
        }
        
        return result
    }
    
    // MARK: - 牛顿迭代法求平方根
    /// 使用牛顿迭代法计算平方根（高精度）
    static func newtonSquareRoot(of number: Double, precision: Double = 1e-10) -> Double? {
        guard number >= 0 else { return nil }
        guard number > 0 else { return 0 }
        
        var x = number
        
        repeat {
            let newX = 0.5 * (x + number / x)
            if abs(x - newX) < precision {
                return newX
            }
            x = newX
        } while true
    }
    
    // MARK: - N次方根
    /// 计算N次方根，支持负数和小数
    static func nthRoot(of number: Double, n: Int, precision: Double = 1e-13) -> Double? {
        // 偶数次根不能是负数
        guard !(number < 0 && n % 2 == 0) else { return nil }
        guard n > 0 else { return nil }
        guard number != 0 else { return 0 }
        
        // 处理负数情况
        let isNegative = number < 0
        let absNumber = abs(number)
        
        // 确定搜索区间
        var left: Double = absNumber < 1 ? absNumber : 0
        var right: Double = absNumber < 1 ? 1 : absNumber
        
        // 特殊情况：n = 1
        guard n != 1 else { return number }
        
        var result: Double = 0
        
        while right - left > precision {
            let mid = (left + right) / 2
            let midPower = pow(mid, Double(n))
            
            if abs(midPower - absNumber) < precision {
                result = mid
                break
            } else if midPower < absNumber {
                left = mid
                result = mid
            } else {
                right = mid
            }
        }
        
        return isNegative ? -result : result
    }
    
    // MARK: - 快速幂算法
    /// 计算 base^exponent，支持整数指数
    static func fastPower(_ base: Double, _ exponent: Int) -> Double {
        guard exponent != 0 else { return 1 }
        
        let isNegativeExponent = exponent < 0
        var exp = abs(exponent)
        var result = 1.0
        var currentBase = base
        
        while exp > 0 {
            if exp % 2 == 1 {
                result *= currentBase
            }
            currentBase *= currentBase
            exp /= 2
        }
        
        return isNegativeExponent ? 1.0 / result : result
    }
    
    /// 演示函数
    static func runExample() {
        print("=== 开方算法示例 ===")
        
        // 整数平方根测试
        let integerTests = [0, 1, 4, 8, 9, 16, 25, 81]
        print("整数平方根测试:")
        for num in integerTests {
            if let sqrt = integerSquareRoot(of: num) {
                print("√\(num) = \(sqrt)")
            }
        }
        
        print("\n牛顿迭代法平方根测试:")
        let doubleTests = [0.0, 1.0, 4.0, 8.0, 25.0, 2.0]
        for num in doubleTests {
            if let sqrt = newtonSquareRoot(of: num) {
                print("√\(num) ≈ \(String(format: "%.10f", sqrt))")
            }
        }
        
        print("\nN次方根测试:")
        let nthRootTests: [(Double, Int)] = [
            (8.0, 3),     // 立方根
            (16.0, 4),    // 四次方根
            (27.0, 3),    // 立方根
            (0.04, 2),    // 平方根
            (-8.0, 3),    // 负数立方根
            (-512.0, 9)   // 负数九次方根
        ]
        
        for (number, n) in nthRootTests {
            if let result = nthRoot(of: number, n: n) {
                print("\(number)^(1/\(n)) ≈ \(String(format: "%.10f", result))")
            } else {
                print("\(number)^(1/\(n)) = 无效（偶数次根不能是负数）")
            }
        }
        
        print("\n快速幂测试:")
        let powerTests: [(Double, Int)] = [
            (2.0, 10),
            (3.0, 4),
            (2.0, -3),
            (5.0, 0)
        ]
        
        for (base, exp) in powerTests {
            let result = fastPower(base, exp)
            print("\(base)^(\(exp)) = \(result)")
        }
    }
}

// MARK: - Double扩展：添加数学运算方法
extension Double {
    /// 计算平方根
    var squareRoot: Double? {
        return MathOperations.newtonSquareRoot(of: self)
    }
    
    /// 计算N次方根
    func nthRoot(_ n: Int) -> Double? {
        return MathOperations.nthRoot(of: self, n: n)
    }
    
    /// 快速幂运算
    func power(_ exponent: Int) -> Double {
        return MathOperations.fastPower(self, exponent)
    }
    
    /// 比较方法（用于替代C++的比较逻辑）
    func compare(to other: Double) -> ComparisonResult {
        if self < other { return .less }
        if self > other { return .greater }
        return .equal
    }
}

// MARK: - Int扩展：添加数学运算方法
extension Int {
    /// 整数平方根
    var integerSquareRoot: Int? {
        return MathOperations.integerSquareRoot(of: self)
    }
    
    /// 快速幂运算（整数版本）
    func power(_ exponent: Int) -> Int {
        return Int(MathOperations.fastPower(Double(self), exponent))
    }
    
    /// 比较方法
    func compare(to other: Int) -> ComparisonResult {
        if self < other { return .less }
        if self > other { return .greater }
        return .equal
    }
}

// MARK: - 数学常量和工具
enum MathConstants {
    static let defaultPrecision: Double = 1e-10
    static let highPrecision: Double = 1e-15
    static let lowPrecision: Double = 1e-6
}

// MARK: - 性能测试
extension MathOperations {
    /// 性能对比测试
    static func performanceTest() {
        print("\n=== 性能测试 ===")
        
        let testNumbers = Array(1...10000)
        
        // 测试整数平方根性能
        let startTime1 = CFAbsoluteTimeGetCurrent()
        for number in testNumbers {
            _ = integerSquareRoot(of: number)
        }
        let time1 = CFAbsoluteTimeGetCurrent() - startTime1
        
        // 测试牛顿迭代法性能
        let startTime2 = CFAbsoluteTimeGetCurrent()
        for number in testNumbers {
            _ = newtonSquareRoot(of: Double(number))
        }
        let time2 = CFAbsoluteTimeGetCurrent() - startTime2
        
        // 测试系统sqrt性能
        let startTime3 = CFAbsoluteTimeGetCurrent()
        for number in testNumbers {
            _ = sqrt(Double(number))
        }
        let time3 = CFAbsoluteTimeGetCurrent() - startTime3
        
        print("整数平方根: \(String(format: "%.4f", time1))秒")
        print("牛顿迭代法: \(String(format: "%.4f", time2))秒")
        print("系统sqrt: \(String(format: "%.4f", time3))秒")
    }
}
