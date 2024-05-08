#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//UTPC Spring 2024 Open Contest - B

//note that one record can only be adjacent to up to 2 other records, and if there is a cycle in the 
//adjacency graph, then it's impossible. 

//otherwise, each component can be arranged up to 2 ways, except if the size of the component is 1, then it can
//only be arranged in 1 way. 

//then, we can permute the components any way we want. 

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    DSU dsu(n);
    bool is_valid = true;
    vector<int> deg(n, 0);
    for(int i = 0; i < k; i++){
        int a, b;
        cin >> a >> b;
        a --;
        b --;
        deg[a] ++;
        deg[b] ++;
        if(!dsu.unify(a, b)) {
            is_valid = false;
        }
    }
    for(int i = 0; i < n; i++){
        if(deg[i] > 2){
            is_valid = false;
        }
    }
    if(!is_valid){
        cout << "-1\n";
        return 0;
    }
    set<int> v1, v2;
    ll mod = 1e9 + 7;
    ll ans = 1;
    for(int i = 0; i < n; i++){
        int next = dsu.find(i);
        if(v1.find(next) != v1.end()) {
            if(v2.find(next) == v2.end()) {
                ans *= 2;
                ans %= mod;
                v2.insert(next);
            }
        }
        v1.insert(next);
    }
    for(ll i = 1; i <= v1.size(); i++){
        ans *= i;
        ans %= mod;
    }
    cout << ans << "\n";
    
    return 0;
}
