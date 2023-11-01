#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//CSES - 2134

struct HLD {
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

        LCA() {
            //do nothing. 
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

    struct SegtreeLazy {
        public:
            int n;
            int* t;    //stores product of range
            int* d;    //lazy tree
            bool* upd;   //upd[i] = true if t[i] needs to be updated
            int uneut, qneut;

            //single element modify
            function<int(int, int)> fmodify;

            //k element modify
            function<int(int, int, int)> fmodifyk;

            //product of two elements for query
            function<int(int, int)> fcombine;

            SegtreeLazy(int maxSize, int updateNeutral, int queryNeutral, function<int(int, int)> fmodify, function<int(int, int, int)> fmodifyk, function<int(int, int)> fcombine) {
                n = maxSize;
                uneut = updateNeutral;
                qneut = queryNeutral;

                this -> fmodify = fmodify;
                this -> fmodifyk = fmodifyk;
                this -> fcombine = fcombine;

                //raise n to nearest pow 2
                int x = 1;
                while(x < n) {
                    x <<= 1;
                }
                n = x;

                t = new int[n * 2];
                d = new int[n * 2];
                upd = new bool[n * 2];

                //make sure to initialize values
                for(int i = 0; i < n * 2; i++){
                    t[i] = uneut;
                }
                for(int i = 0; i < n * 2; i++){
                    d[i] = uneut;
                    upd[i] = false;
                }
            }

            SegtreeLazy() {
                //do nothing. 
            }

            void modify(int l, int r, int val) {    //modifies the range [l, r)
                _modify(l, r, val, 0, n, 1);
            }

            void modify(int ind, int val) { //modifies the range [ind, ind + 1)
                _modify(ind, ind + 1, val, 0, n, 1);
            }

            int query(int l, int r) {   //queries the range [l, r)
                return _query(l, r, 0, n, 1);
            }

            int query(int ind) {    //queries the range [ind, ind + 1)
                return _query(ind, ind + 1, 0, n, 1);
            }

        private:
            //calculates value of node based off of children
            //k is the amount of values that this node represents. 
            void combine(int ind, int k) {
                if(ind >= n){
                    return;
                }
                int l = ind * 2;
                int r = ind * 2 + 1;
                //make sure children are correct value before calculating
                push(l, k / 2);
                push(r, k / 2);
                t[ind] = fcombine(t[l], t[r]);
            }

            //registers a lazy change into this node
            void apply(int ind, int val) {
                upd[ind] = true;
                d[ind] = fmodify(d[ind], val);
            }

            //applies lazy change to this node
            //k is the amount of values that this node represents. 
            void push(int ind, int k) {
                if(!upd[ind]) {
                    return;
                }
                t[ind] = fmodifyk(t[ind], d[ind], k);
                if(ind < n) {
                    int l = ind * 2;
                    int r = ind * 2 + 1;
                    apply(l, d[ind]);
                    apply(r, d[ind]);
                }
                upd[ind] = false;
                d[ind] = uneut;
            }

            void _modify(int l, int r, int val, int tl, int tr, int ind) {
                if(l == r){
                    return;
                }
                if(upd[ind]){
                    push(ind, tr - tl);
                }
                if(l == tl && r == tr) {
                    apply(ind, val);
                    push(ind, tr - tl);
                    return;
                }
                int mid = tl + (tr - tl) / 2;
                if(l < mid) {
                    _modify(l, min(r, mid), val, tl, mid, ind * 2);
                }
                if(r > mid) {
                    _modify(max(l, mid), r, val, mid, tr, ind * 2 + 1);
                }
                combine(ind, tr - tl);
            }

            int _query(int l, int r, int tl, int tr, int ind) {
                if(l == r){
                    return qneut;
                }  
                if(upd[ind]) {
                    push(ind, tr - tl);
                }
                if(l == tl && r == tr){
                    return t[ind];
                }
                int mid = tl + (tr - tl) / 2;
                int lans = qneut;
                int rans = qneut;
                if(l < mid) {
                    lans = _query(l, min(r, mid), tl, mid, ind * 2);
                }
                if(r > mid) {
                    rans = _query(max(l, mid), r, mid, tr, ind * 2 + 1);
                }
                return fcombine(lans, rans);
            }
    };

    LCA lca;
    vector<vector<int>> edges;
    vector<bool> toParentHeavy;
    vector<bool> hasOutHeavy;
    vector<int> parent;
    vector<int> subtreeSize;

    SegtreeLazy segt;
    vector<int> segEndInd; //stores the index at which this heavy path ends. 
    vector<int> segParent; //what is the parent node of this heavy path?
    vector<int> segPos;    //stores the index of each node within the segment tree. 

    void calcSubtreeSize(int cur, int p = -1) {
        parent[cur] = p;
        subtreeSize[cur] = 1;
        for(int i = 0; i < edges[cur].size(); i++){
            int next = edges[cur][i];
            if(next == p){
                continue;
            }
            calcSubtreeSize(next, cur);
            subtreeSize[cur] += subtreeSize[next];
        }
    }

    void calcHLD(int cur, int p = -1) {
        for(int i = 0; i < edges[cur].size(); i++){
            int next = edges[cur][i];
            if(next == p){
                continue;
            }
            if(subtreeSize[next] > subtreeSize[cur] / 2) {
                hasOutHeavy[cur] = true;
                toParentHeavy[next] = true;
            }
            calcHLD(next, cur);
        }
    }

    HLD(int n, int root, vector<vector<int>> adjList) {
        this->lca = LCA(n, root, adjList);
        
        this->edges = adjList;
        this->parent = vector<int>(n, -1);
        this->subtreeSize = vector<int>(n, 0);
        this->toParentHeavy = vector<bool>(n, false);
        this->hasOutHeavy = vector<bool>(n, false);
        this->calcSubtreeSize(root);
        this->calcHLD(root);

        //create the segment tree needed to do the range updates. 
        //assignment modify, max query
        function<int(int, int)> fmodify = [](const int src, const int val) -> int{return val;};
        function<int(int, int, int)> fmodifyk = [](const int src, const int val, const int k) -> int{return val;};
        function<int(int, int)> fcombine = [](const int a, const int b) -> int{return max(a, b);};
        this->segt = SegtreeLazy(n, -1e9, -1e9, fmodify, fmodifyk, fcombine);
        this->segEndInd = vector<int>(n, -1);
        this->segParent = vector<int>(n, -1);
        this->segPos = vector<int>(n, -1);

        //find the positions of the nodes in the segment tree. 
        int posPtr = 0;
        for(int i = 0; i < n; i++){
            if(this->hasOutHeavy[i]) {
                //we want to have each heavy path be contiguous in the segment tree, so we want to start at the beginning. 
                continue;
            }
            int cur = i;
            vector<int> heavyPath(0);
            heavyPath.push_back(cur);
            this->segPos[cur] = posPtr ++;
            while(toParentHeavy[cur]) {
                cur = parent[cur];
                heavyPath.push_back(cur);
                this->segPos[cur] = posPtr ++;
            }
            cur = parent[cur];
            for(int j = 0; j < heavyPath.size(); j++){
                this->segEndInd[heavyPath[j]] = posPtr;
                this->segParent[heavyPath[j]] = cur;
            }
        }
    }

    void modify(int a, int b, int val) {
        int _lca = this->lca.lca(a, b);
        _modify(a, _lca, val);
        _modify(b, _lca, val);
        this->segt.modify(this->segPos[_lca], val);
    }

    void modify(int a, int val) {
        this->segt.modify(this->segPos[a], val);
    }

    int query(int a, int b) {
        int _lca = this->lca.lca(a, b);
        int ret = this->segt.qneut;
        ret = this->segt.fcombine(ret, _query(a, _lca));
        ret = this->segt.fcombine(ret, _query(b, _lca));
        ret = this->segt.fcombine(ret, this->segt.query(this->segPos[_lca]));
        return ret;
    }

    int query(int a) {
        return this->segt.query(this->segPos[a]);
    }

    private:
        void _modify(int a, int _lca, int val) {
            //while a and _lca aren't in the same heavy path
            while(this->segEndInd[a] != this->segEndInd[_lca]) {
                //modify until the end of the segment a belongs to. 
                this->segt.modify(this->segPos[a], this->segEndInd[a], val);
                a = this->segParent[a];
            }
            //a and _lca are in the same heavy path. Now, just modify the segment from a to _lca, not including _lca. 
            this->segt.modify(this->segPos[a], this->segPos[_lca], val);
        }

        int _query(int a, int _lca) {
            int ret = this->segt.qneut;
            while(this->segEndInd[a] != this->segEndInd[_lca]) {
                ret = this->segt.fcombine(ret, this->segt.query(this->segPos[a], this->segEndInd[a]));
                a = this->segParent[a];
            }
            ret = this->segt.fcombine(ret, this->segt.query(this->segPos[a], this->segPos[_lca]));
            return ret;
        }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    vector<int> val(n);
    for(int i = 0; i < n; i++){
        cin >> val[i];
    }
    vector<vector<int>> c(n, vector<int>(0));
    for(int i = 0; i < n - 1; i++){
        int a, b;
        cin >> a >> b;
        a --;
        b --;
        c[a].push_back(b);
        c[b].push_back(a);
    }
    HLD hld(n, 0, c);
    for(int i = 0; i < n; i++){
        hld.modify(i, val[i]);
    }
    for(int i = 0; i < q; i++){
        int t;
        cin >> t;
        if(t == 1){
            int s, x;
            cin >> s >> x;
            s --;
            hld.modify(s, x);
        }
        else {
            int a, b;
            cin >> a >> b;
            a --;
            b --;
            cout << hld.query(a, b) << " ";
        }
    }
    cout << "\n";
    
    return 0;
}
