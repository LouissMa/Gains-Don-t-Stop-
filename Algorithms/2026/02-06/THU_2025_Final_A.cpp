#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    cin >> s;

    // 如果字符串为空，直接结束
    if (s.empty()) {
        return 0;
    }

    int count = 1; // 初始化计数器为1，因为每个字符至少出现一次
    int len = s.length();

    // 从第二个字符开始遍历
    for (int i = 1; i < len; i++) {
        // 如果当前字符和前一个字符相同，计数器加1
        if (s[i] == s[i - 1]) {
            count++;
        } else {
            cout << s[i - 1];
            // 2. 如果计数大于1，输出次数
            if (count > 1) {
                cout << count;
            }
            count = 1;
        }
    }
    cout << s[len - 1];
    if (count > 1) {
        cout << count;
    }

    cout << endl;

    return 0;
}