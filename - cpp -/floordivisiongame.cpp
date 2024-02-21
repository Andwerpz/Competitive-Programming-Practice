#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//CodeChef - FDIVGAME

//compute grundy number for each scenario to turn it into a nim game. The hard part is figuring out
//how to quickly compute grundy number as values can be up to 10^18. 

//after brute forcing the first 10^6 grundy numbers, I found a pattern. I suppose the pattern itself isn't
//too interesting, as it's rather arbitrary, but the grundy number idea is what's important. 

int calc_grundy_fast(ll a) {
    if(a == 0){
        return 0;
    }
    else if(a == 1){
        return 1;
    }
    int ans = 1;
    ll x = 1;
    ll gap = 2;
    while(x < a) {
        x += gap;
        if(ans == 1){
            gap *= 1;
        }
        else if(ans == 2){
            gap *= 3;
        }
        else if(ans == 3){
            gap *= 2;
        }
        else {
            gap *= 2;
        }
        ans = (ans + 1) % 4;
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        ll a;
        int g_sum = 0;
        for(int i = 0; i < n; i++){
            cin >> a;
            g_sum ^= calc_grundy_fast(a);
        }
        cout << (g_sum? "Henry" : "Derek") << "\n";
    }
    
    return 0;
}