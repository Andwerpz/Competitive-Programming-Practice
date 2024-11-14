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

//CTU Open 2021 - I

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    string s; cin >> s;

    int hi = 0;
    int cnt = 0;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '0') {
            cnt++;
        } else {
            cnt = 0;
        }
        hi = max(hi,cnt);
    }

    cout << (hi + 1) / 2 << '\n';
    
    return 0;
}