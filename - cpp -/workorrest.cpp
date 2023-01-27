#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ACPC Weekly Problem Set #1 (Spring 2023) E

//if you make it so that the first day of the week is a holiday, then you'll get rid of any issues regarding 
//the cyclic nature of the week. You can just assume that index n + 1 is a holiday. 

//from there, it's just dp. 

//dp[i] : maximum productivity of the days from 1 - i given that i is a holiday. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<ll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<ll> pfx(n + 1, 0);
    for(int i = 0; i < n; i++){
        pfx[i + 1] = pfx[i] + a[i];
    }
    vector<ll> dp(n, 0);
    ll ans = 0;
    for(int i = 0; i < n; i++){
        for(int j = i - 1; j >= 0; j--) {
            ll next = dp[j];
            int amt = i - j - 1;
            next += pfx[amt / 2] * 2ll;
            if(amt % 2 == 1){
                next += a[amt / 2];
            }
            dp[i] = max(dp[i], next);
        }
        int amt = n - 1 - i;
        ll nextAns = pfx[amt / 2] * 2ll + dp[i];
        if(amt % 2 == 1){
            nextAns += a[amt / 2];
        }
        ans = max(ans, nextAns);
        //cout << dp[i] << endl;
    }
    cout << ans << "\n";
    
    return 0;
}
