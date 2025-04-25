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

//Codeforces - 2086C

//a permutation can be viewed as a collection of cycles. When you remove the element and enforce that replacing
//it has to form it's own cycle, then you need to replace all elements of the cycle that it was a part of as well.

//use dsu to conveniently find cycles. 

struct DSU {
    int N;
    vector<int> dsu, sz;

    DSU() {}
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
        if(sz[rb] > sz[ra]) swap(ra, rb);
        //merge rb into ra
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
        int n;
        cin >> n;
        DSU dsu(n);
        vi p(n);
        for(int i = 0; i < n; i++){
            cin >> p[i];
            p[i] --;
            dsu.unify(i, p[i]);
        }
        map<int, int> m;
        for(int i = 0; i < n; i++){
            m[dsu.find(i)] = dsu.get_sz(i);
        }
        int ans = 0;
        for(int i = 0; i < n; i++){
            int d;
            cin >> d;
            d --;
            d = dsu.find(d);
            ans += m[d];
            m[d] = 0;
            cout << ans << " ";
        }
        cout << "\n";
    }
    
    return 0;
}