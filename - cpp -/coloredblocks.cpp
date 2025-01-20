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

//M(IT)^2 Winter 2025 Advanced Round 2 - P5

//greedy solution that I don't really understand how it works. 

//first, fix the amount of rows to be k. Go from left to right and add each element to one of the rows. 
//When we add an element to a row, we create a 'deadline' that ends on the kth next occurrence of the same value we
//just placed. When placing a value, we should satisfy the deadline that is closest to the right by placing it
//in the same row. Note that you can't satisfy a deadline from an element that is the same color. 

//we can see that if k rows works then k + 1 definitely works, so we can just binary search for the answer. 

bool is_valid(int k, vvi& g, vi& a, vi& ans) {
    int n = a.size();
    for(int i = 0; i < n; i++){
        ans[i] = -1;
    }
    vi r(n, 1e9);
    for(int i = 0; i < g.size(); i++){
        for(int j = 0; j + k < g[i].size(); j++){
            r[g[i][j]] = g[i][j + k];
        }
    }
    int asum = 0;
    vi rptr(g.size(), 0), active(g.size(), 0);
    int row_ptr = 0;
    priority_queue<array<int, 3>> q;  //{-r, c, r_ind}
    for(int i = 0; i < n; i++){
        array<int, 3> nxt = {1, -1, -1};
        if(q.size() != 0) {
            array<int, 3> tmp = q.top();
            q.pop();
            if(tmp[1] == a[i]) {
                if(q.size() != 0) nxt = q.top(), q.pop();
                q.push(tmp);
            }
            else nxt = tmp;
        }
        if(nxt[0] != 1) {
            int nr = -nxt[0], nc = nxt[1], n_rind = nxt[2];
            if(nr <= i) return false;
            ans[i] = n_rind;
            asum --;
            active[nc] --;
            rptr[nc] ++;
            if(active[nc] != 0) {
                q.push({-r[g[nc][rptr[nc]]], nc, ans[g[nc][rptr[nc]]]});
            }
        }
        asum ++;
        active[a[i]] ++;
        if(ans[i] == -1) ans[i] = row_ptr ++;
        if(active[a[i]] == 1) {
            q.push({-r[i], a[i], ans[i]});
        }
        if(asum > k) return false;
    }
    while(q.size() != 0){
        int nr = -q.top()[0];
        q.pop();
        if(nr <= n) return false;
    }
    if(row_ptr > k) return false;
    return true;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vi a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        vvi g;
        {
            map<int, vi> m;
            for(int i = 0; i < n; i++) m[a[i]].push_back(i);
            for(auto i = m.begin(); i != m.end(); i++) g.push_back(i->second);
            for(int i = 0; i < g.size(); i++){
                for(int x : g[i]) a[x] = i;
            }
        }
        int low = 1, high = n;
        int ans = n;
        vi ansv(n);
        while(low <= high) {
            int mid = low + (high - low) / 2;
            if(is_valid(mid, g, a, ansv)) ans = mid, high = mid - 1;
            else low = mid + 1; 
        }
        cout << ans << "\n";
        vvi rows(ans);
        is_valid(ans, g, a, ansv);
        for(int i = 0; i < n; i++){
            rows[ansv[i]].push_back(i + 1);
        }
        for(int i = 0; i < rows.size(); i++){
            cout << rows[i].size() << " ";
            for(int x : rows[i]) cout << x << " ";
            cout << "\n";
        }
    }
    
    return 0;
}