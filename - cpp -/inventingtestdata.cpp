#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

struct DSU {
    int N;
    vector<int> dsu;
    vector<int> max_edge;
    vector<int> size;

    DSU(int n) {
        this->N = n;
        this->dsu = vector<int>(n, 0);
        this->max_edge = vector<int>(n, 0);
        this->size = vector<int>(n, 0);
        for(int i = 0; i < n; i++){ //initialize roots
            dsu[i] = i;
            max_edge[i] = 0;
            size[i] = 1;
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
        max_edge[ra] = max(max_edge[ra], max_edge[rb]);
        size[ra] += size[rb];
        
        return true;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<pair<int, pair<int, int>>> e;
        ll ans = 0;
        for(int i = 0; i < n - 1; i++){
            int a, b, w;
            cin >> a >> b >> w;
            a --;
            b --;
            e.push_back({w, {a, b}});
            ans += w;
        }
        // cout << "DONE READING INPUT" << endl;
        sort(e.begin(), e.end());
        DSU dsu(n);
        for(int i = 0; i < e.size(); i++){
            int a = e[i].second.first;
            int b = e[i].second.second;
            int w = e[i].first;
            // cout << a << " " << b << " " << w << endl;
            int ra = dsu.find(a);
            int rb = dsu.find(b);
            ans += ((ll) dsu.size[ra] * (ll) dsu.size[rb] - 1) * (ll) (w + 1);
            dsu.unify(a, b);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
