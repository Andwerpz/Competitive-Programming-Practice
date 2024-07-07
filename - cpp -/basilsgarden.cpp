#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1987C

//denote the amount of time for some element h[i] to go to zero as t[i]. 
//first, observe that t[n - 1] = h[n - 1], since the last element always decreases by 1 every time unit. 

//then, consider t[n - 2]. If h[n - 2] > h[n - 1], then t[n - 2] = h[n - 2]. But if h[n - 2] <= h[n - 1], then
//the second to last element will become 'bottlenecked' by the last element, and t[n - 2] = t[n - 1] + 1. 

//this is actually true for all i. In the end, we return t[0]. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<ll> h(n);
        for(int i = 0; i < n; i++){
            cin >> h[i];
        }
        vector<ll> t(n);
        t[n - 1] = h[n - 1];
        for(int i = n - 2; i >= 0; i--){
            t[i] = max(t[i + 1] + 1, h[i]);
        }
        cout << t[0] << "\n";
    }
    
    return 0;
}