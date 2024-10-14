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

//KTH Challenge 2021 - A

//implementation. 

//note that there are really only 12 unique transpositions. 

ll tti(string& t) {
    ll ans;
    bool sharp = false;
    if(t[1] == '#'){
        sharp = true;
        ans = stoll(t.substr(2)) * 12ll;
    }
    else {
        ans = stoll(t.substr(1)) * 12ll;
    }
    switch(t[0]) {
        case 'C':
            return ans + 0 + sharp;
            break;

        case 'D':
            return ans + 2 + sharp;
            break;

        case 'E':
            return ans + 4;
            break;
        
        case 'F':
            return ans + 5 + sharp;
            break;

        case 'G':
            return ans + 7 + sharp;
            break;

        case 'A':
            return ans + 9 + sharp;
            break;

        case 'B':
            return ans + 11;
            break;
    }
    return -1; //bruh
}

bool is_sharp(ll t) {
    t %= 12ll;
    return t == 1 || t == 3 || t == 6 || t == 8 || t == 10;
}

ll check_shift(vl& a, ll shift) {
    ll ans = 0;
    for(int i = 0; i < a.size(); i++){
        ans += is_sharp(a[i] + shift);
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    ll mint, maxt;
    {
        string u, v;
        cin >> u >> v;
        mint = tti(u);
        maxt = tti(v);
    }
    vl a(n);
    ll amin = 1e18, amax = -1e18;
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        a[i] = tti(s);
        amin = min(amin, a[i]);
        amax = max(amax, a[i]);
    }
    for(int i = 0; i < n; i++){
        a[i] += mint - amin;
    }
    amax += mint - amin;
    amin = mint;
    ll min_acc = 1e18;
    for(int i = 0; i < 12; i++){
        if(amax + i > maxt) {
            continue;
        }
        min_acc = min(min_acc, check_shift(a, i));
    }
    ll cnt = 0;
    for(int i = 0; i < 12; i++){
        if(amax + i > maxt) {
            continue;
        }
        if(check_shift(a, i) != min_acc) {
            continue;
        }
        ll diff = (maxt - amax + 1) - i;
        // cout << "AMT : " << i << " " << (diff + 11) / 12 << "\n";
        cnt += (diff + 11) / 12;
    }
    cout << min_acc << " " << cnt << "\n";
    
    return 0;
}