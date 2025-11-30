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

//UIUC IPL Team Tryout 2025 - M
//2021 ICPC Asia Shenyang Regional Contest - J

//smart solution is to observe that we only care about the difference from the initial to goal state. 
//so we can just do a one-source shortest path from '0000'. 

//dumb solution is to not observe that and instead optimize all-source shortest paths to run in time. 

string atos(array<int, 3> a) {
    return to_string(a[0]) + to_string(a[1]) + to_string(a[2]);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int idptr = 0;
    map<array<int, 3>, int> mp;
    for(int i = 0; i < 10; i++) for(int j = 0; j < 10; j++) for(int k = 0; k < 10; k++) {
        mp[{i, j, k}] = idptr ++;
    }
    vvi c(idptr);
    for(int i = 0; i < 10; i++) for(int j = 0; j < 10; j++) for(int k = 0; k < 10; k++) {
        array<int, 3> s = {i, j, k};
        array<int, 3> ns;
        int id = mp[s];
        for(int l = 0; l < 3; l++) for(int r = l + 1; r <= 3; r++){
            ns = s;
            for(int ii = l; ii < r; ii++) ns[ii] = (s[ii] + 1) % 10;
            int nid = mp[ns];
            c[id].push_back(nid);
            // cout << "EDGE : " << atos(s) << " " << atos(ns) << "\n";
        }
        for(int l = 0; l < 3; l++) for(int r = l + 1; r <= 3; r++){
            ns = s;
            for(int ii = l; ii < r; ii++) {
                ns[ii] = (s[ii] + 9) % 10;
                // cout << "II : " << (s[ii] + 9) % 10 << "\n";
            }
            int nid = mp[ns];
            c[id].push_back(nid);
            // cout << "EDGE : " << atos(s) << " " << atos(ns) << "\n";
        }
    }
    vvi d(idptr, vi(idptr));
    for(int i = 0; i < idptr; i++){
        d[i] = vi(idptr, 1e9);
        d[i][i] = 0;
        queue<int> q;
        q.push(i);
        // cout << "I : " << i << "\n";
        while(q.size()) {
            int cur = q.front();
            q.pop();
            // cout << "D : " << cur << " " << i << " " << d[i][cur] << "\n";
            for(int x : c[cur]) {
                if(d[i][x] != 1e9) continue;
                d[i][x] = d[i][cur] + 1;
                q.push(x);
            }
        }

    }

    int t;
    cin >> t;
    while(t--){
        string s, t;
        cin >> s >> t;
        int ans = 1e9;
        int fs = s[0] - '0';
        int ft = t[0] - '0';
        array<int, 3> tl = {t[1] - '0', t[2] - '0', t[3] - '0'};
        int tind = mp[tl];

        int incamt = (ft - fs + 10) % 10;
        int decamt = (fs - ft + 10) % 10;
        
        //increase
        array<int, 3> ss;
        if(incamt < 9) for(int i = 0; i <= incamt; i++) for(int j = 0; j <= i; j++) for(int k = 0; k <= j; k++) {
            int x1 = (s[1] - '0' + i) % 10;
            int x2 = (s[2] - '0' + j) % 10;
            int x3 = (s[3] - '0' + k) % 10;
            ss = {x1, x2, x3};
            int ind = mp[ss];
            ans = min(ans, incamt + d[ind][tind]);
            // cout << "D : " << atos(ss) << " " << atos(tl) << " " << d[ind][tind] << "\n";
        }
        //decrease
        if(decamt < 9) for(int i = 0; i <= decamt; i++) for(int j = 0; j <= i; j++) for(int k = 0; k <= j; k++) {
            int x1 = (s[1] - '0' - i + 10) % 10;
            int x2 = (s[2] - '0' - j + 10) % 10;
            int x3 = (s[3] - '0' - k + 10) % 10;
            ss = {x1, x2, x3};
            int ind = mp[ss];
            ans = min(ans, decamt + d[ind][tind]);
        }

        cout << ans << "\n";
    }
    
    return 0;
}