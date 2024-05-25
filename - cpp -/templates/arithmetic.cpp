#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

ll ceil_div(ll a, ll b){
    return (a + b - 1) / b;
}

vector<ll> find_ceil_brk(ll a) {
    vector<ll> ans(0);
    for(int i = 1; i * i <= a; i++){
        ans.push_back(i);
        ans.push_back(ceil_div(a, i));
    }
    return ans;
}