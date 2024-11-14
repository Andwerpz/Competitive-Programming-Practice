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

//NCPC 2024 - H

//pretty much a template check. If you have a working implementation of suffix tree, then the problem is pretty much free.
//(not really free, but still). 

//Assume that you have a suffix trie, and don't care about complexity. The problem becomes pretty easy: each node in the
//trie represents a unique subarray (the path from the node to the root), and the number of times that subarray
//appears in the string is simply the amount of leaves in the subtree under the node.

//A suffix tree is just a compressed trie. Each edge can represent a substring, and the edges don't have to form a tree, 
//allowing for greater compression. But it's just a compressed trie, and the properties above still hold. 

template <typename T>
struct Segtree {
    //note that t[0] is not used
    int n;
    T* t;
    T uneut, qneut;
    function<T(T, T)> fmodify, fcombine;

    Segtree() {}
    Segtree(int n, T updateNeutral, T queryNeutral, function<T(T, T)> fm, function<T(T, T)> fc) {
        this->n = n;
        t = new T[2 * n];
        this->fmodify = fm;
        this->fcombine = fc;
        uneut = updateNeutral;
        qneut = queryNeutral;
        for(int i = 0; i < n; i++) t[i + n] = uneut;
        build();
    }

    void assign(vector<T>& arr) {
        for(int i = 0; i < min(n, (int) arr.size()); i++)
            t[i + n] = arr[i];
        build();
    }

	// build the tree after manually assigning the values.
    void build() { 
        for (int i = n - 1; i > 0; i--)
            t[i] = fcombine(t[i * 2], t[i * 2 + 1]);
    }

    void modify(int p, T value) { // set value at position p
        p += n;
        t[p] = fmodify(t[p], value);
        for (p /= 2; p > 0; p /= 2)
            t[p] = fcombine(t[p * 2], t[p * 2 + 1]);
    }

    T query(int l, int r) { // sum on interval [l, r)
        T l_res = qneut, r_res = qneut;
        bool l_none = true, r_none = true;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l % 2 == 1) {
                if(l_none) {l_none = false; l_res = t[l];}
                else l_res = fcombine(l_res, t[l]);
                l++;
            }
            if (r % 2 == 1) {
                r--;
                if(r_none) {r_none = false; r_res = t[r];}
                else r_res = fcombine(t[r], r_res);
            }
        }
        if(l_none) return r_res;
        if(r_none) return l_res;
        return fcombine(l_res, r_res);
    }

    T query(int ind) {
        return this->query(ind, ind + 1);
    }
};

struct SuffixTree {
    public:
        struct SuffixNode {
            //l, r: left and right boundaries [l, r) of the edge that leads to this node.   
            //parent: index of parent node
            //link: index of link node
            int index;
            int l, r;
            SuffixNode* parent;
            SuffixNode* link;
            map<char, SuffixNode*> children;
            SuffixNode(int index, int l = 0, int r = 0, SuffixNode* parent = nullptr) : index{index}, l{l}, r{r}, parent{parent}, link{nullptr} {}
            int len() {return r - l;}
            SuffixNode* get_child(char c) {
                if(children.find(c) == children.end()) {
                    return nullptr;
                }
                return children[c];
            }
            void set_child(char c, SuffixNode* ptr) {
                if(children.find(c) == children.end()) {
                    children.insert({c, ptr});
                }
                children[c] = ptr;
            }
        };
        
        int n;
        vector<char> chars;
        vector<SuffixNode*> nodes; 

        SuffixTree(string s) {
            //add terminator char
            s.push_back('$');

            //build tree
            this->n = s.size();
            for(int i = 0; i < s.size(); i++){
                this->add_char(s[i]);
            }

            //calculate useful information
            this->calc_leaf_cnt();
            this->calc_suf_arr();
            this->calc_lcp();
        }

        //runs in O(|s|) time. 
        bool contains_string(string s) {
            return count_occurrences(s);
        }

        //each leaf node corresponds to a suffix, so it suffices to see how many leaf nodes there
        //are in the subtree corresponding to s. 
        int count_occurrences(string s) {
            int i = 0;
            SuffixNode* node = this->nodes[0];
            while(i != s.size()) {
                SuffixNode* child = node -> get_child(s[i]);
                if(child == nullptr) {
                    return 0;
                }
                node = child;
                for(int j = child -> l; j < min(child -> r, (int) this->chars.size()) && i < s.size(); j++){
                    if(this->chars[j] != s[i]) {
                        return 0;
                    }
                    i ++;
                }
            }
            return this->leaf_cnt[node -> index];
        }
        
        vector<int> get_suffix_array() {
            return this->suf_arr;
        }

        int get_lcp(int a, int b) {
            if(a == b){
                return this->n - a - 1;
            }
            int a_ind = this->suf_to_suf_ind[a];
            int b_ind = this->suf_to_suf_ind[b];
            if(a_ind > b_ind) {
                swap(a_ind, b_ind);
            }
            return this->lcp_rmq.query(a_ind, b_ind);
        }

        vector<int> suf_arr;    //suffix array
        vector<int> suf_to_suf_ind; //maps suffix indices to their locations in the suffix array. 
        vector<int> leaf_cnt;   //number of leaves in subtree
        vector<int> lcp;    //longest common prefix between adjacent suffixes in suffix array. 

    private:
        Segtree<int> lcp_rmq;



        //uses kasai's algorithm to compute lcp array in O(n). 
        //lcp stands for longest common prefix.
        void calc_lcp() {
            int k = 0;
            int n = this->n;
            vector<int> lcp(n,0);
            vector<int> rank(n,0);
            for(int i = 0; i < n; i++) {
                rank[this->suf_arr[i]] = i;
            }
            for(int i = 0; i < n; i++, k? k-- : 0) {
                if(rank[i]==n-1) {
                    k = 0; 
                    continue;
                }
                int j = this->suf_arr[rank[i] + 1];
                while(i + k < n && j + k < n && this->chars[i + k] == this->chars[j + k]) {
                    k++;
                }
                lcp[rank[i]] = k;
            }
            this->lcp = lcp;
            //create lcp_rmq segtree
            function<int(int, int)> fmodify = [](const int src, const int val) -> int{return val;};
            function<int(int, int)> fcombine = [](const int a, const int b) -> int{return min(a, b);};
            this->lcp_rmq = Segtree<int>(n, 0, 1e9, fmodify, fcombine);
            for(int i = 0; i < n; i++){
                this->lcp_rmq.t[n + i] = lcp[i];
            }
            this->lcp_rmq.build();
        }

        void calc_leaf_cnt() {
            vector<int> ans(this->nodes.size(), 0);
            function<int(SuffixNode*)> dfs = [&ans, &dfs](SuffixNode* cur) -> int {
                int cnt = cur -> children.size() == 0;
                for(auto i = cur -> children.begin(); i != cur -> children.end(); i++){
                    cnt += dfs(i -> second);
                }
                ans[cur -> index] = cnt;
                return cnt;
            };
            dfs(this -> nodes[0]);
            this->leaf_cnt = ans;
        }

        //do greedy dfs on the tree. 
        //Ordering can be changed by switching the comparator in the ordered map in the node struct. 
        void calc_suf_arr() {
            vector<int> ans(this->chars.size(), 0);
            int ind = 0;
            int n = this -> n;
            function<void(SuffixNode*, int)> dfs = [&ans, &dfs, &ind, &n](SuffixNode* cur, int dist) -> void {
                dist += cur -> len();
                if(cur -> children.size() == 0){
                    ans[ind++] = n - dist;
                    return;
                }
                for(auto i = cur -> children.begin(); i != cur -> children.end(); i++){
                    dfs(i -> second, dist);
                }
            };
            dfs(this->nodes[0], 0);
            this->suf_arr = ans;
            //compute mapping from indices to suffix array
            this->suf_to_suf_ind = vector<int>(n, 0);
            for(int i = 0; i < n; i++){
                this->suf_to_suf_ind[this->suf_arr[i]] = i;
            }
        }

        struct SuffixState {
            SuffixNode* v;
            int pos;
            SuffixState(SuffixNode* v, int pos) : v{v}, pos{pos} {}
        };

        SuffixState ptr = SuffixState(nullptr, 0);

        //runs in amortized O(1) time
        void add_char(char c) {
            this->chars.push_back(c);
            this->tree_extend((int) this->chars.size() - 1);
        }

        void tree_extend(int pos) {
            if(pos == 0){
                nodes.push_back(new SuffixNode(0));
                ptr = SuffixState(nodes[0], 0);
            }
            while(true) {
                SuffixState nptr = go(ptr, pos, pos + 1);
                if(nptr.v != nullptr) {
                    ptr = nptr;
                    return;
                }

                SuffixNode* mid = split(ptr);
                SuffixNode* leaf = new SuffixNode(nodes.size(), pos, this -> n, mid);
                nodes.push_back(leaf);
                mid -> set_child(chars[pos], leaf);

                ptr.v = get_link(mid);
                ptr.pos = ptr.v -> len();
                if(mid == nodes[0]) {
                    break;
                }
            }
        }

        SuffixState go(SuffixState st, int l, int r) {
            while(l < r) {
                if(st.pos == st.v -> len()) {
                    st = SuffixState(st.v -> get_child(chars[l]), 0);
                    if(st.v == nullptr) {
                        return st;
                    }
                }
                else {
                    if(chars[st.v -> l + st.pos] != chars[l]) {
                        return SuffixState(nullptr, -1);
                    }
                    if(r - l < st.v -> len() - st.pos) {
                        return SuffixState(st.v, st.pos + r - l);
                    }
                    l += st.v -> len() - st.pos;
                    st.pos = st.v -> len();
                }
            }
            return st;
        }

        SuffixNode* split(SuffixState st) {
            if(st.pos == st.v -> len()) {
                return st.v;
            }
            if(st.pos == 0){
                return st.v -> parent;
            }
            SuffixNode* par = st.v -> parent;
            SuffixNode* new_node = new SuffixNode(nodes.size(), st.v -> l, st.v -> l + st.pos, par);
            nodes.push_back(new_node);
            par -> set_child(chars[st.v -> l], new_node);
            new_node -> set_child(chars[st.v -> l + st.pos], st.v);
            st.v -> parent = new_node;
            st.v -> l += st.pos;
            return new_node;
        }

        SuffixNode* get_link(SuffixNode* v) {
            if(v -> link != nullptr) {
                return v -> link;
            }
            if(v -> parent == nullptr) {
                return nodes[0];
            }
            SuffixNode* to = get_link(v -> parent);
            v -> link = split(go(SuffixState(to, to -> len()), v -> l + (v -> parent == nodes[0]), v -> r));
            return v -> link;
        }
};

ll dfs1(SuffixTree::SuffixNode* root, string& s, vl& seg) {
    int l = root->l;
    int r = root->r;
    if(l == s.size()) {
        //terminator char
        return 0;
    }
    r = min(r, (int) s.size());
    ll amt = 0;
    for(auto i = root->children.begin(); i != root->children.end(); i++){
        SuffixTree::SuffixNode* next = i->second;
        amt += dfs1(next, s, seg);
    }
    seg[l] += amt;
    seg[l + 1] -= amt;
    seg[r] -= amt;
    seg[r + 1] += amt;
    //innards
    seg[l] += r - l;
    seg[l + 1] -= r - l;
    seg[l + 1] -= 1;
    seg[r + 1] += 1;
    amt += r - l;
    // cout << "SUBST AMT : " << amt << " " << l << " " << r << "\n";
    return amt;
}

void dfs2(SuffixTree::SuffixNode* root, string& s, vi& leaf_cnt, map<int, ll>& df) {
    int l = root->l;
    int r = root->r;
    if(l == s.size()) {
        //terminator char
        return;
    }
    r = min(r, (int) s.size());
    for(auto i = root->children.begin(); i != root->children.end(); i++){
        SuffixTree::SuffixNode* next = i->second;
        dfs2(next, s, leaf_cnt, df);
    }
    if(r - l != 0){
        ll amt = leaf_cnt[root->index];
        df[amt] += r - l;
    }
    return;
}

void brute_sol(string& s){
    map<string, int> ss;
    int n = s.size();
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j <= n; j++){
            ss[s.substr(i, j - i)] ++;
        }
    }
    map<char, int> f;
    for(auto i = ss.begin(); i != ss.end(); i++){
        string cur = i->first;
        int amt = i->second;
        for(int j = 0; j < cur.size(); j++){
            f[cur[j]] ++;
        }
        while(amt != 0){
            int d = amt % 10;
            amt /= 10;
            f[d + '0'] ++;
        }
    }
    for(auto i = f.begin(); i != f.end(); i++){
        cout << i->first << " " << i->second << "\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    string s;
    cin >> s;
    int n = s.size();
    SuffixTree st(s);
    SuffixTree::SuffixNode* root = st.nodes[0];
    vl seg(n + 2, 0);
    map<int, ll> df;
    dfs1(root, s, seg);
    dfs2(root, s, st.leaf_cnt, df);
    for(int i = 1; i < seg.size(); i++){
        seg[i] += seg[i - 1];
    }
    map<char, ll> f;
    ll pfx = 0;
    for(int i = 0; i < n; i++){
        pfx += seg[i];
        f[s[i]] += pfx;
    }
    for(auto i = df.begin(); i != df.end(); i++){
        int x = i->first;
        ll amt = i->second;
        // cout << "X AMT : " << x << " " << amt << "\n";
        while(x != 0){
            int d = x % 10;
            x /= 10;
            f[d + '0'] += amt;
        }
    }
    for(auto i = f.begin(); i != f.end(); i++){
        cout << i->first << " " << i->second << "\n";
    }
    // for(int i = 0; i <= n; i++){
    //     cout << seg[i] << " ";
    // }
    // cout << "\n";
    // brute_sol(s);
    
    return 0;
}