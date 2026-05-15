#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <cstdlib>

using namespace std;

// 全局预测分析表 M
map<string, map<string, string>> M;

// 初始化预测分析表 (基于实验3结果)
void initTable() {
    M["S"]["a"] = "S->a";
    M["S"]["^"] = "S->^";
    M["S"]["("] = "S->(T)";
    
    M["T"]["a"] = "T->ST'";
    M["T"]["^"] = "T->ST'";
    M["T"]["("] = "T->ST'";
    
    M["T'"][")"] = "T'->e";   // 用 e 代表 epsilon 空字
    M["T'"][","] = "T'->,ST'";
}

// 辅助函数：将产生式右部拆分成符号数组并逆序压栈
// 处理形如 "ST'" 或 ",ST'" 包含撇号的情况
void pushReverse(vector<string>& stk, string rhs) {
    if (rhs == "e") return; // 空字不入栈
    
    vector<string> tokens;
    for (size_t i = 0; i < rhs.length(); ++i) {
        // 如果当前字符是 T 且下一个字符是 '，则组合成 T'
        if (rhs[i] == 'T' && i + 1 < rhs.length() && rhs[i+1] == '\'') {
            tokens.push_back("T'");
            i++; // 跳过撇号
        } else {
            tokens.push_back(string(1, rhs[i]));
        }
    }
    
    // 逆序压栈
    for (int i = tokens.size() - 1; i >= 0; --i) {
        stk.push_back(tokens[i]);
    }
}

int main() {
    // 解决控制台中文乱码
    system("chcp 65001");
    
    initTable();
    
    // 初始化分析栈，压入结束符 $ 和文法开始符 S
    vector<string> stk;
    stk.push_back("$");
    stk.push_back("S");
    
    // 初始化输入串序列
    vector<string> input = {"(", "a", ",", "a", ")", "$"};
    int ip = 0; // 输入串指针
    
    // 打印表头
    cout << "======================================================" << endl;
    cout << left << setw(15) << "分析栈" 
         << right << setw(15) << "输入串" 
         << "        " << left << "所用规则" << endl;
    cout << "------------------------------------------------------" << endl;

    // 分析主循环
    while (true) {
        // 如果栈空了还没结束，说明出错
        if (stk.empty()) break;
        
        string X = stk.back(); // 取栈顶符号
        string a = input[ip];  // 取当前输入符号
        
        // 拼接当前栈的字符串展示 (自底向上打印)
        string stack_str = "";
        for (const string& s : stk) stack_str += s;
        
        // 拼接当前剩余输入串的展示
        string input_str = "";
        for (size_t i = ip; i < input.size(); ++i) input_str += input[i];
        
        // 1. 成功接受状态
        if (X == "$" && a == "$") {
            cout << left << setw(15) << stack_str 
                 << right << setw(15) << input_str 
                 << "        " << left << "成功" << endl;
            break;
        }
        
        // 2. 匹配到终结符 (消去)
        if (X == a) {
            cout << left << setw(15) << stack_str 
                 << right << setw(15) << input_str 
                 << "        " << "" << endl;
            stk.pop_back(); // 栈顶出栈
            ip++;           // 输入指针后移
        } 
        // 3. 查表展开非终结符
        else if (M.count(X) && M[X].count(a)) {
            string rule = M[X][a];
            cout << left << setw(15) << stack_str 
                 << right << setw(15) << input_str 
                 << "        " << left << rule << endl;
                 
            stk.pop_back(); // 非终结符出栈
            
            // 提取产生式右部 (去掉 "X->")
            string rhs = rule.substr(rule.find("->") + 2);
            // 逆序压栈
            pushReverse(stk, rhs);
        } 
        // 4. 查不到表，出错
        else {
            cout << left << setw(15) << stack_str 
                 << right << setw(15) << input_str 
                 << "        " << "出错: 查不到产生式" << endl;
            break;
        }
    }
    cout << "======================================================" << endl;

    return 0;
}