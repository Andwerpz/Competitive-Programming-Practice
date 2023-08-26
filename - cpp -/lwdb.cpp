#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 2015 ICL Finals, Div 1, D
//https://codeforces.com/gym/100633/my

//relatively standard centroid decomposition problem. 

//for each node, we'll store all the assignments that have happened to that node's subtree in a monotonic map. 
//we're interested in the 'extension distance', which is the extra distance leftover after visiting node i to travel to some other node in 
//the subtree, and the 'color index', which is simply the number of color assignments that have come before this one. 

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
    vector<vector<pair<int, ll>>> edges;
    vector<int> depth;  //distance of each node from the root
    vector<int> dist_depth; //weighted distance of each node from root

    vector<int> left_occ, right_occ;   //leftmost and rightmost occurrences for each node in the euler tour
    
    //single assignment modify, range min query
    //stores the euler tour of the tree to compute lca
    Segtree segt;

    void euler_tour(int cur, int p, vector<int>& ret) {
        left_occ[cur] = ret.size();
        ret.push_back(cur);
        for(int i = 0; i < edges[cur].size(); i++){
            int next = edges[cur][i].first;
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
            int next = edges[cur][i].first;
            if(next == p){
                continue;
            }
            depth[next] = depth[cur] + 1;
            find_depth(next, cur);
        }
    }

    void find_weighted_depth(int cur, int p) {
        for(int i = 0; i < edges[cur].size(); i++){
            int next = edges[cur][i].first;
            ll weight = edges[cur][i].second;
            if(next == p){
                continue;
            }
            dist_depth[next] = dist_depth[cur] + weight;
            find_weighted_depth(next, cur);
        }
    }

    void init(int n, int root, vector<vector<pair<int, ll>>>& edges) {
        this->n = n;
        this->root = root;
        this->edges = edges;

        this->depth = vector<int>(n, 0);
        find_depth(root, -1);

        this->dist_depth = vector<int>(n, 0);
        find_weighted_depth(root, -1);

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
    LCA(int n, int root, vector<vector<pair<int, ll>>> edges) {
        init(n, root, edges);
    }

    int lca(int a, int b) {
        int l = min(left_occ[a], left_occ[b]);
        int r = max(right_occ[a], right_occ[b]);
        int lc = segt.query(l, r);
        return lc;
    }

    ll dist(int a, int b) {
        int lc = lca(a, b);
        return depth[a] + depth[b] - 2 * depth[lc];
    }

    ll weighted_dist(int a, int b) {
        int lc = lca(a, b);
        return dist_depth[a] + dist_depth[b] - 2 * dist_depth[lc];
    }
};

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

void insert(map<ll, int>& m, ll ext_dist, int color_ind) {
    if(ext_dist < 0){
        return;
    }
    //remove all entries with extension dist <= current dist
    while(m.size() != 0 && m.begin() -> first <= ext_dist) {
        m.erase(m.begin() -> first);
    }
    m.insert({ext_dist, color_ind});
}

int query(map<ll, int>& m, ll ext_dist) {
    //find the minimum element where dist >= ext_dist, and return the color index
    if(ext_dist < 0){
        return -1;
    }
    if(m.lower_bound(ext_dist) == m.end()) {
        return -1;
    }
    return m.lower_bound(ext_dist) -> second;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<vector<pair<int, ll>>> c(n, vector<pair<int, ll>>(0));
    vector<vector<int>> adj_list(n, vector<int>(0));
    for(int i = 0; i < n - 1; i++){
        int a, b;
        ll w;
        cin >> a >> b >> w;
        a --;
        b --;
        c[a].push_back({b, w});
        c[b].push_back({a, w});
        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
    }
    LCA lca(n, 0, c);
    CentroidDecomp cd;
    vector<int> cp = cd.calc_centroid_decomp(n, adj_list);
    vector<int> color(1, 0);
    //instead of doing this, might have to keep a monotonic set where the node color goes up, but the extension dist goes down. 
    //map extension dist to color index
    //as extension dist goes down, color index goes up
    vector<map<ll, int>> node_color(n, map<ll, int>());
    int q;
    cin >> q;
    while(q--) {
        int type;
        cin >> type;
        if(type == 1){
            int v, n_color;
            ll d;
            cin >> v >> d >> n_color;
            v --;
            color.push_back(n_color);
            int ptr = v;
            while(ptr != -1){
                ll dist = lca.weighted_dist(v, ptr);
                insert(node_color[ptr], d - dist, color.size() - 1);
                ptr = cp[ptr];
            }
        }
        else {
            int v;
            cin >> v;
            v --;
            int best_color = 0;
            int ptr = v;
            while(ptr != -1){
                ll dist = lca.weighted_dist(v, ptr);
                best_color = max(best_color, query(node_color[ptr], dist));
                ptr = cp[ptr];
            }
            cout << color[best_color] << "\n";
        }
    }
    
    return 0;
}
