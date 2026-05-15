#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iomanip>

using namespace std;

// 定义产生式结构体
struct Production {
    string left;  // 左部非终结符
    string right; // 右部符号串
};

int main() {
    system("chcp 65001");
    // 1. 定义终结符和非终结符
    vector<string> terminals = {"a", "^", "(", ")", ",", "$"};
    vector<string> non_terminals = {"S", "T", "T'"};

    // 2. 定义文法产生式 (例 4.10)
    // 注意: ^ 代表图中的 \Lambda, ~ 代表 \varepsilon
    vector<Production> prods = {
        {"S", "a"},
        {"S", "^"},
        {"S", "(T)"},
        {"T", "ST'"},
        {"T'", ",ST'"},
        {"T'", "~"}  // ~ 表示空字 epsilon
    };

    // 3. 已知 FIRST 集 (直接取自教材图表)
    map<string, set<string>> first_sets;
    first_sets["a"] = {"a"};
    first_sets["^"] = {"^"};
    first_sets["(T)"] = {"("};
    first_sets["ST'"] = {"a", "^", "("}; // FIRST(T) 就是 FIRST(S)
    first_sets[",ST'"] = {","};
    first_sets["~"] = {"~"};

    // 4. 已知 FOLLOW 集 (直接取自教材图表)
    map<string, set<string>> follow_sets;
    follow_sets["S"] = {"$", ",", ")"};
    follow_sets["T"] = {")"};
    follow_sets["T'"] = {")"};

    // 5. 定义预测分析表 M: M[非终结符][终结符] = 产生式字符串
    map<string, map<string, string>> M;

    // 6. 核心算法：构造预测分析表
    for (const auto& p : prods) {
        string A = p.left;
        string alpha = p.right;

        // 获取该产生式右部的 FIRST 集
        set<string> first_alpha = first_sets[alpha];

        bool has_epsilon = false;

        // 规则 (2): 对于 FIRST(alpha) 中的每一个终结符 a
        for (const string& a : first_alpha) {
            if (a != "~") {
                // 将 A -> alpha 填入 M[A, a]
                M[A][a] = A + "->" + (alpha == "~" ? "e" : alpha); 
            } else {
                has_epsilon = true; // 记录包含空字
            }
        }

        // 规则 (3): 如果 FIRST(alpha) 包含空字 epsilon (~)
        if (has_epsilon) {
            // 对于 FOLLOW(A) 中的每一个终结符 b
            for (const string& b : follow_sets[A]) {
                // 将 A -> epsilon 填入 M[A, b]
                M[A][b] = A + "->e"; // 用 e 打印代表 epsilon
            }
        }
    }

    // 7. 打印输出预测分析表 (格式化输出)
    cout << "================== 预测分析表 M ==================" << endl;
    
    // 打印表头
    cout << left << setw(10) << "";
    for (const string& t : terminals) {
        cout << setw(12) << t;
    }
    cout << endl;
    cout << "------------------------------------------------------------------------" << endl;

    // 打印表内容
    for (const string& nt : non_terminals) {
        cout << left << setw(10) << nt;
        for (const string& t : terminals) {
            if (M[nt].count(t) > 0) {
                cout << setw(12) << M[nt][t];
            } else {
                cout << setw(12) << ""; // 空白表示 error
            }
        }
        cout << endl;
    }
    cout << "==================================================" << endl;

    return 0;
}