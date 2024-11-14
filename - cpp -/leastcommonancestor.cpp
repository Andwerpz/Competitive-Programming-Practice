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

//Meta Hacker Cup 2024 Round 3 - B

//dumb mistake D:

//to solve for ancestors, we can do a dfs backtracking while maintaining two maps, fmap and smap. 
//fmap will map for each frequency, the set of indices in U with that frequency, and smap will map for every
//index in U, their frequency. Updating smap will allow to update fmap. 

//to solve for descendants, we can use a similar idea, but with DSU. 

//im pretty sure that this runs in O(n * log(n)^2), but idk. It takes around a minute to run. 

struct DSU {
    int N;
    vector<int> dsu, sz;
    vector<map<int, set<int>>> fmap;
    vector<map<int, int>> smap;

    DSU(int n) {
        this->N = n;
        this->dsu = vector<int>(n, 0);
        this->sz = vector<int>(n, 1);
        this->fmap = vector<map<int, set<int>>>(n);
        this->smap = vector<map<int, int>>(n);
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
        if(smap[ra].size() < smap[rb].size()) {
            swap(ra, rb);
        }
        //merge rb into ra
        dsu[rb] = ra;
        sz[ra] += sz[rb];
        for(auto i = smap[rb].begin(); i != smap[rb].end(); i++){
            int v = i->first;
            int amt = i->second;
            int oamt = smap[ra][v];
            int namt = oamt + amt;
            smap[ra][v] = namt;
            if(oamt != 0){
                fmap[ra][oamt].erase(v);
            }
            fmap[ra][namt].insert(v);
        }
        return true;
    }
};

void solveA(int cur, vvi& c, vi& a, map<int, set<int>>& fmap, map<int, int>& smap, vi& A) {
    if(smap.size() != 0){
        while(true) {
            int minamt = fmap.begin()->first;
            if(fmap[minamt].size() == 0){
                fmap.erase(minamt);
                continue;
            }
            A[cur] = *(fmap[minamt].begin());
            break;
        }
    }
    smap[a[cur]] ++;
    int amt = smap[a[cur]];
    if(amt != 1){
        fmap[amt - 1].erase(a[cur]);
    }
    fmap[amt].insert(a[cur]);
    if(amt != 1 && fmap[amt - 1].size() == 0){
        fmap.erase(amt - 1);
    }

    for(int i = 0; i < c[cur].size(); i++){
        solveA(c[cur][i], c, a, fmap, smap, A);
    }

    smap[a[cur]] --;
    fmap[amt].erase(a[cur]);
    if(amt != 1){
        fmap[amt - 1].insert(a[cur]);
    }
    if(fmap[amt].size() == 0){
        fmap.erase(amt);
    }
}

void solveD(int cur, vvi& c, vi& a, DSU& dsu, vi& D) {
    for(int i = 0; i < c[cur].size(); i++){
        solveD(c[cur][i], c, a, dsu, D);
    }

    for(int i = 0; i < c[cur].size(); i++){
        dsu.unify(cur, c[cur][i]);
    }

    int croot = dsu.find(cur);
    if(dsu.smap[croot].size() != 0){
        while(true){
            int minamt = dsu.fmap[croot].begin()->first;
            if(dsu.fmap[croot][minamt].size() == 0){
                dsu.fmap[croot].erase(minamt);
                continue;
            }
            D[cur] = *(dsu.fmap[croot][minamt].begin());
            break;
        }
        
    }

    dsu.smap[croot][a[cur]] ++;
    int amt = dsu.smap[croot][a[cur]];
    if(amt != 1){
        dsu.fmap[croot][amt - 1].erase(a[cur]);
    }
    dsu.fmap[croot][amt].insert(a[cur]);
    if(amt != 1 && dsu.fmap[croot][amt - 1].size() == 0){
        dsu.fmap[croot].erase(amt - 1);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ifstream in("least_common_ancestor_input.txt");
    streambuf *cinbuf = cin.rdbuf(); //save old buf
    cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
    
    ofstream out("--out--.txt");
    streambuf *coutbuf = cout.rdbuf(); //save old buf
    cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
    
    const ll mod = 998244353;
    int t;
    cin >> t;
    int casi = 0;
    while(t--){
        casi ++;
        int n;
        cin >> n;
        vvi c(n);
        vector<string> a(n);
        for(int i = 0; i < n; i++){
            int p;
            cin >> p >> a[i];
            if(p != -1){
                c[p - 1].push_back(i);
            }
        }
        ll u;
        vi aind(n, -1);
        {   
            set<string> s;
            for(int i = 0; i < n; i++){
                s.insert(a[i]);
            }
            map<string, int> m;
            for(auto i = s.begin(); i != s.end(); i++){
                m[*i] = m.size();
            }
            for(int i = 0; i < n; i++){
                aind[i] = m[a[i]];
            }
            u = s.size() + 1;
        }
        map<int, set<int>> fmap;
        map<int, int> smap;
        DSU dsu(n);
        vi A(n, -1), D(n, -1);
        solveA(0, c, aind, fmap, smap, A);
        solveD(0, c, aind, dsu, D);
        ll ans = 0;
        for(int i = 0; i < n; i++){
            ans = (ans * u) + A[i] + 1;
            ans %= mod;
            ans = (ans * u) + D[i] + 1;
            ans %= mod;
        }
        cout << "Case #" << casi << ": " << ans << "\n";
        // for(int i = 0; i < n; i++){
        //     cout << A[i] + 1 << " ";
        // }
        // cout << "\n";
        // for(int i = 0; i < n; i++){
        //     cout << D[i] + 1 << " ";
        // }
        // cout << "\n";
    }
    
    return 0;
}