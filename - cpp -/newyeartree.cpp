#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef std::pair<int, int> pii;
typedef std::pair<ll, ll> pll;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 379F

//let the endpoints of the old diameter be A and B. If you add a new node X to the tree, then the
//diameter of the new tree has to be one of dist(A, B), dist(A, X), or dist(B, X). 

//we can easily find distances between nodes on a tree using LCA. 

struct LCA {
    struct Segtree {
        //note that t[0] is not used
        int n;
        int* t;
        int* node_id;
        int uneut, qneut;

        //single element modification function
        function<int(int, int)> fmodify;

        //product of two elements for query and updating tree
        function<int(int, int)> fcombine;

        Segtree() {
            //do nothing
        }

        Segtree(int n, int updateNeutral, int queryNeutral, function<int(int, int)> fmodify, function<int(int, int)> fcombine) {
            this -> n = n;
            t = new int[2 * n];
            node_id = new int[2 * n];

            this -> fmodify = fmodify;
            this -> fcombine = fcombine;

            uneut = updateNeutral;
            qneut = queryNeutral;

            for(int i = 0; i < 2 * n; i++){
                t[i] = uneut;
                node_id[i] = 0;
            }
        }

        void build() { // build the tree after manually assigning the values.
            for (int i = n - 1; i > 0; i--) {   
                t[i] = fcombine(t[i * 2], t[i * 2 + 1]);
                node_id[i] = t[i] == t[i * 2]? node_id[i * 2] : node_id[i * 2 + 1];
            }
        }

        int query(int l, int r) { // least deep node on interval [l, r)
            int min_depth = 1e9;
            int res = -1;
            for (l += n, r += n; l < r; l /= 2, r /= 2) {
                if (l % 2 == 1) {
                    if(t[l] < min_depth) {
                        res = node_id[l];
                        min_depth = t[l];
                    }
                    l++;
                }
                if (r % 2 == 1) {
                    r--;
                    if(t[r] < min_depth) {
                        res = node_id[r];
                        min_depth = t[r];
                    }
                }
            }
            return res;
        }
    };

    int n;
    int root;
    vector<vector<int>> edges;
    vector<int> depth;  //distance of each node from the root

    vector<int> left_occ, right_occ;   //leftmost and rightmost occurrences for each node in the euler tour
    
    //single assignment modify, range min query
    //stores the euler tour of the tree to compute lca
    Segtree segt;

    void euler_tour(int cur, int p, vector<int>& ret) {
        left_occ[cur] = ret.size();
        ret.push_back(cur);
        for(int i = 0; i < edges[cur].size(); i++){
            int next = edges[cur][i];
            if(next == p){
                continue;
            }
            euler_tour(next, cur, ret);
            ret.push_back(cur);
        }
        right_occ[cur] = ret.size();
    }

    void find_depth(int cur, int p) {
        for(int i = 0; i < edges[cur].size(); i++){
            int next = edges[cur][i];
            if(next == p){
                continue;
            }
            depth[next] = depth[cur] + 1;
            find_depth(next, cur);
        }
    }

    void init(int n, int root, vector<vector<int>>& edges) {
        this->n = n;
        this->root = root;
        this->edges = edges;

        this->depth = vector<int>(n, 0);
        find_depth(root, -1);

        vector<int> tour(0);
        this->left_occ = vector<int>(n, -1);
        this->right_occ = vector<int>(n, -1);
        euler_tour(root, -1, tour);

        function<int(int, int)> fmodify = [](const int src, const int val) -> int{return val;};
        function<int(int, int)> fcombine = [](const int a, const int b) -> int{return min(a, b);};
        this->segt = Segtree(tour.size(), 0, 1e9, fmodify, fcombine);
        for(int i = 0; i < tour.size(); i++){
            segt.node_id[i + tour.size()] = tour[i];
            segt.t[i + tour.size()] = depth[tour[i]];
        }
        segt.build();
    }

    //adjacency list constructor
    LCA(int n, int root, vector<vector<int>> edges) {
        init(n, root, edges);
    }

    LCA() {}

    //parent list constructor
    //if node i is the root, then parents[i] must equal -1
    LCA(int n, vector<int> parents) {
        int root = -1;
        vector<vector<int>> edges(n, vector<int>(0));
        for(int i = 0; i < n; i++){
            if(parents[i] == -1){
                root = i;
            }
            edges[parents[i]].push_back(i);
            edges[i].push_back(parents[i]);
        }
        init(n, root, edges);
    }

    int lca(int a, int b) {
        int l = min(left_occ[a], left_occ[b]);
        int r = max(right_occ[a], right_occ[b]);
        int lc = segt.query(l, r);
        return lc;
    }

    int dist(int a, int b) {
        int lc = lca(a, b);
        return depth[a] + depth[b] - 2 * depth[lc];
    }

};

vector<vector<int>> c;
void add_edge(int u, int v) {
    c[u].push_back(v);
    c[v].push_back(u);
}

LCA lca;
int a = 1, b = 2, diam = 2;
void update_diam(int x) {
    if(lca.dist(a, x) > diam) {
        b = x;
        diam = lca.dist(a, x);
    }
    else if(lca.dist(b, x) > diam) {
        a = x;
        diam = lca.dist(b, x);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int q;
    cin >> q;
    int n = 4 + 2 * q;
    c = vector(n, vector<int>(0));
    add_edge(0, 1);
    add_edge(0, 2);
    add_edge(0, 3);
    vector<int> v(q);
    int ptr = 4;
    for(int i = 0; i < q; i++){
        cin >> v[i];
        v[i] --;
        add_edge(v[i], ptr ++);
        add_edge(v[i], ptr ++);
    }
    lca = LCA(n, 0, c);
    ptr = 4;
    for(int i = 0; i < q; i++){
        update_diam(ptr ++);
        update_diam(ptr ++);
        cout << diam << "\n";
    }
    
    return 0;
}