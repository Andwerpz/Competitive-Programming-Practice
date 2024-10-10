#include <bits/stdc++.h>
typedef long long ll;
// typedef __int128 lll;
typedef long double ld;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1174F

//we can use randomness to solve this problem. Apparently the intended solution was HLD or Centroid
//Decomposition. How tf is this a 2400?

//let's maintain a set of nodes that could be x, that is they are consistent with x for all of the 
//queries we've done so far. 

//then, we can do one of the two types of queries; d or s. 

//for type d query, choose a random node from the valid set, a. Then, eliminate all nodes from the valid 
//set that do not have the correct distance from a. 

//for type s query, find the lca of all the nodes in the valid set. Then, query for the next
//step towards x. Remove all nodes that do not have this next node as their parent. 
//keep in mind that if the lca of all the nodes happens to be a node in the valid set, we cannot
//do this query, as this node might be x, and we'll get WA. 

//we can just alternate between type d and s queries until the valid set shrinks to 1 element. 

void get_dist(int cur, int p, vector<vector<int>>& c, vector<int>& dist) {
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        dist[next] = dist[cur] + 1;
        get_dist(next, cur, c, dist);
    }
}

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

    //is a the parent of b
    bool is_parent(int a, int b) {
        return left_occ[a] <= left_occ[b] && right_occ[a] >= right_occ[b];
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    srand(time(0));
    int n;
    cin >> n;
    vector<vector<int>> c(n, vector<int>(0));
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u --;
        v --;
        c[u].push_back(v);
        c[v].push_back(u);
    }
    LCA lca(n, 0, c);
    vector<int> valid;
    for(int i = 0; i < n; i++){
        valid.push_back(i);
    }
    int qcnt = 0;
    while(qcnt != 36){
        //narrow thru distance
        if(qcnt != 36){
            qcnt ++;
            int cur = valid[rand() % valid.size()];
            vector<int> dist(n, 0);
            get_dist(cur, -1, c, dist);
            cout << "d " << cur + 1 << endl;
            int a_dist;
            cin >> a_dist;
            vector<int> n_valid(0);
            for(int j = 0; j < valid.size(); j++){
                if(dist[valid[j]] == a_dist) {
                    n_valid.push_back(valid[j]);
                }
            }
            valid = n_valid;
        }
        //narrow thru lca
        if(qcnt != 36){
            qcnt ++;
            if(valid.size() == 1){
                break;
            }
            int cur = valid[0];
            for(int j = 1; j < valid.size(); j++){
                cur = lca.lca(cur, valid[j]);
            }
            bool contains = false;
            for(int j = 0; j < valid.size(); j++){
                if(cur == valid[j]) {
                    contains = true;
                }
            }
            if(contains) {
                continue;
            }
            cout << "s " << cur + 1 << endl;
            int next;
            cin >> next;
            next --;
            vector<int> n_valid(0);
            for(int j = 0; j < valid.size(); j++){
                if(lca.is_parent(next, valid[j])) {
                    n_valid.push_back(valid[j]);
                }
            }
            valid = n_valid;
        }
    }
    cout << "! " << valid[0] + 1 << endl;
    
    return 0;
}
