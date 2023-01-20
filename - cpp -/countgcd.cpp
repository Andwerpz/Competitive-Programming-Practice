#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1750D

//first, figure out in what situations there are no valid b arrays. 
// - a[i] % a[i + 1] != 0
//if any i doesn't satisfy the above condition, then there are no valid b arrays. 
//this is true because gcd(a, b) % gcd(a, b, c) == 0. 

//now we need to calculate how many possible b arrays there are. 

ll ceilDiv(ll a, ll b){
    return (a / b) + (a % b != 0? 1 : 0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    const int N = (int) sqrt(1e9) + 1;
    vector<int> lp(N+1);
    vector<int> pr;
    for (int i=2; i <= N; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; i * pr[j] <= N; ++j) {
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i]) {
                break;
            }
        }
    }
    
    ll mod = 998244353;
    int t;
    cin >> t;
    while(t-- > 0){
        int n = 0;
        ll m = 0;
        cin >> n >> m;
        vector<ll> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        ll ans = 1;
        ll prev = a[0];
        for(int i = 1; i < n; i++){
            ll next = a[i];
            if(prev % next != 0){
                ans = 0;
                break;
            }
            ll div = prev / next;
            ll mul = m / next;  //b[i] has to be multiple of a[i]. 
            vector<ll> f(1, 1);
            for(int j : pr){
                if(div < j){
                    //cout << "BR : " << div << " " << j << "\n";
                    break;
                }
                if(div % j == 0){
                    //cout << "F : " << j << "\n";
                    int fSize = f.size();
                    for(int l = 0; l < fSize; l++){
                        f.push_back(-f[l] * j);
                    }
                    while(div % j == 0){
                        div /= j;
                    }
                }
            }
            if(div != 1){
                int fSize = f.size();
                for(int l = 0; l < fSize; l++){
                    f.push_back(-f[l] * div);
                }
            }
            ll fmul = 0;
            for(int j : f){
                fmul += mul / j;
            }
            //cout << "mul : " << fmul << "\n";
            //cout << m / next << "\n";
            ans *= fmul;
            ans %= mod;
            prev = next;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
