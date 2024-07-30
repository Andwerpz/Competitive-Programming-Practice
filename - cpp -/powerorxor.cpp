#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

//Codeforces - 1673E

//I really don't want to explain this one. go read editorial lol 

//true if odd, false if even. 
bool nck_parity(int n, int k) {   
    return (k & (n - k)) == 0;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    vi b(n);
    for(int i = 0; i < n; i++){
        cin >> b[i];
    }
    //for each combination, figure out whether or not it's going to be in the final product
    vb ans((1 << 22), false);
    map<pii, bool> parmap;
    for(int i = 0; i < n; i++){
        //base = b[i];
        //current number is 2^(base * 2^multsum)
        //if multsum gets >= 20, then result is not in final product
        int multsum = 0;    
        for(int j = i + 1; j <= n && multsum < 20; j++){
            //first test current multsum
            pii key = {(n - 1) - (j - i - 1), (i != 0) + (j != n)};
            if(!parmap.count(key)) {
                bool parity = false;
                int totrem = (n - 1) - (j - i - 1) - (i != 0) - (j != n);
                for(int _k = k; _k <= n - 1; _k++){
                    int xorrem = _k - (i != 0) - (j != n);
                    if(xorrem > totrem || xorrem < 0) {
                        continue;
                    }
                    parity ^= nck_parity(totrem, xorrem);
                }
                parmap[key] = parity;
            }
            bool parity = parmap[key];
            ll ind = (ll) b[i] << (ll) multsum;
            if(ind >= ans.size()){
                break;
            }
            ans[ind] = ans[ind] ^ parity;
            //update multsum
            if(j != n){
                multsum += b[j];
            }
        }
    }
    int lo = 0;
    for(int i = 0; i < (1 << 20); i++){
        if(ans[i]){
            lo = i;
        }
    }
    for(int i = lo; i >= 0; i--){
        cout << ans[i];
    }
    cout << "\n";
    
    return 0;
}