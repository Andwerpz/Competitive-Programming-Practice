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

//2024 NA Mid Central Regional - E

//DSU

const int N = 1000005;
int dsu[N];

void dsu_init() {
    for(int i = 0; i < N; i++){
        dsu[i] = i;
    }
}

int find(int a) {
    if(dsu[a] == a){
        return a;
    }
    return dsu[a] = find(dsu[a]);
}

bool unify(int a, int b) {
    int ra = find(a);
    int rb = find(b);
    if(ra == rb){
        return false;
    }
    dsu[rb] = ra;
    return true;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    dsu_init();
    int cnt = n;
    int ans = n == 1? 0 : -1;
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        u --;
        v --;
        cnt -= unify(u, v);
        if(cnt == 1 && ans == -1){
            ans = i + 1;
        }
    }
    cout << ans << "\n";
    
    return 0;
}