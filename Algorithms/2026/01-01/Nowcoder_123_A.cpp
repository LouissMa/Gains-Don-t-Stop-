#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int n;
    cin>>n;
    vector<string> v(6);
    for(int i=0;i<6;i++)
    {
        if(i==2 || i == 5 ) v[i] = "koishiYun";
        else v[i] = "Kato_Shoko";
    }
    for(int i=0;i<n;i++)
    {
        int t;
        cin>>t;
        t--;
        cout<<v[t]<<endl;
    }
    return 0;
}