#include <iostream>
using namespace std;
int n, m;
int a[25];
long long ans;

bool prime(int x){      //判断素数不必多说
    if(x == 1 || x != 2 && x % 2 == 0) return 0;
    for(int i = 3; i * i <= x; i++) if(x % i == 0) return 0;
    return 1;
}

void DFS(int k, int s, int x){      //k表示当前已选的数的个数，s表示这几个数的和，x表示上一个选择的数的下一位
    if(k == m){
        if(prime(s)) ans++;
        return;
    }
    for(int i = x; i < n; i++) DFS(k + 1, s + a[i], i + 1);      //从x开始选，保证是升序
}

int main(){
    cin >> n >> m;
    for(int i = 0; i < n; i++) cin >> a[i];
    DFS(0, 0, 0);
    cout << ans << "\n";
    return 0;
}
