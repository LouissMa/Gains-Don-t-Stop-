#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;
const int N = 2e5+10;

int n,q,k;
int diff[N];      // 差分数组
int cnt[N];       // 覆盖次数数组

signed main()
{
    SPEED;
    cin>>n>>k>>q;
    
    // 初始化数组
    for(int i=0; i<N; i++) {
        diff[i] = 0;
        cnt[i] = 0;  // 关键：初始化cnt数组
    }
    
    // 构建差分数组
    for(int i=1; i<=n; i++)
    {
        int l, r;
        cin>>l>>r;
        diff[l]++;
        diff[r+1]--;
    }
    
    // 通过差分数组计算每个位置的覆盖次数
    for(int i=1; i<N; i++)  // 这里用i<N是正确的
    {
        cnt[i] = cnt[i-1] + diff[i];
    }
    
    // 计算前缀和，s[i]表示[1,i]中被至少k个区间覆盖的位置数
    int s[N];
    s[0] = 0;
    for(int i=1; i<N; i++)
    {
        s[i] = s[i-1];
        if(cnt[i] >= k)
        {
            s[i]++;
        }
    }
    
    while(q--)
    {
        int a,b;
        cin>>a>>b;
        cout<<s[b]-s[a-1]<<endl;
    }
    return 0;
}