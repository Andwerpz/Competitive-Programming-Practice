#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef array<int, 2> pii;
typedef array<ll, 2> pll;
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

//Codeforces - 1279C

//when removing a present, we can rearrange all presents above such that when we need to take a present
//above, it'll be on the top of the stack. 

//so, the only case when we need to take a present and it's not on the top will be when we're in 'unvisited'
//territory. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        vi a(n), b(m), p(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        for(int i = 0; i < m; i++) cin >> b[i];
        for(int i = 0; i < n; i++) a[i] --, p[a[i]] = i;
        for(int i = 0; i < m; i++) b[i] --;
        vb t(n, true);
        for(int i = 0; i < m; i++) t[p[b[i]]] = false;
        vl pfx(n + 1, 0);
        for(int i = 1; i <= n; i++) pfx[i] = pfx[i - 1] + t[i - 1];
        vb v(n, false);
        ll ans = 0, usent = 0;
        for(int i = 0; i < m; i++){
            if(v[p[b[i]]]) {ans ++, usent --; continue;}
            ans += usent * 2;
            for(int j = p[b[i]]; j >= 0; j--){
                if(v[j]) break;
                v[j] = true;
                if(!t[j]) ans += 2, usent ++;
            }
            usent --;
            ans --;
            ans += pfx[p[b[i]] + 1] * 2;
        }
        cout << ans << "\n";
    }
    
    return 0;
}