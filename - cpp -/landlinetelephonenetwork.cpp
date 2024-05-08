#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Kattis - landline

//might seem like a simple mst problem at first, but there's a tricky edge case. 
//if all the nodes are insecure, then you have to create a complete graph. 

struct DSU {
    int N;
    vector<int> dsu;

    DSU(int n) {
        this->N = n;
        this->dsu = vector<int>(n, 0);
        for(int i = 0; i < n; i++){ //initialize roots
            dsu[i] = i;
        }
    }

    void dsu_init() {
        for(int i = 0; i < N; i++){
            dsu[i] = i;
        }
    }

    int find(int a) {
        if(dsu[a] == a) {
            return a;
        }
        return dsu[a] = find(dsu[a]);
    }

    //ret true if updated something
    bool unify(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if(ra == rb) {
            return false;
        }
        dsu[rb] = ra;
        return true;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, p;
    cin >> n >> m >> p;
    DSU dsu(n);
    vector<bool> insecure(n, false);
    for(int i = 0; i < p; i++){
        int next;
        cin >> next;
        next --;
        insecure[next] = true;
    }
    vector<vector<int>> c_sec(0);
    vector<vector<pair<int, int>>> c(n, vector<pair<int, int>>(0));
    for(int i = 0; i < m; i++){
        int a, b, cost;
        cin >> a >> b >> cost;
        a --;
        b --;
        bool ins = insecure[a] || insecure[b];
        c[a].push_back({cost, b});
        c[b].push_back({cost, a});
        if(!ins) {
            c_sec.push_back({cost, a, b});
        }
    }
    if(p == n){
        //all bad
        if(m != n * (n - 1) / 2) {
            cout << "impossible\n";
        }
        else {
            ll ans = 0;
            for(int i = 0; i < c.size(); i++){
                for(int j = 0; j < c[i].size(); j++){
                    ans += c[i][j].first;
                }
            }
            ans /= 2;
            cout << ans << "\n";
        }
        return 0;
    }
    sort(c_sec.begin(), c_sec.end());
    ll ans = 0;
    for(int i = 0; i < c_sec.size(); i++){
        int w = c_sec[i][0];
        int a = c_sec[i][1];
        int b = c_sec[i][2];
        if(dsu.unify(a, b)) {
            ans += w;
        }
    }
    int good_cmp = -1;
    for(int i = 0; i < n; i++){
        if(insecure[i]) {
            continue;
        }
        if(good_cmp == -1){
            good_cmp = dsu.find(i);
        }
        if(good_cmp != dsu.find(i)) {
            cout << "impossible\n";
            return 0;
        }
    }
    for(int i = 0; i < n; i++){
        if(!insecure[i]) {
            continue;
        }
        int min_w = 1e9;
        for(int j = 0; j < c[i].size(); j++){
            int w = c[i][j].first;
            int next = c[i][j].second;
            if(!insecure[next]) {
                min_w = min(min_w, w);
            }
        }
        if(min_w == 1e9){
            cout << "impossible\n";
            return 0;
        }
        ans += min_w;
    }
    cout << ans << "\n";
    
    return 0;
}
