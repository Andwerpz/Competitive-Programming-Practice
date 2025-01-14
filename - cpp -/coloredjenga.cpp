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

//Codeforces - 424E

//got too frustrated with problem D:

//essentially just need to come up with better hash function for state, and figure out where my bug in the 
//dp is. 

//should spit out a unique identifier for every state
//some optimizations to reduce the number of states. Ideally we want all states with same EV to hash to same id
// - order of layers doesn't really matter, except for the top layer
// - only really need to differentiate between middle and side pieces
typedef array<ll, 3> ident_t;
map<ident_t, ld> dp;
ident_t encode(vector<string> a) {
    int top = a.size();
    for(int i = 0; i < a.size(); i++){
        if(a[i][0] < a[i][2]) swap(a[i][0], a[i][2]);   //disregard ordering of side pieces
        if(a[i][0] == '.' && a[i][1] == '.' && a[i][2] == '.') {
            top = i - 1;
            break;
        }
    }
    sort(a.begin(), a.begin() + top);   //disregard ordering of layers that are not top
    ll r = 0, g = 0, b = 0;
    for(int i = 0; i < a.size(); i++){
        for(int j = 0; j < 3; j++){
            if(a[i][j] == 'R') r ^= (1 << (i * 3 + j));
            if(a[i][j] == 'G') g ^= (1 << (i * 3 + j));
            if(a[i][j] == 'B') b ^= (1 << (i * 3 + j));
        }
    }
    return {r, g, b};
}

//all combinations of removing a block, and where to place it on top
ld solve(vector<string>& a) {
    ident_t id = encode(a);
    // cout << "SOLVE : " << id[0] << " " << id[1] << " " << id[2] << "\n";
    if(dp.count(id)) {
        return dp[id];
    }
    int top = a.size();
    int place = a.size();
    for(int i = a.size() - 1; i >= 0; i--){
        if(a[i][0] != '.' || a[i][1] != '.' || a[i][2] != '.') {
            top = i, place = i;
            if(a[i][0] != '.' && a[i][1] != '.' && a[i][2] != '.') {
                place = i + 1;
            }
            break;
        }
    }
    ld red_ev = 1e18, green_ev = 1e18, blue_ev = 1e18;
    for(int i = 0; i < top; i++){
        if(a[i][1] == '.') continue;
        for(int j = 0; j < 3; j++){
            if(a[i][j] == '.') continue;
            if(j == 1 && (a[i][0] == '.' || a[i][2] == '.')) continue;
            for(int k = 0; k < 3; k++){
                if(a[place][k] != '.') continue;
                char c = a[i][j];
                swap(a[i][j], a[place][k]);
                if(c == 'R') red_ev = min(red_ev, solve(a));
                else if(c == 'G') green_ev = min(green_ev, solve(a));
                else if(c == 'B') blue_ev = min(blue_ev, solve(a));
                swap(a[i][j], a[place][k]);
            }
        }
    }
    ld continue_prob = 5.0 / 6.0;
    if(red_ev == 1e18) continue_prob -= 1.0 / 6.0;
    if(green_ev == 1e18) continue_prob -= 2.0 / 6.0;
    if(blue_ev == 1e18) continue_prob -= 2.0 / 6.0;
    ld ans = 0;
    if(continue_prob > 0.0001) {
        ans = 1.0;
        if(red_ev != 1e18) ans += red_ev * (1.0 / 6.0);
        if(green_ev != 1e18) ans += green_ev * (2.0 / 6.0);
        if(blue_ev != 1e18) ans += blue_ev * (2.0 / 6.0);
        ans *= 1.0 / continue_prob;
        // cout << "EV : " << red_ev << " " << blue_ev << " " << green_ev << "\n";
    }
    // cout << "STATE\n";
    // for(int i = 0; i < a.size(); i++){
    //     cout << a[i] << "\n";
    // }
    // cout << "TOP : " << top << " " << place << "\n";
    // cout << "CPROB : " << continue_prob << " " << blue_ev << " " << green_ev << "\n";
    if((dp.size() + 1) % 10000 == 0) cout << dp.size()<< endl;
    dp[id] = ans;
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<string> a(n * 3 + 1, string(3, '.'));
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    reverse(a.begin(), a.begin() + n);
    ld ans = solve(a);
    cout << fixed << setprecision(10) << ans << "\n";
    cout << "STATE CNT : " << dp.size() << "\n";
    
    return 0;
}