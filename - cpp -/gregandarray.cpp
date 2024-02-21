#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 295A

//simple implementation; 2 prefix sum range modification. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, k;
    cin >> n >> m >> k;
    vector<ll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<pair<ll, pair<int, int>>> ops(0);
    for(int i = 0; i < m; i++){
        int l, r, d;
        cin >> l >> r >> d;
        l --;
        ops.push_back({d, {l, r}});
    }
    vector<ll> f(m + 1, 0);
    for(int i = 0; i < k; i++){
        int l, r;
        cin >> l >> r;
        l --;
        f[l] ++;
        f[r] --;
    }
    for(int i = 1; i < m; i++){
        f[i] += f[i - 1];
    }
    vector<ll> add(n + 1, 0);
    for(int i = 0; i < m; i++){
        ll d = ops[i].first;
        int l = ops[i].second.first;
        int r = ops[i].second.second;
        add[l] += d * f[i];
        add[r] -= d * f[i];
    }
    for(int i = 1; i < n; i++){
        add[i] += add[i - 1];
    }
    for(int i = 0; i < n; i++){
        a[i] += add[i];
        cout << a[i] << " \n"[i == n - 1];
    }
    
    return 0;
}
