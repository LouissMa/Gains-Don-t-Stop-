#include<bits/stdc++.h>
using namespace std;

int main(){
  int n, m;
  cin >> n >> m;
  vector<int> c(m);
  for(int i=0; i<m; i++) cin >> c[i];
  int ans=0;
  for(int i=0; i<n; i++){
    map<int,int> d;
    int k;
    cin >> k;
    for(int j=0; j<k; j++){
      int p;
      cin >> p;
      d[p-1]++;
    }
    for(auto[k, v]: d){
      if(v <= c[k]){
        ans += v;
      }
    }
  }
  cout << ans << endl;
}
