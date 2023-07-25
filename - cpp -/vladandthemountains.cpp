#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1851G

//lets say that you start at a mountain of height 'h', and you have 'e' energy. The highest mountain that you
//can go to is of height h + e. 

//thus, we can sort queries based off of this tallest height, and use a dsu datastructure to find if two nodes are connected. 

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
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        vector<int> h(n);
        for(int i = 0; i < n; i++){
            cin >> h[i];
        }
        vector<pair<int, int>> c(m);
        for(int i = 0; i < m; i++){
            cin >> c[i].first >> c[i].second;
            c[i].first --;
            c[i].second --;
        }
        int q;
        cin >> q;
        vector<vector<int>> queries(q, vector<int>(4));
        for(int i = 0; i < q; i++){
            int a, b, e;
            cin >> a >> b >> e;
            a --;
            b --;
            queries[i] = {a, b, e, i};
        }
        sort(queries.begin(), queries.end(), [&](vector<int>& a, vector<int>& b) -> bool {
            return (h[a[0]] + a[2]) < (h[b[0]] + b[2]);
        });
        sort(c.begin(), c.end(), [&](pair<int, int>& a, pair<int, int>& b) -> bool {
            return max(h[a.first], h[a.second]) < max(h[b.first], h[b.second]);
        });
        vector<bool> ans(q);
        DSU dsu(n);
        int cptr = 0;
        for(int i = 0; i < q; i++){
            int a = queries[i][0];
            int b = queries[i][1];
            int e = queries[i][2];
            while(cptr != m && h[a] + e >= max(h[c[cptr].first], h[c[cptr].second])) {
                dsu.unify(c[cptr].first, c[cptr].second);
                cptr ++;
            }
            ans[queries[i][3]] = dsu.find(a) == dsu.find(b);
        }
        for(int i = 0; i < q; i++){
            cout << (ans[i]? "YES\n" : "NO\n");
        }
    }
    
    return 0;
}
