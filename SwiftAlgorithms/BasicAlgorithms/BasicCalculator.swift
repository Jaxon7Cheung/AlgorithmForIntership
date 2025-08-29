import Foundation

// MARK: - 计算器节点定义
/// 用于表示计算器中的操作数和操作符
struct CalculatorNode {
    let value: Int
    let operatorChar: Character
    let isOperator: Bool
    
    init(value: Int) {
        self.value = value
        self.operatorChar = " "
        self.isOperator = false
    }
    
    init(operatorChar: Character) {
        self.value = 0
        self.operatorChar = operatorChar
        self.isOperator = true
    }
}

// MARK: - 基本计算器
/// Swift风格的表达式计算器，支持括号但不支持小数

class BasicCalculator {
    
    // MARK: - 私有属性
    private var operatorStack: [CalculatorNode] = []
    private var outputQueue: [CalculatorNode] = []
    
    // 操作符优先级映射
    private let operatorPrecedence: [Character: Int] = [
        "+": 1, "-": 1, "*": 2, "/": 2, "(": 0
    ]
    
    // MARK: - 公共方法
    /// 计算表达式的值
    func calculate(_ expression: String) -> Int {
        // 清空之前的状态
        operatorStack.removeAll()
        outputQueue.removeAll()
        
        // 中缀转后缀
        let postfixExpression = infixToPostfix(expression)
        
        // 计算后缀表达式
        return evaluatePostfix(postfixExpression)
    }
    
    // MARK: - 中缀转后缀表达式
    private func infixToPostfix(_ expression: String) -> [CalculatorNode] {
        let cleanedExpression = expression.replacingOccurrences(of: " ", with: "")
        var i = 0
        var previousChar: Character = "("  // 用于处理一元运算符
        
        while i < cleanedExpression.count {
            let char = cleanedExpression[cleanedExpression.index(cleanedExpression.startIndex, offsetBy: i)]
            
            switch char {
            case "(":
                previousChar = "("
                operatorStack.append(CalculatorNode(operatorChar: "("))
                i += 1
                
            case ")":
                previousChar = ")"
                // 弹出操作符直到遇到左括号
                while let top = operatorStack.last, top.operatorChar != "(" {
                    outputQueue.append(operatorStack.removeLast())
                }
                // 弹出左括号
                if !operatorStack.isEmpty {
                    operatorStack.removeLast()
                }
                i += 1
                
            case "0"..."9":
                previousChar = "1"  // 标记为数字
                // 解析多位数字
                let (number, nextIndex) = parseNumber(from: cleanedExpression, startIndex: i)
                outputQueue.append(CalculatorNode(value: number))
                i = nextIndex
                
            case "+", "-", "*", "/":
                // 处理一元运算符（负号）
                if (previousChar == "(" || previousChar == " ") && char == "-" {
                    outputQueue.append(CalculatorNode(value: 0))  // 添加0作为被减数
                }
                
                // 处理操作符优先级
                while let top = operatorStack.last,
                      let currentPrecedence = operatorPrecedence[char],
                      let topPrecedence = operatorPrecedence[top.operatorChar],
                      currentPrecedence <= topPrecedence && top.operatorChar != "(" {
                    outputQueue.append(operatorStack.removeLast())
                }
                
                operatorStack.append(CalculatorNode(operatorChar: char))
                previousChar = char
                i += 1
                
            default:
                i += 1
            }
        }
        
        // 将剩余操作符加入输出队列
        while !operatorStack.isEmpty {
            outputQueue.append(operatorStack.removeLast())
        }
        
        return outputQueue
    }
    
    // MARK: - 解析数字
    private func parseNumber(from expression: String, startIndex: Int) -> (Int, Int) {
        var number = 0
        var index = startIndex
        
        while index < expression.count {
            let char = expression[expression.index(expression.startIndex, offsetBy: index)]
            if char.isNumber {
                number = number * 10 + Int(String(char))!
                index += 1
            } else {
                break
            }
        }
        
        return (number, index)
    }
    
    // MARK: - 计算后缀表达式
    private func evaluatePostfix(_ postfixExpression: [CalculatorNode]) -> Int {
        var stack: [Int] = []
        
        for node in postfixExpression {
            if !node.isOperator {
                stack.append(node.value)
            } else {
                guard stack.count >= 2 else { return 0 }
                
                let operand2 = stack.removeLast()
                let operand1 = stack.removeLast()
                
                let result = performOperation(operand1, operand2, node.operatorChar)
                stack.append(result)
            }
        }
        
        return stack.last ?? 0
    }
    
    // MARK: - 执行运算
    private func performOperation(_ operand1: Int, _ operand2: Int, _ operator: Character) -> Int {
        switch `operator` {
        case "+":
            return operand1 + operand2
        case "-":
            return operand1 - operand2
        case "*":
            return operand1 * operand2
        case "/":
            return operand2 != 0 ? operand1 / operand2 : 0
        default:
            return 0
        }
    }
}

// MARK: - 增强型计算器
/// 支持更多功能的计算器

class AdvancedCalculator: BasicCalculator {
    
    /// 计算表达式并返回详细结果
    func calculateWithDetails(_ expression: String) -> (result: Int, steps: [String]) {
        var steps: [String] = []
        steps.append("原表达式: \(expression)")
        
        let result = calculate(expression)
        steps.append("计算结果: \(result)")
        
        return (result, steps)
    }
    
    /// 批量计算多个表达式
    func batchCalculate(_ expressions: [String]) -> [Int] {
        return expressions.map { calculate($0) }
    }
    
    /// 验证表达式是否有效
    func isValidExpression(_ expression: String) -> Bool {
        let validChars = Set("0123456789+-*/() ")
        return Set(expression).isSubset(of: validChars)
    }
}

// MARK: - String扩展：表达式计算
extension String {
    /// 计算当前字符串表达式的值
    func calculateExpression() -> Int? {
        let calculator = BasicCalculator()
        guard BasicCalculator().isValid(self) else { return nil }
        return calculator.calculate(self)
    }
    
    /// 检查是否为有效的数学表达式
    var isValidMathExpression: Bool {
        return AdvancedCalculator().isValidExpression(self)
    }
}

// MARK: - BasicCalculator扩展：验证方法
extension BasicCalculator {
    /// 验证表达式是否有效
    func isValid(_ expression: String) -> Bool {
        let validChars = Set("0123456789+-*/() ")
        return Set(expression).isSubset(of: validChars) && !expression.isEmpty
    }
}

// MARK: - 计算器工厂
struct CalculatorFactory {
    enum CalculatorType {
        case basic
        case advanced
    }
    
    static func createCalculator(type: CalculatorType) -> BasicCalculator {
        switch type {
        case .basic:
            return BasicCalculator()
        case .advanced:
            return AdvancedCalculator()
        }
    }
}

// MARK: - 演示和测试
extension BasicCalculator {
    /// 运行计算器示例
    static func runExample() {
        print("=== 基本计算器示例 ===")
        
        let calculator = BasicCalculator()
        
        let testExpressions = [
            "1 + 4 + 5 + 2 * 3 + 6 / 2",
            "-1 + (-(4+5+2)*3) + 6/ 2",
            "1 + 6",
            "(1 + 2) * 3",
            "2 * (3 + 4)",
            "100 / (2 + 3) * 4",
            "-(2 + 3)",
            "10 - 2 * 3"
        ]
        
        for expression in testExpressions {
            let result = calculator.calculate(expression)
            print("\"\(expression)\" = \(result)")
        }
        
        // 测试高级计算器
        print("\n=== 高级计算器示例 ===")
        let advancedCalculator = AdvancedCalculator()
        
        let complexExpression = "-1 + (-(4+5+2)*3) + 6/ 2"
        let (result, steps) = advancedCalculator.calculateWithDetails(complexExpression)
        
        print("计算步骤:")
        steps.forEach { print("  \($0)") }
        
        // 批量计算
        let batchResults = advancedCalculator.batchCalculate(testExpressions)
        print("\n批量计算结果: \(batchResults)")
        
        // 验证表达式
        let validExpression = "1 + 2 * 3"
        let invalidExpression = "1 + 2 * abc"
        print("\n表达式验证:")
        print("\"\(validExpression)\" 是否有效: \(advancedCalculator.isValidExpression(validExpression))")
        print("\"\(invalidExpression)\" 是否有效: \(advancedCalculator.isValidExpression(invalidExpression))")
    }
    
    /// 交互式计算器
    static func interactiveCalculator() {
        print("=== 交互式计算器 ===")
        print("请输入数学表达式（输入 'quit' 退出）:")
        
        let calculator = AdvancedCalculator()
        
        while true {
            guard let input = readLine(), input.lowercased() != "quit" else {
                print("计算器已退出")
                break
            }
            
            if calculator.isValidExpression(input) {
                let result = calculator.calculate(input)
                print("结果: \(result)\n")
            } else {
                print("无效的表达式，请重新输入\n")
            }
        }
    }
}
