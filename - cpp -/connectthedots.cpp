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

//Codeforces - 2020D

//for each (d, a % d) pair, we can keep a seperate pointer to the maximum right node that it touched. 
//then, just have to use DSU to unify components. 

struct DSU {
    int N;
    vector<int> dsu, sz;

    DSU(int n) {
        this->N = n;
        this->dsu = vector<int>(n, 0);
        this->sz = vector<int>(n, 1);
        for(int i = 0; i < n; i++){ //initialize roots
            dsu[i] = i;
        }
    }

    int find(int a) {
        if(dsu[a] == a) {
            return a;
        }
        return dsu[a] = find(dsu[a]);
    }

    int get_sz(int a){
        return sz[find(a)];
    }

    //ret true if updated something
    bool unify(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if(ra == rb) {
            return false;
        }
        dsu[rb] = ra;
        sz[ra] += sz[rb];
        return true;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        DSU dsu(n);
        int ans = n;
        vector q(m, tuple<int, int, int>());    //{a, d, k}
        for(int i = 0; i < m; i++){
            int a, d, k;
            cin >> a >> d >> k;
            q[i] = {a, d, k};
        }
        // sort(q.begin(), q.end(), [](vi& a, vi& b) -> bool {
        //     return a[0] < b[0];
        // });
        sort(q.begin(), q.end());
        vvi rptr(11, vi(11, 0));
        for(int i = 0; i < m; i++){
            int a = get<0>(q[i]) - 1;
            int d = get<1>(q[i]);
            int k = get<2>(q[i]);
            // cout << "ADK : " << a << " " << d << " " << k << "\n";
            int nr = a + d * k;
            a = max(a, rptr[d][a % d]);
            rptr[d][a % d] = max(rptr[d][a % d], nr);
            while(a < nr){
                ans -= dsu.unify(a, a + d);
                a += d;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}