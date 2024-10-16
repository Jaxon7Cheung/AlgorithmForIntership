//
//  main.cpp
//  lt&al
//
//  Created by 张旭洋 on 2024/10/7.
//

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

// 中文数字转阿拉伯数字
int cvtNum(const string& src) {
    // 定义数字单位映射表
    // 键为中文数字单位，值为对应的阿拉伯数字值
    unordered_map<string, int> multi = {
        {"亿", 100000000}, {"万", 10000}, {"千", 1000}, {"百", 100}, {"十", 10}
    };
    
    // 定义基本数字映射表
    // 键为中文数字字符，值为对应的阿拉伯数字
    unordered_map<string, int> base = {
        {"零", 0}, {"一", 1}, {"二", 2}, {"三", 3}, {"四", 4}, {"五", 5},
        {"六", 6}, {"七", 7}, {"八", 8}, {"九", 9}
    };

    int result = 0;  // 存储最终结果
    int temp = 0;    // 存储临时结果，用于处理千、百、十位数
    int current = 0; // 存储当前处理的数字

    // 每次处理3个字符（C++ UTF-8编码中文，一个中文字符长度为3）
    for (int i = 0; i < src.length(); i += 3) {
        string curr = src.substr(i, 3);
        
        if (multi.count(curr)) {  // 如果当前字符是数字单位
            // 特殊处理"十"开头的情况，例如"十一"应该是11而不是110
            current = (current == 0 && curr == "十") ? 1 : current;
            
            if (curr == "万") {  // 处理"万"位
                // 将当前累积的结果乘以10000，加到最终结果上
                result += (temp + current) * 10000;
                temp = 0;  // 重置临时结果
            } else if (curr == "亿") {  // 处理"亿"位
                // 将当前所有累积的结果乘以100000000
                result = (result + temp + current) * 100000000;
                temp = 0;  // 重置临时结果
            } else {  // 处理其他单位（千、百、十）
                // 将当前数字乘以对应单位，加到临时结果上
                temp += current * multi[curr];
            }
            current = 0;  // 重置当前数字
        } else if (base.count(curr)) {  // 如果当前字符是基本数字
            current = base[curr];  // 获取当前数字的值
        }
    }

    // 合并最终结果：累加result（亿、万位）、temp（千百十位）和current（个位）
    return result + temp + current;
}

int main(void) {
    // 测试用例数组，包含各种不同情况的中文数字表示
    string tests[] = {
        "五十六万七千九百零一",  // 常规数字
        "五千四百二十八万九千三百二十一",  // 大数
        "五亿零一十万零八十",  // 包含"亿"和"零"的数字
        "九千万零一十二",  // "零"后面是十位数
        "二万零一百零七",  // 多个"零"
        "七千七百七十七",
        "十",  // 特殊情况：单个"十"
        "十七",  // "十"开头的数字
        "二十",  // 整十数
        "零"  // 特殊情况：零
    };

    // 遍历测试用例数组，将每个中文数字转换为阿拉伯数字并输出结果
    for (string test : tests) {
        cout << "Input: " << test << ", Result: " << cvtNum(test) << endl;
    }

    return 0;
}



// 加了一个Bool值处理连续零的情况
//#include <iostream>
//#include <string>
//#include <unordered_map>
//using namespace std;
//
//// 中文数字转阿拉伯数字
//int cvtNum(const string& src) {
//    // 定义数字单位映射表
//    // 键为中文数字单位，值为对应的阿拉伯数字值
//    unordered_map<string, int> multi = {
//        {"亿", 100000000}, {"万", 10000}, {"千", 1000}, {"百", 100}, {"十", 10}
//    };
//    
//    // 定义基本数字映射表
//    // 键为中文数字字符，值为对应的阿拉伯数字
//    unordered_map<string, int> base = {
//        {"零", 0}, {"一", 1}, {"二", 2}, {"三", 3}, {"四", 4}, {"五", 5},
//        {"六", 6}, {"七", 7}, {"八", 8}, {"九", 9}
//    };
//
//    int result = 0;  // 存储最终结果
//    int temp = 0;    // 存储临时结果，用于处理千、百、十位数
//    int current = 0; // 存储当前处理的数字
//    bool hasPrefix = false;  // 标记是否遇到了数字单位，用于处理"零"
//
//    // 每次处理3个字符（一个中文数字）
//    for (int i = 0; i < src.length(); i += 3) {
//        string curr = src.substr(i, 3);
//        
//        if (multi.count(curr)) {  // 如果当前字符是数字单位
//            // 特殊处理"十"开头的情况，例如"十一"应该是11而不是110
//            current = (current == 0 && curr == "十") ? 1 : current;
//            
//            if (curr == "万") {  // 处理"万"位
//                // 将当前累积的结果乘以10000，加到最终结果上
//                result += (temp + current) * 10000;
//                temp = 0;  // 重置临时结果
//            } else if (curr == "亿") {  // 处理"亿"位
//                // 将当前所有累积的结果乘以100000000
//                result = (result + temp + current) * 100000000;
//                temp = 0;  // 重置临时结果
//            } else {  // 处理其他单位（千、百、十）
//                // 将当前数字乘以对应单位，加到临时结果上
//                temp += current * multi[curr];
//            }
//            current = 0;  // 重置当前数字
//            hasPrefix = true;  // 标记已经遇到数字单位
//        } else if (base.count(curr)) {  // 如果当前字符是基本数字
//            current = base[curr];  // 获取当前数字的值
//            // 处理连续的"零"，例如"一万零零一"中间的"零"
//             if (!hasPrefix && temp == 0 && result == 0 && current == 0) continue;
//            hasPrefix = false;  // 重置数字单位标记
//        }
//    }
//
//    // 合并最终结果：累加result（亿、万位）、temp（千百十位）和current（个位）
//    return result + temp + current;
//}
//
//int main(void) {
//    // 测试用例数组，包含各种不同情况的中文数字表示
//    const string tests[] = {
//        "五十六万七千九百零一",  // 常规数字
//        "五千四百二十八万九千三百二十一",  // 大数
//        "五亿零一十万零八十",  // 包含"亿"和"零"的数字
//        "九千万零一十二",  // "零"后面是十位数
//        "二万零一百零七",  // 多个"零"
//        "十",  // 特殊情况：单个"十"
//        "十七",  // "十"开头的数字
//        "二十",  // 整十数
//        "零"  // 特殊情况：零
//    };
//
//    // 遍历测试用例数组，将每个中文数字转换为阿拉伯数字并输出结果
//    for (const auto& test : tests) {
//        cout << "Input: " << test << ", Result: " << cvtNum(test) << endl;
//    }
//
//    return 0;
//}

// 这种情况无法处理十开头的数字
//#include <iostream>
//#include <string>
//#include <unordered_map>
//using namespace std;
//
//int cvtNum(string src) {
//    unordered_map<string, int> multi;
//    multi["亿"] = 1e8;
//    multi["万"] = 1e4;
//    multi["千"] = 1e3;
//    multi["百"] = 1e2;
//    multi["十"] = 1e1;
//
//    unordered_map<string, int> base;
//    base["零"] = 0;
//    base["一"] = 1;
//    base["二"] = 2;
//    base["三"] = 3;
//    base["四"] = 4;
//    base["五"] = 5;
//    base["六"] = 6;
//    base["七"] = 7;
//    base["八"] = 8;
//    base["九"] = 9;
//
//    cout << "current src: " << src << endl;
//
//    int len = src.length();
//    int dst = 0, yi_dst = 0, wan_dst = 0;
//    int currval = 0;
//    for(int i = 0; i < len; i += 3) {
//        string curr = src.substr(i, 3);
//        if (multi.count(curr)) {
//            if (curr == "亿") {
//                yi_dst = (dst + currval) * multi[curr];
//                dst = 0;
//            } else if (curr == "万") {
//                wan_dst = (dst + currval) * multi[curr];
//                dst = 0;
//            } else {
//                dst += currval * multi[curr];
//            }
//            currval = 0;
//        } else {
//            currval = base[curr];
//        }
//    }
//
//    dst += yi_dst + wan_dst + currval;
//    return dst;
//}
//
//int main(void) {
//    string src = "五亿零一十万零八十";
////     string src = "五十六万七千九百零一";
//    // string src = "五千四百二十八万九千三百二十一";
//    // string src = "五千四百二十八万零二十一";
//    // string src = "五亿零一十万零八十";
//    // string src = "九千万零一十二";
//    // string src = "九千万";
////     string src = "二万零一百零七";
////    string src = "二十一";
////    string src = "十";
////    string src = "十七";
////    string src = "零";
//    
//
//    int res = cvtNum(src);
//    cout << "curr result: " << res << endl;
//
//    return 0;
//}
