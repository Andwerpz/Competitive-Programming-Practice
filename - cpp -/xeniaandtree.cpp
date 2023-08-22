#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 342E

//classic centroid decomposition + lca path finding problem. 

//TODO write this. 

struct CentroidDecomp {
    CentroidDecomp() {
        //yay
    }

    vector<bool> vis;
    vector<int> centroid_parent;
    vector<int> size;   //size of subtree in original tree
    vector<vector<int>> edges;

    int find_size(int cur, int p = -1) {
        if(vis[cur]) {
            return 0;
        }
        size[cur] = 1;
        for(int i = 0; i < edges[cur].size(); i++){
            int next = edges[cur][i];
            if(next != p){
                size[cur] += find_size(next, cur);
            }
        }
        return size[cur];
    }

    int find_centroid(int cur, int p, int sub_size) {
        for(int i = 0; i < edges[cur].size(); i++){
            int next = edges[cur][i];
            if(next == p){
                continue;
            }
            if(!vis[next] && size[next] > sub_size / 2) {
                return find_centroid(next, cur, sub_size);
            }
        }
        return cur;
    }

    void init_centroid(int cur, int p = -1) {
        find_size(cur);
        int centroid = find_centroid(cur, -1, size[cur]);
        vis[centroid] = true;
        centroid_parent[centroid] = p;
        for(int i = 0; i < edges[centroid].size(); i++){
            int next = edges[centroid][i];
            if(!vis[next]){
                init_centroid(next, centroid);
            }
            
        }
    }

    //returns an array 'a' where the parent of node i is a[i]. 
    //if i is the root, then a[i] = -1. 
    vector<int> calc_centroid_decomp(int n, vector<vector<int>>& adj_list) {
        edges = adj_list;
        vis = vector<bool>(n, false);
        centroid_parent = vector<int>(n, -1);
        size = vector<int>(n, -1);
        init_centroid(0);
        return centroid_parent;
    }
};

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
    
    int n, m;
    cin >> n >> m;
    vector<vector<int>> c(n, vector<int>(0));
    for(int i = 0; i < n - 1; i++){
        int a, b;
        cin >> a >> b;
        a --;
        b --;
        c[a].push_back(b);
        c[b].push_back(a);
    }
    //find centroid decomposition of tree
    CentroidDecomp cd;
    vector<int> cd_parent = cd.calc_centroid_decomp(n, c);
    vector<int> min_dist(n, 1e9);   //minimum distance from a red node in the subtree to this node. 
    //do lca preprocessing
    LCA lca(n, 0, c);
    //paint node 0 red
    {   
        int v = 0;
        int ptr = v;
        while(ptr != -1){
            int dist = lca.dist(v, ptr);
            min_dist[ptr] = min(min_dist[ptr], dist);
            ptr = cd_parent[ptr];
        }
    }
    //process the queries
    while(m--) {
        int t, v;
        cin >> t >> v;
        v --;
        if(t == 1){
            //paint some blue node red
            int ptr = v;
            while(ptr != -1){
                int dist = lca.dist(v, ptr);
                min_dist[ptr] = min(min_dist[ptr], dist);
                ptr = cd_parent[ptr];
            }
        }
        else {
            //query shortest distance to red node
            int ans = 1e9;
            int ptr = v;
            while(ptr != -1){
                ans = min(ans, min_dist[ptr] + lca.dist(v, ptr));
                ptr = cd_parent[ptr];
            }
            cout << ans << "\n";
        }
    }
    
    return 0;
}
