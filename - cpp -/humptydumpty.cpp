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

//UTPC Contest 2-26-25 Div.1 - H

//implementation.

//we only have to consider platforms that have an empty space directly above them. 
//we can just compute the minimum and maximum falling distance for every platform from y = 0 to 1e5. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    set<pii> s;
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        int x, y;
        cin >> x >> y;
        s.insert({x, y});
    }
    vvi row(1e5 + 100); //only include elements that are not covered from above
    for(pii x : s){
        if(!s.count({x.first, x.second + 1})) {
            row[x.second].push_back(x.first);
        }
    }
    vector<map<int, int>> fmp_mx(1e5 + 100), fmp_mn(1e5 + 100);
    //insert 'ground'
    for(int i = 0; i < fmp_mx.size(); i++){
        fmp_mx[i][0] = 0;
        fmp_mn[i][0] = 0;
    }
    //for every row, compute fmp entries
    for(int i = 1; i < row.size(); i++){
        sort(row[i].begin(), row[i].end());
        for(int j = 0; j < row[i].size();){
            int rptr = j;
            int l = row[i][rptr];
            while(rptr + 1 != row[i].size() && row[i][rptr] + 1 == row[i][rptr + 1]) rptr ++;
            int r = row[i][rptr];
            int fall_amt_mx = 0, fall_amt_mn = 1e9;
            if(!s.count({l - 1, i + 1})) {
                fall_amt_mx = max(fall_amt_mx, max(fmp_mx[l - 1].rbegin()->second, i - fmp_mx[l - 1].rbegin()->first));
                fall_amt_mn = min(fall_amt_mn, max(fmp_mn[l - 1].rbegin()->second, i - fmp_mn[l - 1].rbegin()->first));
            }
            if(!s.count({r + 1, i + 1})) {
                fall_amt_mx = max(fall_amt_mx, max(fmp_mx[r + 1].rbegin()->second, i - fmp_mx[r + 1].rbegin()->first));
                fall_amt_mn = min(fall_amt_mn, max(fmp_mn[r + 1].rbegin()->second, i - fmp_mn[r + 1].rbegin()->first));
            }
            if(fall_amt_mn == 1e9) fall_amt_mn = 0;
            for(int k = l; k <= r; k++){
                fmp_mx[k][i] = fall_amt_mx;
                fmp_mn[k][i] = fall_amt_mn;
            }
            j = rptr + 1;
        }
    }
    int q;
    cin >> q;
    for(int i = 0; i < q; i++){
        int x, y;
        cin >> x >> y;
        auto ptr_mx = fmp_mx[x].upper_bound(y);
        ptr_mx --;
        int ans_mx = max(ptr_mx->second, y - ptr_mx->first - 1);
        auto ptr_mn = fmp_mn[x].upper_bound(y);
        ptr_mn --;
        int ans_mn = max(ptr_mn->second, y - ptr_mn->first - 1);
        cout << ans_mx << " " << ans_mn << "\n";
    }
    
    return 0;
}