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

//Meta Hacker Cup 2025 Round 1 - A1 A2

//for A1 you can just take the maximum out of the adjacent segment height differences

//for A2, model the thing as a graph. Then, create a minimum spanning tree and the answer is just the
//maximum edge weight. 

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
    
    ifstream in("snake_scales_chapter_2_input.txt");
    streambuf *cinbuf = cin.rdbuf(); //save old buf
    cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
    
    ofstream out("--out--.txt");
    streambuf *coutbuf = cout.rdbuf(); //save old buf
    cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

    int t;
    cin >> t;
    int casi = 0;
    while(t--) {
        casi ++;
        int n;
        cin >> n;
        vi a(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        
        // //no ground
        // int ans = 0;
        // for(int i = 0; i < n - 1; i++) {
        //     ans = max(ans, abs(a[i] - a[i + 1]));
        // }

        //including ground
        int ans = 0;   
        DSU dsu(n + 1);
        vector<pair<int, pii>> e;  //{len, {u, v}}
        for(int i = 0; i < n - 1; i++) {
            e.push_back({abs(a[i] - a[i + 1]), {i, i + 1}});
        }
        for(int i = 0; i < n; i++) {
            e.push_back({a[i], {i, n}});
        }
        sort(e.begin(), e.end());
        int ccnt = n;
        for(int i = 0; i < e.size(); i++) {
            int len = e[i].first;
            int u = e[i].second.first;
            int v = e[i].second.second;
            if(dsu.unify(u, v)) {
                ccnt --;
                ans = max(ans, len);
            }
        }

        cout << "Case #" << casi << ": " << ans << "\n";
    }
    
    return 0;
}