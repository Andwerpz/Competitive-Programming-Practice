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

//sum over subsets dp. dpa[i] = sum over a[j] where j is a subset of i
//sum over supersets dp. dpb[i] = sum over a[j] where i is a subset of j

//go here for explanation
//https://codeforces.com/blog/entry/105247

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int BITS = 22;
    int n;
    cin >> n;
    vi a(n), dpa((1 << BITS), 0), dpb((1 << BITS), 0);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        dpa[a[i]] = a[i];
        dpb[a[i]] = a[i];
    }
    //subsets
    for(int i = 0; i < BITS; i++){
        for(int j = 0; j < (1 << BITS); j++){
            if(j & (1 << i)) {
                dpa[j] = max(dpa[j], dpa[j ^ (1 << i)]);   //replace this with whatever you want
                //dpa[j] += dpa[j ^ (1 << i)];  //sum for example
            }
        }
    }
    //supersets
    for(int i = 0; i < BITS; i++){
        for(int j = 0; j < (1 << BITS); j++){
            if((j & (1 << i)) == 0) { //only different line
                dpb[j] += dpb[j ^ (1 << i)];
            }
        }
    }
    
    return 0;
}