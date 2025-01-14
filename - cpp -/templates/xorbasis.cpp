#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;

//basis where basis[i] represents the basis vector with most significant on bit being ith bit. 
//basis[i] = 0 means there is no basis vector there yet

const int B = 20;
bool basisInsert(vl& b, ll x){
    for(int i = B - 1; i >= 0; i--){
        if((x & (1ll << i)) == 0) continue;
        if(!b[i]) {b[i] = x; return true;}
        x ^= b[i];
    }
    return false;
}

bool inBasis(vl& b, ll x){
    for(int i = B - 1; i >= 0; i--)
        if(x & (1ll << i)) x ^= b[i];
    return x == 0;
}

ll basisMax(vl& b) {
    ll ans = 0;
    for(int i = B - 1; i >= 0; i--) if(b[i] && !(ans & (1ll << i))) ans ^= b[i];
    return ans;
}