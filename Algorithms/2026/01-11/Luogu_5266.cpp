#include <bits/stdc++.h>
using namespace std;
#define int long long
#define SPEED ios::sync_with_stdio(false);cin.tie(0); cout.tie(0);
typedef pair<int, int> PII;

signed main()
{
    SPEED;
    int q;
    cin>>q;
    map<string,int> v;
    while(q--)
    {
        int op;
        cin>>op;
        if(op == 1)
        {
            string s;
            cin>>s;
            int sco;
            cin>>sco;
            v[s] = sco;
            cout<<"OK\n";
        }
        else if(op == 2)
        {
            string s;
            cin>>s;
            if(v.count(s)) cout<<v[s]<<"\n";
            else cout<<"Not found\n";
        }
        else if(op == 3)
        {
            string s;
            cin>>s;
            if(v.count(s))
            {
                v.erase(s);
                cout<<"Deleted successfully\n";
            }
            else cout<<"Not found\n";
        }
        else 
        {
            cout<<v.size()<<"\n";
        }
    }
    return 0;
}