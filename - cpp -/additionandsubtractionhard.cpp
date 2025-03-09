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

//AtCoder - ARC66E

//First, we can place a lower bound on the answer. Our final answer should be better than if we don't
//place in any parentheses at all. So the only elements that we are 'missing' are the ones that
//have negative signs in front of them. 

//How can we 'save' some initially negative element? Notice that if an element is enclosed with 2 
//negative signs, it becomes positive. So if we 'sacrifice' the positive elements following the first
//negative element, then we can 'save' the remaining negative elements. 

//One consideration is that maybe the sacrifice is not worth it. If sacrificing the positive 
//elements behind the first negative element is not worth it, then we can instead sacrifice the 
//positive elements behind the second negative elements. Note however that we shouldn't sacrifice
//more than 1 segment of positive elements, as if you already sacrificed an earlier segment, then
//any later segment shouldn't be sacrificed. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vl a(n), nind(0), pfx(n + 1, 0);
    ll ans = 0;
    for(int i = 0; i < n; i++){
        bool neg = false;
        if(i != 0) {
            string op;
            cin >> op;
            neg = op == "-";
        }
        cin >> a[i];
        if(neg) nind.push_back(i);
        ans += a[i] * (neg? -1 : 1);
    }
    for(int i = 1; i <= n; i++){
        pfx[i] = pfx[i - 1] + a[i - 1];
    }
    ll nsum = 0;
    for(int i = 1; i < nind.size(); i++){
        int l = nind[i - 1], r = nind[i];
        ll cans = pfx[n] - 2 * (pfx[r] - pfx[l]);
        cans -= nsum * 2;
        ans = max(ans, cans);
        nsum += a[l];
    }
    cout << ans << "\n";
    
    return 0;
}