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

vector<int> primes;
void init_primes() 
{
    int maxx = 2e5;
    vector<bool> is_prime(maxx + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int p = 2; p * p <= maxx; p++) {
        if (is_prime[p]) {
            for (int i = p * p; i <= maxx; i += p) {
                is_prime[i] = false;
            }
        }
    }
    for (int p = 2; p <= maxx; p++) {
        if (is_prime[p]) {
            primes.push_back(p);
        }
    }
}
void solve() 
{
    int n;
    cin>>n;
    init_primes();
    for(int i=0;i<n;i++)
    {
        cout<<primes[i] * primes[i + 1]<<(i == n - 1 ? "" : " ");
    }
    cout<<endl;
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