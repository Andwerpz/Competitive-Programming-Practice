#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1688D

//we can consider two cases, k >= n, and k < n. For each, the key is to consider maximizing
//the original mushrooms and the extra mushrooms seperately. 

//if k < n, then the optimal way of collecting original mushrooms and extra mushrooms
//are the same; collect the subarray with the highest sum of original mushrooms. 

//else, k >= n. Once again, we can use the same stragegy for original and extra mushrooms. Since k >= n, 
//it is guranteed that we can collect all the original mushrooms. The key to maximize the extra mushrooms
//is to minimize the amount of extra mushrooms remaining after you finish collecting. 

//thus, at the end of your collection, you need to do a full sweep of the line; e.g. go from index 0 to n - 1. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0) {
        int n;
        ll k;
        cin >> n >> k;
        vector<ll> pfx(n);
        for(int i = 0; i < n; i++){
            cin >> pfx[i];
            if(i != 0){
                pfx[i] += pfx[i - 1];
            }
        }
        if(k >= n){
            cout << (pfx[n - 1] + (k - n) * n + ((ll) (n - 1) * (ll) n) / 2ll) << "\n";
        }
        else{
            ll max = 0;
            for(int i = 0; i + k - 1 < n; i++){
                max = std::max(max, pfx[i + k - 1] - (i == 0? 0 : pfx[i - 1]));
            }
            cout << (max + (k * (k - 1)) / 2ll) << "\n";
        }
    }
    
    return 0;
}
