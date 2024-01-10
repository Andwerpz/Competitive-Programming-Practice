#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1902F

//apparently HLD wasn't the intended solution, and the extra log(n) factor is causing the TLE
//intended solution has O((n + q)*B^2) time complexity, where B is the number of bits. 

int nr_basis_add = 0;
int nr_fcombine = 0;

bool basisAdd(int* b, int val, int start = 0) {
    nr_basis_add ++;
    for(int i = start; i < 20; i++){
        if((val & 1 << i) == 0){
            continue;
        }
        if(b[i] == -1){
            b[i] = val;
            return true;
        }
        val ^= b[i];
    }
    return false;
}

bool isRepresentable(int* b, int val) {
    for(int i = 0; i < 20; i++){
        if((val & 1 << i) == 0){
            continue;
        }
        if(b[i] == -1) {
            return false;
        }
        val ^= b[i];
    }
    return true;
}

struct seg{
    int basis[20];
    int nr_b = 0;
    seg(int val) {
        fill(basis, basis + 20, -1);
        nr_b += basisAdd(basis, val);
    }
    seg() {
        fill(basis, basis + 20, -1);
    }
};

template<typename T>
struct RMQ  {
    vector<T> elements;
    int n;
    static const int block_size = 30; // block size. adjust accordingly
    vector<int> mask;
    vector<int> sparse_table;
 
    //type of function the table is storing. Currently, it stores the minimum because it returns the minimum index 
    int op(int x, int y) { 
        return elements[x] < elements[y] ? x : y;
    }
 
    int least_significant_bit(int x) {
        return x & -x;
    }
    
    int most_significant_bit_index(int x) {
        return 31 - __builtin_clz(x);
    }
 
    // answers the smaller queries given size is <= b. elements[r-size+1..r] using masks
    int small_query(int r, int size = block_size) {
        //get only the 'size' least significant bits from the mask
        //with that, get the most significant set bit
        int dist_from_r = most_significant_bit_index(mask[r] & ((1<<size)-1));
        return r - dist_from_r;
    }
 
    RMQ() {} //need this to satisfy master goon's requirements
 
    //constructor
    RMQ (const vector<T>& input): elements(input), n(input.size()), mask(n), sparse_table(n) {
        //construct masks for all elements
        int curr_mask = 0;
        for(int i = 0; i < n; i++) {
            //shift mask by 1, keeping only the 'b' least significant bits
            curr_mask = (curr_mask<<1) & ((1<<block_size)-1);
            //while the current value is smaller than the value least significant bit of curr_mask
            //update that 0 into a 1. 
            while(curr_mask > 0 && op(i, i - most_significant_bit_index(least_significant_bit(curr_mask))) == i) {
                curr_mask ^= least_significant_bit(curr_mask);
            }
            //the least bit will always be minimum in that small bit
            curr_mask |= 1;
            mask[i] = curr_mask;
        }
        //construct sparse table for the n / b blocks
        //lower level
        for(int i = 0; i < n/block_size; i++) {
            sparse_table[i] = small_query(block_size * i + block_size - 1);
        }
        //rest of the levels
        for(int j = 1; (1<<j) <= n/block_size; j++) {
            for(int i = 0; i + (1<<j) <= n / block_size; i++) {
                sparse_table[n / block_size * j + i] = op(sparse_table[n / block_size * (j - 1) + i], sparse_table[n / block_size * (j - 1) + i + (1<<(j-1))]);
            }
        }
 
    }
 
    //query(l,r) returns the element from the minimum of v[l..r]
    //can be updated to return index by changing what we are returning
    T query(int l, int r) {
        //query size <= b
        if(r - l + 1 <= block_size) {
            return elements[small_query(r, r - l + 1)];
            // return small_query(r, r- l + 1);
        }
 
        //work out the small parts of the answer
        //it's ok for it to overlap and because size > b, we can freely let size of both sides be b
        int ans = op(small_query(l + block_size - 1), small_query(r)); 
 
        //blocks to query over
        int x = l / block_size + 1;
        int y = r / block_size - 1;
 
        if(x <= y) {
            int j = most_significant_bit_index(y - x + 1);
            ans = op(ans, op(sparse_table[n / block_size * j + x], sparse_table[n / block_size * j + y - (1 << j) + 1]));
        }
 
        return elements[ans];
        // return ans;
    }
 
    //alternative way to build if can't easily do with constructor or want to reuse
    void build (const vector<T>& input) {
        elements = input;
        n = input.size();
        mask.assign(n,0);
        sparse_table.assign(n,0);
        
        //construct masks for all elements
        int curr_mask = 0;
        for(int i = 0; i < n; i++) {
            //shift mask by 1, keeping only the 'b' least significant bits
            curr_mask = (curr_mask<<1) & ((1<<block_size)-1);
            //while the current value is smaller than the value least significant bit of curr_mask
            //update that 0 into a 1. 
            while(curr_mask > 0 && op(i, i - most_significant_bit_index(least_significant_bit(curr_mask))) == i) {
                curr_mask ^= least_significant_bit(curr_mask);
            }
            //the least bit will always be minimum in that small bit
            curr_mask |= 1;
            mask[i] = curr_mask;
        }
        //construct sparse table for the n / b blocks
        //lower level
        for(int i = 0; i < n/block_size; i++) {
            sparse_table[i] = small_query(block_size * i + block_size - 1);
        }
        //rest of the levels
        for(int j = 1; (1<<j) <= n/block_size; j++) {
            for(int i = 0; i + (1<<j) <= n / block_size; i++) {
                sparse_table[n / block_size * j + i] = op(sparse_table[n / block_size * (j - 1) + i], sparse_table[n / block_size * (j - 1) + i + (1<<(j-1))]);
            }
        }
 
    }
 
};
 
//reqs: edges is a valid tree rooted at 0. No cycles.
// template<typename T>
struct LCA {
 
    RMQ<int> rmq;
    vector<vector<int>> adj;
    vector<int> ids; //stores id of node at i
    vector<int> nodes; //stores node of id at i
    vector<int> euler;
    vector<int> euler_ids;
    int n;
 
    LCA() {} //default constructor
 
    //given vector where each node stores its parent
    LCA(const vector<int>& parents) {
        this->n = parents.size();
        adj.assign(n, {});
        for(int i = 1; i < n; i++) {
            adj[i].push_back(parents[i]);
            adj[parents[i]].push_back(i);
        }
        build();
    }    
 
    //given adjacency list. untested
    LCA(const vector<vector<int>> &input_adj) {
        this->n = input_adj.size();
        adj = input_adj;
        build();
    }
 
    void constructor(const vector<vector<int>> &input_adj) {
        this->n = input_adj.size();
        adj = input_adj;
        build();
    }
 
    void build() {
        euler_ids.assign(n,-1);
        nodes.assign(n,-1);
        ids.assign(n,-1);
        assign_ids();
        euler_tour(0,-1);
        rmq.build(euler);
    }
 
    //assigns id in a level traversal manner so rmq works
    void assign_ids() {
        queue<pair<int,int>> q; //curr, parent
        int id = 0;
        q.push({0,-1});
        while(q.size()) {
            pair<int,int> p = q.front();
            q.pop();
            ids[p.first] = id;
            nodes[id++] = p.first;
            for(auto x : adj[p.first]) {
                if(x != p.second) {
                    q.push({x,p.first});
                }
            }   
        }
 
    }   
 
    void euler_tour(int i, int p) {
        euler_ids[i] = euler.size();
        euler.push_back(ids[i]);
        for(auto x : adj[i]) {
            if(x != p) {
                euler_tour(x,i);
                euler.push_back(ids[i]);
            }
        }
    }
 
    //finds lca of node l and r [l,r]
    int lca(int l, int r) { //reverse order
        return nodes[rmq.query(min(euler_ids[l],euler_ids[r]), max(euler_ids[l],euler_ids[r]))];
    }
};

struct HLD {
    template <typename T>
    struct Segtree {
        //note that t[0] is not used
        int n;
        T* t;
        T uneut, qneut;

        //single element modification function
        function<T(T, T)> fmodify;

        //product of two elements for query and updating tree
        function<T(T, T)> fcombine;

        Segtree() {
            //do nothing
        }

        Segtree(int n, T updateNeutral, T queryNeutral, vector<T>& initVal, function<T(T, T)> fmodify, function<T(T, T)> fcombine) {
            this -> n = n;
            t = new T[2 * n];

            this -> fmodify = fmodify;
            this -> fcombine = fcombine;

            uneut = updateNeutral;
            qneut = queryNeutral;

            for(int i = 0; i < n; i++){
                if(i < initVal.size()) {
                    t[i + n] = initVal[i];
                }
                else {
                    t[i + n] = uneut;
                }
            }
            build();
        }

        void build() { // build the tree after manually assigning the values.
            for (int i = n - 1; i > 0; i--) {   
                t[i] = fcombine(t[i * 2], t[i * 2 + 1]);
            }
        }

        void modify(int p, T value) { // set value at position p
            p += n;
            t[p] = fmodify(t[p], value);
            for (p /= 2; p > 0; p /= 2) {
                t[p] = fcombine(t[p * 2], t[p * 2 + 1]);
            }
        }

        T query(int l, int r) { // sum on interval [l, r)
            T res = qneut;
            for (l += n, r += n; l < r; l /= 2, r /= 2) {
                if (l % 2 == 1) {
                    res = fcombine(res, t[l]);
                    l++;
                }
                if (r % 2 == 1) {
                    r--;
                    res = fcombine(t[r], res);
                }
            }
            return res;
        }

        T query(int ind) {
            return this->query(ind, ind + 1);
        }
    };

    LCA lca;
    vector<vector<int>> edges;
    bool *toParentHeavy, *hasOutHeavy;
    int *parent, *subtreeSize;

    Segtree<seg> segt;
    int *segEndInd, *segBeginInd, *segParent, *segPos;
    // segEndInd //stores the index at which this heavy path ends. 
    // segBeginInd // stores the index at which this heavy path begins. 
    // segParent //what is the parent node of this heavy path?
    // segPos    //stores the index of each node within the segment tree. 

    //caches the results to queries that entirely contain a segment. 
    //answer to a segment is stored at the beginning of the segment. 
    //TODO modify cache 
    seg *maxSegCache;   

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

    HLD(int n, int root, vector<vector<int>>& adjList, vector<seg>& initVal) {
        this->lca = LCA(adjList);
        
        this->edges = adjList;
        this->parent = new int[n];
        this->subtreeSize = new int[n];
        this->toParentHeavy = new bool[n];
        this->hasOutHeavy = new bool[n];
        fill(this->parent, this->parent + n, -1);
        fill(this->subtreeSize, this->subtreeSize + n, 0);
        fill(this->toParentHeavy, this->toParentHeavy + n, false);
        fill(this->hasOutHeavy, this->hasOutHeavy + n, false);
        this->calcSubtreeSize(root);
        this->calcHLD(root);

        //find the positions of the nodes in the segment tree. 
        this->segEndInd = new int[n];
        this->segBeginInd = new int[n];
        this->segParent = new int[n];
        this->segPos = new int[n];
        fill(this->segEndInd, this->segEndInd + n, -1);
        fill(this->segBeginInd, this->segBeginInd + n, -1);
        fill(this->segParent, this->segParent + n, -1);
        fill(this->segPos, this->segPos + n, -1);
        int posPtr = 0;
        for(int i = 0; i < n; i++){
            if(this->hasOutHeavy[i]) {
                //we want to have each heavy path be contiguous in the segment tree, so we want to start at the beginning. 
                continue;
            }
            int begin = posPtr;
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
                this->segBeginInd[heavyPath[j]] = begin;
                this->segEndInd[heavyPath[j]] = posPtr;
                this->segParent[heavyPath[j]] = cur;
            }
        }

        //create the actual initial values
        vector<seg> _initVal(n);
        for(int i = 0; i < n; i++){
            _initVal[this->segPos[i]] = initVal[i];
        }

        //create the segment tree needed to do the range updates. 
        //currently set to assignment modify, vector basis query
        function<seg(seg, seg)> fmodify = [](const seg src, const seg val) -> seg{
            return val;
        };
        function<seg(seg, seg)> fcombine = [](const seg a, const seg b) -> seg{
            if(a.nr_b == 20){
                return a;
            }
            if(b.nr_b == 20){
                return b;
            }
            nr_fcombine ++;
            seg next;
            for(int i = 0; i < 20; i++){
                next.basis[i] = a.basis[i];
            }
            next.nr_b = a.nr_b;
            for(int i = 19; i >= 0; i--){
                if(b.basis[i] != -1){
                    next.nr_b += basisAdd(next.basis, b.basis[i], i);
                }
            }
            return next;
        };
        this->segt = Segtree<seg>(n, {}, {}, _initVal, fmodify, fcombine);

        //cache segment query results
        this->maxSegCache = new seg[n];
        for(int i = 0; i < n; i++){
            if(this->segPos[i] == this->segBeginInd[i]) {
                int begin = this->segBeginInd[i];
                int end = this->segEndInd[i];
                this->maxSegCache[begin] = this->segt.query(begin, end);
            }
        }
    }

    // void modify(int a, int b, seg& val) {
    //     int _lca = this->lca.lca(a, b);
    //     _modify(a, _lca, val);
    //     _modify(b, _lca, val);
    //     this->segt.modify(this->segPos[_lca], val);
    // }

    void modify(int a, seg& val) {
        this->segt.modify(this->segPos[a], val);
    }

    seg query(int a, int b) {
        int _lca = this->lca.lca(a, b);
        seg ret = this->segt.qneut;
        ret = this->segt.fcombine(ret, _query(a, _lca));
        ret = this->segt.fcombine(ret, _query(b, _lca));
        ret = this->segt.fcombine(ret, this->segt.query(this->segPos[_lca]));
        return ret;
    }

    seg query(int a) {
        return this->segt.query(this->segPos[a]);
    }

    private:
        // void _modify(int a, int _lca, seg& val) {
        //     //while a and _lca aren't in the same heavy path
        //     while(this->segEndInd[a] != this->segEndInd[_lca]) {
        //         //modify until the end of the segment a belongs to. 
        //         this->segt.modify(this->segPos[a], this->segEndInd[a], val);
        //         a = this->segParent[a];
        //     }
        //     //a and _lca are in the same heavy path. Now, just modify the segment from a to _lca, not including _lca. 
        //     this->segt.modify(this->segPos[a], this->segPos[_lca], val);
        // }

        seg _query(int a, int _lca) {
            seg ret = this->segt.qneut;
            while(this->segEndInd[a] != this->segEndInd[_lca]) {
                //see if we can use the cache
                if(this->segBeginInd[a] == this->segPos[a]) {
                    //use the cache
                    ret = this->segt.fcombine(ret, this->maxSegCache[this->segBeginInd[a]]);
                }
                else {
                    ret = this->segt.fcombine(ret, this->segt.query(this->segPos[a], this->segEndInd[a]));
                }
                //ret = this->segt.fcombine(ret, this->segt.query(this->segPos[a], this->segEndInd[a]));
                a = this->segParent[a];
            }
            ret = this->segt.fcombine(ret, this->segt.query(this->segPos[a], this->segPos[_lca]));
            return ret;
        }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
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
    vector<seg> initVal(n);
    for(int i = 0; i < n; i++) {
        initVal[i] = {a[i]};
    }
    HLD hld(n, 0, c, initVal);
    // for(int i = 0; i < n; i++){
    //     int* basis = hld.query(i).basis;
    //     for(int j = 0; j < 20; j++){
    //         cout << basis[j] << " ";
    //     }
    //     cout << "\n";
    // }
    int q;
    cin >> q;
    while(q--){
        int x, y, k;
        cin >> x >> y >> k;
        x --;
        y --;
        int* basis = hld.query(x, y).basis;
        // for(int i = 0; i < 20; i++){
        //     cout << basis[i] << "\n";
        // }
        cout << (isRepresentable(basis, k)? "YES" : "NO") << "\n";
    }
    //cout << "NR BASIS ADD : " << nr_basis_add << "\n";
    //cout << "NR FCOMBINE : " << nr_fcombine << "\n";
    
    return 0;
}
