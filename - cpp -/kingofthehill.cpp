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

// BAPC 2023 - K

//not sure how the editorial solution works, apparently if you binary search both horizontally and vertically 
//at the same time, then it works??

bool debug = true;
vvi jg;
int n;

vvi g;
int qcnt = 0, ans = 0;
int interact(int r, int c) {
    assert(r >= 0 && r < n && c >= 0 && c < n);
    if(g[r][c] != -1) return g[r][c];
    cout << "? " << (r + 1) << " " << (c + 1) << endl;
    qcnt ++;
    // cout << "QCNT : " << qcnt << endl;
    assert(qcnt <= 10 * n + 100);
    int ret;
    if(debug) {
        ret = jg[r][c];
    }
    else {
        cin >> ret;
    }
    ans = max(ans, ret);
    g[r][c] = ret;
    return g[r][c];
}

int solve(int n) {
    g = vvi(n, vi(n, -1));
    qcnt = 0;

    if(debug) {
        jg = vvi(n, vi(n));
        for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) cin >> jg[i][j];
        vi dr = {-1, 1, 0, 0}, dc = {0, 0, -1, 1};

        // srand(time(0));
        // vvb v(n, vb(n, false));
        // priority_queue<pair<int, pii>> q;
        // int sr, sc;
        // cin >> sr >> sc;
        // q.push({0, {sr, sc}});
        // v[sr][sc] = true;
        
        // int vptr = n * n;
        // while(q.size()) {
        //     int r = q.top().second.first;
        //     int c = q.top().second.second;
        //     q.pop();
        //     jg[r][c] = vptr --;
        //     for(int i = 0; i < 4; i++) {
        //         int nr = r + dr[i];
        //         int nc = c + dc[i];
        //         if(nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
        //         if(v[nr][nc]) continue;
        //         v[nr][nc] = true;
        //         q.push({rand(), {nr, nc}});
        //     }
        // }
        // assert(vptr == 0);

        // for(int i = 0; i < n; i++) {
        //     for(int j = 0; j < n; j++) cout << jg[i][j] << " ";
        //     cout << "\n";
        // }

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(jg[i][j] == n * n) continue;
                bool ispeak = true;
                for(int k = 0; k < 4; k++ ){
                    int nr = i + dr[k];
                    int nc = j + dc[k];
                    if(nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
                    if(jg[i][j] < jg[nr][nc]) ispeak = false;
                }
                assert(!ispeak);
            }
        }
    }

    int rlow = 0, rhigh = n;
    int clow = 0, chigh = n;
    bool do_row = true;
    while((rhigh - rlow) * (chigh - clow) > 4) {
        cout << "QUERY : " << rlow << " " << rhigh << " " << clow << " " << chigh << endl;
        if(do_row) {
            int rmid = rlow + (rhigh - rlow) / 2;
            int mx = -1, mxc = -1;
            for(int i = clow; i < chigh; i++) {
                int val = interact(rmid, i);
                if(val > mx) {
                    mx = val;
                    mxc = i;
                }
            }
            assert(mxc != -1);
            int upv = -1, dwv = -1;
            if(rmid != 0) upv = interact(rmid - 1, mxc);
            if(rmid != n - 1) dwv = interact(rmid + 1, mxc);
            assert(upv != dwv);
            if(upv > dwv) rhigh = rmid + 1;
            else rlow = rmid;
        }
        else {
            int cmid = clow + (chigh - clow) / 2;
            cout << "CMID : " << cmid << endl;
            int mx = -1, mxr = -1;
            for(int i = rlow; i < rhigh; i++) {
                int val = interact(i, cmid);
                if(val > mx) {
                    mx = val;
                    mxr = i;
                }
            }
            assert(mxr != -1);
            int lv = -1, rv = -1;
            if(cmid != 0) lv = interact(mxr, cmid - 1);
            if(cmid != n - 1) rv = interact(mxr, cmid + 1);
            assert(lv != rv);
            if(lv > rv) chigh = cmid + 1;
            else clow = cmid;
        }
        do_row = !do_row;
    }
    cout << "END : " << rlow << " " << rhigh << " " << clow << " " << chigh << "\n";
    for(int i = rlow; i < rhigh; i++) for(int j = clow; j < chigh; j++) interact(i, j);
    cout << "! " << ans << endl;
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> n;
    if(debug) {
        while(1) {
            int ans = solve(n);
            if(ans != n * n) {
                for(int i = 0; i < n; i++) {
                    for(int j = 0; j < n; j++) cout << jg[i][j] << " ";
                    cout << "\n";
                }
                assert(false);
            }
        }
    }
    else {
        solve(n);
    }
    
    return 0;
}