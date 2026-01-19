#include<bits/stdc++.h>
using namespace std;

void solve(){
  int n;
  string s;
  cin>>n>>s;
  string t=s;
  sort(t.begin(),t.end());
  vector<int> ans;
  for (int i=0;i<n;i++) if (t[i]!=s[i]) ans.push_back(i+1);
  if (ans.size()==0) cout<<"Bob\n";
  else{
    cout<<"Alice\n";
    int k=ans.size();
    cout<<k<<endl;
    for (int i=0;i<k;i++) cout<<ans[i]<<" \n"[i==k-1];
  }
}

int main(){
  int t;
  cin>>t;
  while (t--) solve();
}
