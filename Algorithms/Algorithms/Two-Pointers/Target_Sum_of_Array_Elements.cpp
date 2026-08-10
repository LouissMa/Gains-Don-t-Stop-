#include <iostream>
using namespace std;
const int N = 100010;    // 数组最大长度，题目说不超过1e5
int n, m, x;
int a[N], b[N];

int main()
{
    scanf("%d%d%d", &n, &m, &x);
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);   // 读入升序数组A
    for(int i = 0; i < m; i++) scanf("%d", &b[i]);   // 读入升序数组B
    
    // i从A的头部开始，j从B的尾部开始
    for(int i = 0, j = m - 1; i < n; i++)
    {
        // 步骤1：如果和太大，不断左移j，直到和<=x
        while(j >= 0 && a[i] + b[j] > x) 
            j--;
        
        // 步骤2：此时要么和<=x，要么j已经越界
        // 检查和是否恰好等于x
        if(j >= 0 && a[i] + b[j] == x) 
            cout << i << ' ' << j << endl;
        
        // 步骤3：如果和<x，说明当前B[j]太小
        // 但下一轮i会增大（A[i]变大），所以j不需要回退，直接i++
    }
    return 0;
}