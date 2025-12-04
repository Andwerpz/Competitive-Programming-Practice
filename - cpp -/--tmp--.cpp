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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vvi c(n), rc(n);
    for(int i = 0; i < n; i++) {
        int m;
        cin >> m;
        for(int j = 0; j < m; j++) {
            int p;
            cin >> p;
            p --;
            c[p].push_back(i);
            rc[i].push_back(p);
        }
    }
    int b;
    {
        int t;
        cin >> t;
        set<int> s;
        for(int i = 0; i < t; i++) {
            int p;
            cin >> p;
            if(s.count(p)) s.erase(p);
            else s.insert(p);
            b = max(b, (int) s.size());
        }
    }
    vi add(n, -1), rm(n, -1), addrm(n, -1);
    vi indeg(n, 0);
    for(int i = 0; i < n; i++) {
        for(int x : c[i]) {
            indeg[x] ++;
        }
    }
    queue<int> q;
    for(int i = 0; i < n; i++) {
        if(indeg[i] == 0) {
            q.push(i);
        }
    }
    vvi addo(n), rmo(n);
    while(q.size()) {
        int cur = q.front();
        q.pop();
        vi dep = rc[cur];
        //addo, rmo
        {
            sort(dep.begin(), dep.end(), [&](int a, int b) -> bool {
            return add[a] > add[b];
            });
            addo[cur] = dep;
            sort(dep.begin(), dep.end(), [&](int a, int b) -> bool {
                return rm[a] < rm[b];
            });
            rmo[cur] = dep;
        }
        //cost to add just this peg
        {
            for(int i = 0; i < dep.size(); i++) {
                add[cur] = max(add[cur], add[addo[cur][i]] + i);
            }
            add[cur] = max(add[cur], 1 + (int) dep.size());
            for(int i = 0; i < dep.size(); i++) {
                add[cur] = max(add[cur], rm[rmo[cur][i]] + (int) dep.size() - i);
            }
        }
        //cost to remove just this peg
        {
            for(int i = 0; i < dep.size(); i++) {
                rm[cur] = max(rm[cur], add[addo[cur][i]] + i + 1);
            }
            rm[cur] = max(rm[cur], 1 + (int) dep.size());
            for(int i = 0; i < dep.size(); i++) {
                rm[cur] = max(rm[cur], rm[rmo[cur][i]] + (int) dep.size() - i - 1);
            }
        }
        //cost to add + remove just this peg
        {
            for(int i = 0; i < dep.size(); i++) {
                addrm[cur] = max(addrm[cur], add[addo[cur][i]] + i);
            }
            addrm[cur] = max(addrm[cur], 1 + (int) dep.size());
            for(int i = 0; i < dep.size(); i++) {
                addrm[cur] = max(addrm[cur], rm[rmo[cur][i]] + (int) dep.size() - i - 1);
            }
        }
        //dependents
        for(int x : c[cur]) {
            indeg[x] --;
            if(indeg[x] == 0) {
                q.push(x);
            }
        }
    }   
    for(int i = 0; i < n; i++) {
        if(b * 10 < addrm[i]) {
            cout << "-1\n";
            return 0;
        }
    }
    function<void(int)> do_add, do_rm, do_addrm;
    vi ans;
    do_add = [&](int ind) -> void {
        for(int i = 0; i < addo[ind].size(); i++) {
            do_add(addo[ind][i]);
        }   
        ans.push_back(ind);
        for(int i = 0; i < rmo[ind].size(); i++) {
            do_rm(rmo[ind][i]);
        }
    };
    do_rm = [&](int ind) -> void {
        for(int i = 0; i < addo[ind].size(); i++) {
            do_add(addo[ind][i]);
        }   
        ans.push_back(ind);
        for(int i = 0; i < rmo[ind].size(); i++) {
            do_rm(rmo[ind][i]);
        }
    };
    do_addrm = [&](int ind) -> void {
        for(int i = 0; i < addo[ind].size(); i++) {
            do_add(addo[ind][i]);
        }   
        ans.push_back(ind);
        ans.push_back(ind);
        for(int i = 0; i < rmo[ind].size(); i++) {
            do_rm(rmo[ind][i]);
        }
    };

    for(int i = 0; i < n; i++) do_addrm(i);
    cout << ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++) cout << (ans[i] + 1) << "\n";

    for(int i = 0; i < n; i++) cout << add[i] << " ";
    cout << "\n";
    for(int i = 0; i < n; i++) cout << rm[i] << " ";
    cout << "\n";
    for(int i = 0; i < n; i++) cout << addrm[i] << " ";
    cout << "\n";

    
    return 0;
}