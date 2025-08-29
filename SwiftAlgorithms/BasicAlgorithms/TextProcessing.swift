import Foundation

// MARK: - 中文数字转换器
/// Swift风格的中文数字转阿拉伯数字实现

struct ChineseNumberConverter {
    
    // MARK: - 私有常量
    private static let unitMap: [String: Int] = [
        "亿": 100_000_000,
        "万": 10_000,
        "千": 1_000,
        "百": 100,
        "十": 10
    ]
    
    private static let digitMap: [String: Int] = [
        "零": 0, "一": 1, "二": 2, "三": 3, "四": 4,
        "五": 5, "六": 6, "七": 7, "八": 8, "九": 9
    ]
    
    // MARK: - 主转换函数
    /// 将中文数字字符串转换为阿拉伯数字
    static func convertToArabic(_ chineseNumber: String) -> Int {
        guard !chineseNumber.isEmpty else { return 0 }
        
        var result = 0      // 最终结果
        var temp = 0        // 临时结果（千百十位）
        var current = 0     // 当前数字
        
        // 将字符串分解为字符数组
        let characters = Array(chineseNumber)
        
        for char in characters {
            let charString = String(char)
            
            if let unit = unitMap[charString] {
                // 处理数字单位
                current = handleUnit(charString, current: current, temp: &temp, result: &result, unit: unit)
            } else if let digit = digitMap[charString] {
                // 处理基本数字
                current = digit
            }
        }
        
        return result + temp + current
    }
    
    // MARK: - 处理单位的私有方法
    private static func handleUnit(_ unitString: String, current: Int, temp: inout Int, result: inout Int, unit: Int) -> Int {
        var currentValue = current
        
        // 特殊处理"十"开头的情况
        if currentValue == 0 && unitString == "十" {
            currentValue = 1
        }
        
        switch unitString {
        case "万":
            result += (temp + currentValue) * unit
            temp = 0
        case "亿":
            result = (result + temp + currentValue) * unit
            temp = 0
        default:  // 千、百、十
            temp += currentValue * unit
        }
        
        return 0  // 重置当前数字
    }
    
    // MARK: - 批量转换
    /// 批量转换中文数字数组
    static func batchConvert(_ chineseNumbers: [String]) -> [Int] {
        return chineseNumbers.map { convertToArabic($0) }
    }
    
    /// 演示函数
    static func runExample() {
        print("=== 中文数字转换示例 ===")
        
        let testCases = [
            "五十六万七千九百零一",
            "五千四百二十八万九千三百二十一",
            "五亿零一十万零八十",
            "九千万零一十二",
            "二万零一百零七",
            "七千七百七十七",
            "十",
            "十七",
            "二十",
            "零"
        ]
        
        for testCase in testCases {
            let result = convertToArabic(testCase)
            print("输入: \(testCase) -> 输出: \(result)")
        }
        
        // 批量转换演示
        print("\n批量转换结果: \(batchConvert(testCases))")
    }
}

// MARK: - String扩展：中文数字转换
extension String {
    /// 将当前字符串作为中文数字转换为阿拉伯数字
    var chineseToArabic: Int {
        return ChineseNumberConverter.convertToArabic(self)
    }
    
    /// 检查是否为有效的中文数字
    var isValidChineseNumber: Bool {
        let validChars = Set("零一二三四五六七八九十百千万亿")
        return Set(self).isSubset(of: validChars)
    }
}

// MARK: - 句子缩写器
/// Swift风格的句子首字母缩写实现

struct SentenceAbbreviator {
    
    /// 生成句子的首字母缩写
    static func abbreviate(_ sentence: String) -> String {
        return sentence
            .components(separatedBy: .whitespacesAndNewlines)  // 按空格分词
            .filter { !$0.isEmpty }  // 过滤空字符串
            .compactMap { $0.first?.uppercased() }  // 取首字母并转大写
            .joined()  // 连接成字符串
    }
    
    /// 生成多个句子的缩写
    static func abbreviateMultiple(_ sentences: [String]) -> [String] {
        return sentences.map { abbreviate($0) }
    }
    
    /// 交互式处理（模拟原C++程序）
    static func interactiveProcess() {
        print("=== 句子缩写生成器 ===")
        print("请输入要处理的句子数量:")
        
        guard let input = readLine(), let count = Int(input), count > 0 else {
            print("无效输入")
            return
        }
        
        print("请输入 \(count) 个句子:")
        var results: [String] = []
        
        for i in 1...count {
            print("句子 \(i):")
            if let sentence = readLine() {
                let abbreviation = abbreviate(sentence)
                results.append(abbreviation)
                print("缩写: \(abbreviation)")
            }
        }
        
        print("\n所有缩写结果:")
        results.enumerated().forEach { index, abbr in
            print("句子\(index + 1): \(abbr)")
        }
    }
    
    /// 演示函数
    static func runExample() {
        print("=== 句子缩写示例 ===")
        
        let testSentences = [
            "hello world swift programming",
            "artificial intelligence machine learning",
            "ios development with swift",
            "the quick brown fox jumps",
            "data structures and algorithms"
        ]
        
        for sentence in testSentences {
            let abbreviation = abbreviate(sentence)
            print("\"\(sentence)\" -> \(abbreviation)")
        }
        
        // 批量处理演示
        let abbreviations = abbreviateMultiple(testSentences)
        print("\n批量处理结果: \(abbreviations)")
    }
}

// MARK: - String扩展：句子缩写
extension String {
    /// 生成当前字符串的首字母缩写
    var abbreviation: String {
        return SentenceAbbreviator.abbreviate(self)
    }
    
    /// 按句子分割并生成缩写
    var sentenceAbbreviations: [String] {
        return self
            .components(separatedBy: CharacterSet(charactersIn: ".!?"))
            .filter { !$0.trimmingCharacters(in: .whitespacesAndNewlines).isEmpty }
            .map { $0.trimmingCharacters(in: .whitespacesAndNewlines).abbreviation }
    }
}

// MARK: - 字符处理工具
struct CharacterUtils {
    /// 检查字符是否为大写字母
    static func isUppercase(_ char: Character) -> Bool {
        return char.isUppercase
    }
    
    /// 将字符转换为大写
    static func toUppercase(_ char: Character) -> Character {
        return Character(char.uppercased())
    }
    
    /// 将字符转换为小写
    static func toLowercase(_ char: Character) -> Character {
        return Character(char.lowercased())
    }
}

// MARK: - Character扩展：便利方法
extension Character {
    /// 转换为大写字符
    var uppercased: Character {
        return CharacterUtils.toUppercase(self)
    }
    
    /// 转换为小写字符
    var lowercased: Character {
        return CharacterUtils.toLowercase(self)
    }
    
    /// 检查是否为大写字母
    var isUppercased: Bool {
        return CharacterUtils.isUppercase(self)
    }
}

// MARK: - 综合示例运行器
struct TextProcessingExample {
    static func runAll() {
        print("🚀 Swift文本处理算法示例\n")
        
        ChineseNumberConverter.runExample()
        print()
        SentenceAbbreviator.runExample()
        
        // 演示扩展方法
        print("\n=== 扩展方法演示 ===")
        print("\"五十六万七千九百零一\".chineseToArabic: \(\"五十六万七千九百零一\".chineseToArabic)")
        print("\"hello world swift\".abbreviation: \(\"hello world swift\".abbreviation)")
        print("\"What is AI? Machine learning rocks!\".sentenceAbbreviations: \(\"What is AI? Machine learning rocks!\".sentenceAbbreviations)")
        
        // 字符处理演示
        let char: Character = "a"
        print("Character 'a' uppercased: \(char.uppercased)")
        print("Character 'A' isUppercased: \(Character("A").isUppercased)")
    }
}
