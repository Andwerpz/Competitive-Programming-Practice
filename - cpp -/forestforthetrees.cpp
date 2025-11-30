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

pii rot90(pii x) {
    return {-x.second, x.first};
}

pii add(pii a, pii b) {
    return {a.first + b.first, a.second + b.second};
}

pii sub(pii a, pii b) {
    return {a.first - b.first, a.second - b.second};
}

int dist(pii a, pii b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

vector<pii> solve(vector<pii>& a, vector<pii>& b, int rmax, int rotamt) {
    rotamt %= 4;
    int nt = a.size(), ns = b.size();
    set<pii> bs;
    for(int i = 0; i < ns; i++) bs.insert(b[i]);
    for(int i = 0; i < nt; i++) for(int j = 0; j < rotamt; j++) a[i] = rot90(a[i]);
    vector<pii> ans;
    for(int i = 0; i < nt; i++) {
        pii rpos = sub(a[i], b[0]);
        int cnt = 0;
        bool is_valid = true;
        for(int j = 0; j < nt; j++) {
            if(dist(a[j], rpos) > rmax) continue;
            pii relpos = sub(a[j], rpos);
            if(relpos.first == 0 && relpos.second == 0) {
                is_valid = false;
                break;
            }
            if(!bs.count(relpos)) {
                is_valid = false;
                break;
            }
            // cout << "RELPOS : " << relpos.first
            cnt ++;
            if(cnt > ns) {
                is_valid = false;
                break;
            }
        }
        if(cnt != ns) is_valid = false;
        // cout << "CNT : " << cnt << " " << rpos.first << " " << rpos.second << "\n";
        if(is_valid) ans.push_back(rpos);
    }   
    for(int i = 0; i < nt; i++) for(int j = 0; j < (4 - rotamt) % 4; j++) a[i] = rot90(a[i]);
    for(int i = 0; i < ans.size(); i++) for(int j = 0; j < (4 - rotamt) % 4; j++) ans[i] = rot90(ans[i]);
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int nt, ns, rmax;
    cin >> nt >> ns >> rmax;
    vector<pii> a(nt);
    for(int i = 0; i < nt; i++) {
        cin >> a[i].first >> a[i].second;
    }
    vector<pii> b(ns);
    for(int i = 0; i < ns; i++) {
        cin >> b[i].first >> b[i].second;
    }
    vector<pii> ans;
    for(int i = 0; i < 4; i++) {
        vector<pii> cans = solve(a, b, rmax, i);
        // cout << "CANS : \n";
        // for(pii x : cans) cout << x.first << " " << x.second << "\n";
        for(pii x : cans) ans.push_back(x);
    }
    // cout << "ANS : \n";
    // for(int i = 0; i < ans.size(); i++) cout << ans[i].first << " " << ans[i].second << "\n";
    if(ans.size() == 1) cout << ans[0].first << " " << ans[0].second << "\n";
    else if(ans.size() > 1) cout << "Ambiguous\n";
    else cout << "Impossible\n";
    
    return 0;
}