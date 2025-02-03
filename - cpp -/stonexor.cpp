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

//AtCoder - ABC390D

//12th bell number is around 4 million, so a brute force solution is viable. 

//do recursively so you don't have to move around as much memory, and stuff everything into a 
//vector and sort for better memory locality. 

int cnt = 0;
void solve(int aptr, int pptr, vl& a, vl& p, vector<ll>& s, ll xsum) {
    if(aptr == a.size()) {
        cnt ++;
        s.push_back(xsum);
        return;
    }
    //add to end
    p[pptr] = a[aptr];
    solve(aptr + 1, pptr + 1, a, p, s, xsum ^ a[aptr]);
    p[pptr] = 0;
    //add to something existing
    for(int i = 0; i < pptr; i++){
        xsum ^= p[i];
        p[i] += a[aptr];
        xsum ^= p[i];
        solve(aptr + 1, pptr, a, p, s, xsum);
        xsum ^= p[i];
        p[i] -= a[aptr];
        xsum ^= p[i];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vl p(n, 0), a(n, 0);
    for(int i = 0; i < n; i++) cin >> a[i];
    vl s(0);
    solve(0, 0, a, p, s, 0);
    int ans = 1;
    sort(s.begin(), s.end());
    for(int i = 1; i < s.size(); i++) if(s[i - 1] != s[i]) ans ++;
    cout << ans << "\n";
    // cout << "CNT : " << cnt << "\n";
    
    return 0;
}