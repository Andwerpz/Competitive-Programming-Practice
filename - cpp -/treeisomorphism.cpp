#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//SPOJ - TREEISO

//checking whether two rooted trees are isomorphic is not too hard, we just have to come up with a hashing function
//for a tree, and apply it recursively on the subtrees until we've hashed the entire tree. 

//then, to check if two unrooted trees are isomorphic, we can turn them both into rooted trees. We just need to find
//the centroid for the two trees, and since there can be at most 2 centroids, we need to check up to 4 combinations
//of roots. 

//takes in adjacency list, returns a list of the centroids of the tree. 
vector<int> findCentroid(const vector<vector<int>> &g) {
    int n = g.size();
    vector<int> centroid;
    vector<int> sz(n);
    function<void (int, int)> dfs = [&](int u, int prev) {
            sz[u] = 1;
            bool is_centroid = true;
            for (auto v : g[u]) if (v != prev) {
                    dfs(v, u);
                    sz[u] += sz[v];
                    if (sz[v] > n / 2) is_centroid = false;
            }
            if (n - sz[u] > n / 2) is_centroid = false;
            if (is_centroid) centroid.push_back(u);
    };
    dfs(0, -1);
    return centroid;
}

vector<ll> primes = {1000000007, 1000000009, 1000000021, 1000000033};

ll cantor(ll a, ll b, ll m) {
    return ((a + b) * (a + b + 1) / 2 + b) % m;
}

ll get_hash(int cur, int p, vector<vector<int>>& c, ll mod) {
    vector<ll> hash(0);
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        hash.push_back(get_hash(next, cur, c, mod));
    }
    sort(hash.begin(), hash.end());
    ll ans = c[cur].size();
    for(int i = 0; i < hash.size(); i++){
        ans = cantor(ans, hash[i], mod);
    }
    return ans;
}

bool areEqual(vector<vector<int>>& c1, vector<vector<int>>& c2, int cent1, int cent2) {
    for(int i = 0; i < primes.size(); i++){
        if(get_hash(cent1, -1, c1, primes[i]) != get_hash(cent2, -1, c2, primes[i])) {
            return false;
        }
    }
    return true;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<vector<int>> c1(n, vector<int>(0));
        vector<vector<int>> c2(n, vector<int>(0));
        for(int i = 0; i < n - 1; i++){
            int a, b;
            cin >> a >> b;
            a --;
            b --;
            c1[a].push_back(b);
            c1[b].push_back(a);
        }
        for(int i = 0; i < n - 1; i++){
            int a, b;
            cin >> a >> b;
            a --;
            b --;
            c2[a].push_back(b);
            c2[b].push_back(a);
        }
        vector<int> cent1 = findCentroid(c1);
        vector<int> cent2 = findCentroid(c2);
        bool is_valid = false;
        for(int i = 0; i < cent1.size(); i++){
            for(int j = 0; j < cent2.size(); j++){
                if(areEqual(c1, c2, cent1[i], cent2[j])) {
                    //cout << "EQUAL : " << cent1[i] << " " << cent2[j] << "\n";
                    is_valid = true;
                }
            }
        }
        cout << (is_valid? "YES" : "NO") << "\n";
    }
    
    return 0;
}
