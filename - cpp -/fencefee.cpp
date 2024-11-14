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

//NCPC 2024 - F

//just use shoelace while doing graph traversal. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ld PI = acos(-1);
    int e;
    cin >> e;
    int ptr = 0;
    map<pii, int> aind;
    vector<pii> a;
    vvi c;
    vvb cv;
    for(int i = 0; i < e; i++){
        pii u, v;
        cin >> u.first >> u.second >> v.first >> v.second;
        if(!aind.count(u)) {
            aind[u] = ptr ++;
            a.push_back(u);
            c.push_back({});
            cv.push_back({});
        }
        if(!aind.count(v)) {
            aind[v] = ptr ++;
            a.push_back(v);
            c.push_back({});
            cv.push_back({});
        }
        int ui = aind[u];
        int vi = aind[v];
        c[ui].push_back(vi);
        c[vi].push_back(ui);
        cv[ui].push_back(false);
        cv[vi].push_back(false);
    }
    int n = ptr;
    ld ans = 0;
    while(true){
        bool unv = true;
        ld carea = 0;
        int cnode = -1, cedge = -1;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < c[i].size(); j++){
                if(!cv[i][j]) {
                    unv = false;
                    cnode = i;
                    cedge = j;
                }
            }
        }
        if(unv){
            break;
        }
        // cout << "SNODE : " << cnode << " " << cedge << "\n";
        int snode = cnode;
        while(true){
            int nnode = c[cnode][cedge];
            cv[cnode][cedge] = true;
            pii cur = a[cnode];
            pii next = a[nnode];
            carea += (cur.first * next.second - cur.second * next.first) / (ld) 2.0;
            // cout << "EDGE : " << cur.first << " " << cur.second << ", " << next.first << " " << next.second << "\n";
            cnode = nnode;
            if(cnode == snode){
                break;
            }
            //figure out next edge
            pii cvec = {cur.first - next.first, cur.second - next.second};
            ld cpo = atan2(cvec.second, cvec.first);
            int nedge = -1;
            ld min_diff = 1e18;
            for(int i = 0; i < c[nnode].size(); i++){
                pii nnext = a[c[nnode][i]];
                if(nnext.first == cur.first && nnext.second == cur.second){
                    continue;
                }
                pii nvec = {nnext.first - next.first, nnext.second - next.second};
                ld npo = atan2(nvec.second, nvec.first);
                ld diff = cpo - npo;
                while(diff < 0){
                    diff += 2 * PI;
                }
                if(diff < min_diff){
                    min_diff = diff;
                    nedge = i;
                }
            }
            cedge = nedge;
        }
        // cout << "CAREA : " << carea << "\n";
        if(carea > 0){
            ans += carea * carea;
        }
    }
    cout << fixed << setprecision(10) << ans << "\n";
    
    return 0;
}