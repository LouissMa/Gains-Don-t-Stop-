#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

std :: string s[7] = {"Red", "Orange", "Yellow", "Green", "Blue", "Indigo", "Violet"};
signed main()
{
    SPEED;
    vector<int> a(7);
    for(int i=0;i<7;i++)
    {
        cin>>a[i];
    }
    int pos = max_element(a.begin(), a.end()) - a.begin();
    cout<<s[pos]<<endl;
    return 0;
}