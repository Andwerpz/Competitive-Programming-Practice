#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1296F

//for each query, we can just update all the edges on the path with g. Note that the minimum beauty 
//for each edge is equal to the maximum g value that passes through it. 

//to find the path from any two nodes, we can just root the tree arbitrarily, and compute the lca
//for nodes a and b. Then, we can just go from a to lca, and b to lca. Finding lca takes log(n) time. 

//then, to check if the edge beauties are valid, we can just go again through the queries, and see if they all are
//valid on our generated tree. 

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<vector<int>> c(n, vector<int>(0));
    vector<vector<int>> edgeInd(n, vector<int>(0));
    for(int i = 0; i < n - 1; i++){
        int a, b;
        cin >> a >> b;
        a --;
        b --;
        c[a].push_back(b);
        edgeInd[a].push_back(i);
        c[b].push_back(a);
        edgeInd[b].push_back(i);
    }
    int root = 0;
    LCA lca(n, root, c);
    vector<int> parent(n, -1);
    vector<int> parentEdgeInd(n, -1);
    stack<int> s;
    s.push(root);
    while(s.size() != 0){
        int cur = s.top();
        s.pop();
        for(int i = 0; i < c[cur].size(); i++){
            int next = c[cur][i];
            if(next == parent[cur]) {
                continue;
            }
            parent[next] = cur;
            parentEdgeInd[next] = edgeInd[cur][i];
            s.push(next);
        }
    }
    vector<int> ans(n - 1, 1);
    int m;
    cin >> m;
    bool isValid = true;
    vector<vector<int>> queries(m, vector<int>(3));
    for(int i = 0; i < m; i++) {
        int a, b, g;
        cin >> a >> b >> g;
        a --;
        b --;
        queries[i] = {a, b, g};
        int _lca = lca.lca(a, b);
        while(a != _lca) {
            ans[parentEdgeInd[a]] = max(ans[parentEdgeInd[a]], g);
            a = parent[a];
        }
        while(b != _lca) {
            ans[parentEdgeInd[b]] = max(ans[parentEdgeInd[b]], g);
            b = parent[b];
        }
    }
    for(int i = 0; i < m; i++){
        int a = queries[i][0];
        int b = queries[i][1];
        int g = queries[i][2];
        int _lca = lca.lca(a, b);
        int mnBeauty = 1e9;
        while(a != _lca) {
            mnBeauty = min(mnBeauty, ans[parentEdgeInd[a]]);
            a = parent[a];
        }
        while(b != _lca) {
            mnBeauty = min(mnBeauty, ans[parentEdgeInd[b]]);
            b = parent[b];
        }
        if(mnBeauty != g){
            isValid = false;
        }
    }
    if(!isValid) {
        cout << "-1\n";
        return 0;
    }
    for(int i = 0; i < n - 1; i++){
        cout << ans[i] << " ";
    }
    cout << "\n";
    
    return 0;
}
