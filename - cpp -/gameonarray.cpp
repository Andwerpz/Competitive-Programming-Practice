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

//Codeforces - 2147D

//write a brute force tester + make a guess lmao

//ty josh for observations
//observe that if all values are even, then alice and bob will get the exact same score. 
//then, if there exist some odd values, alice and bob will first try to greedily pick the odd values with
//highest frequency before then doing the even strat. 

pair<pll, vl> solve(map<ll, ll>& m, bool alice, ll csum) {
    // cout << "SOLVE : " << csum << endl;
    if(csum == 0) return {{0, 0}, {}};
    if(alice) {
        bool found = false;
        pair<pll, vl> ans = {{0, csum}, {}};
        for(auto i = m.begin(); i != m.end(); i++) {
            ll x = i->first, amt = i->second;
            if(x == 0 || amt == 0) continue;
            m[x] = 0;
            m[x - 1] += amt;
            pair<pll, vl> nans = solve(m, !alice, csum - amt);
            nans.first.first += amt;
            nans.second.push_back(x);
            if(nans.first.first > ans.first.first || !found) ans = nans, found = true;
            m[x - 1] -= amt;
            m[x] = amt;
        }
        return ans;
    }
    else {
        bool found = false;
        pair<pll, vl> ans = {{0, csum}, {}};
        for(auto i = m.begin(); i != m.end(); i++) {
            ll x = i->first, amt = i->second;
            if(x == 0 || amt == 0) continue;
            m[x] = 0;
            m[x - 1] += amt;
            pair<pll, vl> nans = solve(m, !alice, csum - amt);
            nans.first.second += amt;
            nans.second.push_back(x);
            if(nans.first.second > ans.first.second || !found) ans = nans, found = true;
            m[x - 1] -= amt;
            m[x] = amt;
        }
        return ans;
    }
    assert(false);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        map<ll, ll> m;
        ll sum = 0;
        for(int i = 0; i < n; i++) {
            ll a;
            cin >> a;
            m[a] ++;
            sum += a;
        }
        ll alice = 0, bob = 0;
        map<ll, ll> f;
        for(auto i = m.begin(); i != m.end(); i++) {
            ll x = i->first, amt = i->second;
            f[amt] += x;
        }
        bool alice_turn = true;
        for(auto i = f.rbegin(); i != f.rend(); i++) {
            ll amt = i->first, amtamt = i->second;
            if(alice_turn) {
                alice += amt * ((amtamt + 1) / 2);
                bob += amt * (amtamt / 2);
            }
            else {
                bob += amt * ((amtamt + 1) / 2);
                alice += amt * (amtamt / 2);
            }
            if(amtamt % 2) alice_turn = !alice_turn;
        }
        cout << alice << " " << bob << "\n";

        // pair<pll, vl> ans = solve(m, true, sum);
        // reverse(ans.second.begin(), ans.second.end());
        // for(int i = 0; i < ans.second.size(); i++) cout << ans.second[i] << " ";
        // cout << "\n";
        // cout << ans.first.first << " " << ans.first.second << "\n";
    }
    
    return 0;
}