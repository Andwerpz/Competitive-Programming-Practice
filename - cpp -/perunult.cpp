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

//Codeforces - 912C

//implementation problem :/
//how dis a 2500. To be fair, there are some very difficult edge cases to think about, and without
//access to the testcases i probably would've been very annoyed. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    ll bounty, increase, damage;
    cin >> bounty >> increase >> damage;
    vvl a(n, vl(3));    //{max health, start heath, regen}
    bool can_inf = false;
    for(int i = 0; i < n; i++){
        cin >> a[i][0] >> a[i][1] >> a[i][2];
        if(a[i][0] <= damage) {
            can_inf = true;
        }
    }
    vector upd(n, vector<pll>());   //{time, health}
    for(int i = 0; i < m; i++){
        ll t, e, h;
        cin >> t >> e >> h;
        e --;
        upd[e].push_back({t, h});
    }
    map<ll, ll> ev;
    for(int i = 0; i < n; i++){
        ll sh = a[i][1];
        ll reg = a[i][2];
        upd[i].push_back({0, sh});
        sort(upd[i].begin(), upd[i].end());
        bool p_exit = true;
        for(int j = 0; j < upd[i].size(); j++){
            ll curh = upd[i][j].second;
            ll curt = upd[i][j].first;
            if(p_exit && curh <= damage) {
                ev[curt] ++;
                p_exit = false;
            }
            else if(!p_exit && curh > damage) {
                ev[curt] --;
                p_exit = true;
            }
            if(!p_exit && reg != 0) {
                //see if curh will exceed damage before time
                ll et = ((damage + 1) - curh + reg - 1) / reg;
                ll dt = et + 1;
                if(j != upd[i].size() - 1) {
                    dt = upd[i][j + 1].first - curt;
                }
                if(et > 0 && et < dt) {
                    ev[curt + et] --;
                    p_exit = true;
                }
            }
        }
        if(!p_exit && reg == 0) {
            can_inf = true;
        }
    }
    if(can_inf && increase != 0) {
        cout << "-1\n";
        return 0;
    }
    ll cnt = 0;
    ll ans = 0;
    for(auto i = ev.begin(); i != ev.end(); i++){
        ll curt = i->first;
        ans = max(ans, cnt * (bounty + (curt - 1) * increase));
        cnt += i->second;
        ans = max(ans, cnt * (bounty + curt * increase));
    }
    cout << ans << "\n";
    
    return 0;
}