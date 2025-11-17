#include <iostream>
#include <vector>
using namespace std;

int main() {
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector<long long> arr(n);
        
        for(int i=0; i<n; i++) cin>>arr[i];

        long long maxi = 0, sum = 0;
        for (int i=0; i<n; i++){
            long long x = max(arr[i], arr[(i+1)%n]);
            sum += x;
            maxi = max(maxi, arr[i]);
        }
        cout<<sum - maxi<<endl;
    }
}
