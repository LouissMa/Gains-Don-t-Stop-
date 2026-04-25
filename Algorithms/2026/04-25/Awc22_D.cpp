//simultaneouscontroloflightbulbpanels.cpp
#include <bits/stdc++.h>

using namespace std;

#define all(x) (x).begin(), (x).end()

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin>>n>>k;

    vector<int> a(n);
    for(int i=0;i<n;i++) cin>>a[i];

    vector<bool> x(n, false);
    queue<int> q;
    int cnt=0;
    for(int i=0;i<n-k+1;i++){
        if(!q.empty() && q.front()+k<=i) q.pop();
        if((q.size()%2)^a[i]==1){
            q.push(i);
            cnt++;
            x[i]=true;
        }
    }

    while(!q.empty()) q.pop();

    vector<int> c(n, 0);
    for(int i=0;i<n;i++){
        if(x[i]) q.push(i);
        if(!q.empty() && q.front()+k<=i) q.pop();
        if((q.size()%2)==1) c[i]=1;
        else c[i]=0;
        if(c[i]!=a[i]){
            cnt=-1;
            break;
        }
    }

    cout<<cnt<<'\n';
    return 0;
}