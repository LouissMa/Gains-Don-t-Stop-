/*
Problem: Problem Title
Contest: Contest Name
URL: URL
Memory Limit: 1024 MB
Time Limit: 2000 ms

Description:
Paste problem statement here
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> pii;

void solve() 
{
    vector<int> a(3);
    for(int i=0;i<3;i++) cin>>a[i];
    vector<vector<int>> vec;
    for(int j=0;j<2;j++)
    {
        vector<int> v;
        for(int i=0;i<3;i++)
        {
            int x;
            cin>>x;
            v.push_back(x);
        }
        sort(v.begin(), v.end());
        do{
            vec.push_back(v);
        }while(next_permutation(v.begin(), v.end()));
    }
    for(int i=0;i<vec.size();i++)
    {
        for(int j=0;j<vec.size();j++)
        {
            vector<int> b = vec[i];
            vector<int> c = vec[j];
            sort(a.begin(), a.end());
            do{
                if(b[0] == a[0] && c[1] == a[1] && b[1] + c[0] == a[2] && b[2] + c[2] == 180)
                {
                    cout<<"YES"<<endl;
                    return;
                }
            }while(next_permutation(a.begin(), a.end()));
        }
    }
    cout<<"NO"<<endl;
}

signed main() 
{
    SPEED;
    int t = 1;
    cin >> t;
    while(t--) 
    {
        solve();
    }
    return 0;
}