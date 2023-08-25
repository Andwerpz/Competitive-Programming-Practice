#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 766E

//holy moly this took a long time to debug. 

//this is pretty much a standard centroid decomposition problem, with some minor tweaks to account for xor. 

//for each node, we store the xor sum of all paths so far from the nodes in it's subtree. 
//note that we don't directly store the sum, we instead store the counts of bits that make up the sum
//so that we can perform xor on the sum. 

//the part that took the longest was figuring out how to account for double counting. To do this, we also keep track
//for each node, the contribution to the sum of the parent node. Then, when computing the answer contributed by the
//parent node, we can subtract the amount equal to whatever subtree we came from. 

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
    vector<int> val;    //value on each node. 
    vector<int> depth;  //distance of each node from the root, used to find lca. 
    vector<int> xor_depth;  //xor distance of each node from the root. 

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

    void find_xor_depth(int cur, int p) {
        for(int i = 0; i < edges[cur].size(); i++){
            int next = edges[cur][i];
            if(next == p){
                continue;
            }
            xor_depth[next] = xor_depth[cur] ^ val[next];
            find_xor_depth(next, cur);
        }
    }

    void init(int n, int root, vector<vector<int>>& edges, vector<int>& val) {
        this->n = n;
        this->root = root;
        this->edges = edges;
        this->val = val;

        this->depth = vector<int>(n, 0);
        find_depth(root, -1);

        this->xor_depth = vector<int>(n, 0);
        this->xor_depth[root] = val[root];
        find_xor_depth(root, -1);

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
    LCA(int n, int root, vector<vector<int>> edges, vector<int> val) {
        init(n, root, edges, val);
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

    int xor_dist(int a, int b) {
        int lc = lca(a, b);
        return xor_depth[a] ^ xor_depth[b] ^ val[lc];
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

ll solve_dfs(int cur, int p, vector<int>& val, vector<vector<int>>& c, ll psum, int start) {
    ll ans = 0;
    psum ^= val[cur];   
    if(start <= cur) {
        ans += psum;
    }
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        ans += solve_dfs(next, cur, val, c, psum, start);
    }
    return ans;
}

ll solve(int n, vector<vector<int>>& c, vector<int>& val) {
    ll ans = 0;
    for(int i = 0; i < n; i++){
        ans += solve_dfs(i, -1, val, c, 0, i);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> val(n);
    for(int i = 0; i < n; i++){
        cin >> val[i];
    }
    vector<vector<int>> c(n, vector<int>(0));
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u --;
        v --;
        c[u].push_back(v);
        c[v].push_back(u);
    }
    LCA lca(n, 0, c, val);
    CentroidDecomp cd;
    vector<int> cp = cd.calc_centroid_decomp(n, c);
    vector<vector<ll>> bits(n, vector<ll>(30, 0));  //for each bit, store how many are on
    vector<vector<ll>> bits_to_parent(n, vector<ll>(30, 0));    //how many bits did this node contribute to the parent?
    vector<ll> total(n, 0);     //total number of paths going into each node so far. 
    ll ans = 0;
    for(int i = n - 1; i >= 0; i--){
        int ptr = i;
        int psum = val[i];
        vector<ll> bits_over(30, 0);
        ll total_over = 0;
        //cout << "I : " << i << "\n";
        while(ptr != -1){
            
            //update bits
            {
                int tmp = psum;
                for(int j = 0; j < 30; j++){
                    bits[ptr][j] += tmp & 1;
                    //cout << bits[ptr][j] << " ";
                    tmp /= 2;
                }
                //cout << "\n";
                total[ptr] ++;
                //cout << "TOTAL : " << total[ptr] << "\n";
            }

            // cout << "PTR : " << ptr << " " << psum << " " << val[ptr] << "\n";
            // {
            //     for(int j = 0; j < 30; j++){
            //         cout << bits[ptr][j] << " ";
            //     }
            //     cout << "\n";
            // }

            // cout << "BITS OVER : " << "\n";
            // for(int j = 0; j < 30; j++){
            //     cout << bits_over[j] << " ";
            // }
            // cout << ": " << total_over << "\n";
            
            //update answer
            {
                int tmp = psum ^ val[ptr];
                ll bit_val = 1;
                ll cur_total = total[ptr] - total_over;
                for(int j = 0; j < 30; j++){
                    ll nr_bits = bits[ptr][j];
                    nr_bits -= bits_over[j];
                    if(tmp & 1){
                        nr_bits = cur_total - nr_bits;
                    }
                    // if(nr_bits != 0){
                    //     cout << "ADD : " << nr_bits * bit_val << " " << nr_bits << " " << bit_val << "\n";
                    // }
                    ans += nr_bits * bit_val;
                    tmp /= 2;
                    bit_val *= 2;
                }
            }
            if(cp[ptr] != -1){
                // //account for double counting paths
                // {
                //     for(int j = 0; j < 30; j++){
                //         bits_over[j] = bits[ptr][j];
                //     }
                //     total_over = total[ptr];
                //     //int nxor = lca.xor_dist(ptr, cp[ptr]) ^ val[ptr];
                //     int nxor = lca.xor_dist(i, ptr) ^ lca.xor_dist(i, cp[ptr]);
                //     cout << "NXOR : " << nxor << "\n";
                //     for(int j = 0; j < 30; j++){
                //         if(nxor & 1) {
                //             bits_over[j] = total_over - bits_over[j];
                //         }
                //         nxor /= 2;
                //     }
                //     // cout << "BITS OVER : " << "\n";
                //     // for(int j = 0; j < 30; j++){
                //     //     cout << bits_over[j] << " ";
                //     // }
                //     // cout << " : " << total_over << "\n";
                // }
                //cout << "XOR DIST : " << i << " " << cp[ptr] << " " << lca.xor_dist(i, cp[ptr]) << "\n";
                psum ^= lca.xor_dist(i, cp[ptr]) ^ lca.xor_dist(i, ptr);
                //upd bits to parent
                {
                    int tmp = psum;
                    for(int j = 0; j < 30; j++){
                        bits_to_parent[ptr][j] += tmp & 1;
                        tmp /= 2;
                    }
                }
                //account for double counting
                {
                    for(int j = 0; j < 30; j++){
                        bits_over[j] = bits_to_parent[ptr][j];
                    }
                    total_over = total[ptr];
                }
            }
            ptr = cp[ptr];
        }
    }
    cout << ans << "\n";

    //cout << "BRUTE FORCE : " << solve(n, c, val) << "\n";
    
    return 0;
}
