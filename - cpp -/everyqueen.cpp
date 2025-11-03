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

//UIUC IPL Team Tryout 2025 - C

//pick an arbitrary queen, if every queen is attacking that one, then you've found your answer. 
//otherwise, there must be a queen that is not attacking this one. 

//then, observe that the number of cells that both these non-mutually attacking queens are both attacking
//is very limited, up to 12. The answer has to be one of them, so we can just try all of them. 

bool is_atk(pii queen, pii cell) {
    int dx = queen.first - cell.first;
    int dy = queen.second - cell.second;
    if(min(abs(dx), abs(dy)) == 0) return 1;
    if(abs(dx) == abs(dy)) return 1;
    return 0;
}

bool all_atk(vector<pii>& a, pii cell) {
    for(int i = 0; i < a.size(); i++) if(!is_atk(a[i], cell)) return false;
    return true;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<pii> a(n);
        for(int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
        int atk = -1;
        for(int i = 1; i < n; i++) {
            if(!is_atk(a[0], a[i])) atk = i;
        }
        if(atk == -1) {
            cout << "YES\n";
            cout << a[0].first << " " << a[0].second << "\n";
            continue;
        }
        bool found = false;
        pii ans; 
        // row col
        {
            pii cell = {a[0].first, a[atk].second};
            if(all_atk(a, cell)) {
                found = true;
                ans = cell;
            }
        }
        // col row
        {
            pii cell = {a[atk].first, a[0].second};
            if(all_atk(a, cell)) {
                found = true;
                ans = cell;
            }
        }
        // up diag, row
        {
            pii cell = {a[0].first, a[atk].second + (a[0].first - a[atk].first)};
            if(all_atk(a, cell)) {
                found = true;
                ans = cell;
            }
        }
        // up diag, col
        {
            pii cell = {a[atk].first + (a[0].second - a[atk].second), a[0].second};
            if(all_atk(a, cell)) {
                found = true;
                ans = cell;
            }
        }
        // down diag, row
        {
            pii cell  = {a[0].first, a[atk].second - (a[0].first - a[atk].first)};
            if(all_atk(a, cell)) {
                found = true;
                ans = cell;
            }
        }
        // down diag, col
        {
            pii cell = {a[atk].first - (a[0].second - a[atk].second), a[0].second};
            if(all_atk(a, cell)) {
                found = true;
                ans = cell;
            }
        }
        // row, up diag
        {
            pii cell = {a[atk].first, a[0].second + (a[atk].first - a[0].first)};
            if(all_atk(a, cell)) {
                found = true;
                ans = cell;
            }
        }
        // col, up diag
        {
            pii cell = {a[0].first + (a[atk].second - a[0].second), a[atk].second};
            if(all_atk(a, cell)) {
                found = true;
                ans = cell;
            }
        }
        // row down diag
        {
            pii cell = {a[atk].first, a[0].second - (a[atk].first - a[0].first)};
            if(all_atk(a, cell)) {
                found = true;
                ans = cell;
            }
        }
        // col, down diag
        {
            pii cell = {a[0].first - (a[atk].second - a[0].second), a[atk].second};
            if(all_atk(a, cell)) {
                found = true;
                ans = cell;
            }
        }
        // up diag, down diag
        {
            pii c1 = {a[0].first, a[atk].second - (a[0].first - a[atk].first)};
            pii c2 = {a[atk].first - (a[0].second - a[atk].second), a[0].second};
            pii cell = {(c1.first + c2.first) / 2, (c1.second + c2.second) / 2};
            if(all_atk(a, cell)) {
                found = true;
                ans = cell;
            }
        }
        // down diag, up diag
        {
            pii c1 = {a[atk].first, a[0].second - (a[atk].first - a[0].first)};
            pii c2 = {a[0].first - (a[atk].second - a[0].second), a[atk].second};
            pii cell = {(c1.first + c2.first) / 2, (c1.second + c2.second) / 2};
            if(all_atk(a, cell)) {
                found = true;
                ans = cell;
            }
        }
        // print ans
        if(found) {
            cout << "YES\n";
            cout << ans.first << " " << ans.second << "\n";
        }
        else {
            cout << "NO\n";
        }
    }
    
    return 0;
}