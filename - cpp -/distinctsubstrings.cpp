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

//CSES - 2105

//suffix automaton template check. 
//each node corresponds to a unique substring, but you also have to keep into account
//how many characters each edge represents. 

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

        bool contains_string(string s) {
            return count_occurrences(s);
        }

        //each leaf node corresponds to a suffix, so it suffices to see how many leaf nodes there
        //are in the subtree corresponding to s. 
        //runs in O(|s|) time. 
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

        //returns the start position of the earliest occurrence of s
        //runs in O(|s|) time.
        //tested on https://cses.fi/problemset/task/2104/
        int earliest_occ(string s){
            int i = 0;
            int ans = -1;
            SuffixNode* node = this->nodes[0];
            while(i != s.size()) {
                SuffixNode* child = node -> get_child(s[i]);
                if(child == nullptr) {
                    return -1;
                }
                node = child;
                for(int j = child -> l; j < min(child -> r, (int) this->chars.size()) && i < s.size(); j++){
                    if(this->chars[j] != s[i]) {
                        return -1;
                    }
                    i ++;
                    if(i == s.size()) {
                        ans = (j + 1) - s.size();
                    }
                }
            }
            return ans;
        }

        ll count_unique_substrings() {
            function<ll(SuffixNode*)> dfs = [&](SuffixNode* root) -> ll {
                ll l = root->l, r = root->r;
                r = min((ll) chars.size() - 1, r);   //get rid of terminator char
                ll ans = r - l;
                for(auto i = root->children.begin(); i != root->children.end(); i++){
                    ans += dfs(i->second);
                }
                return ans;
            };
            return dfs(nodes[0]);
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

    private:
        Segtree<int> lcp_rmq;

        vector<int> suf_arr;    //suffix array
        vector<int> suf_to_suf_ind; //maps suffix indices to their locations in the suffix array. 
        vector<int> leaf_cnt;   //number of leaves in subtree
        vector<int> lcp;    //longest common prefix between adjacent suffixes in suffix array. 

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    string s;
    cin >> s;
    SuffixTree st(s);
    cout << st.count_unique_substrings() << "\n";
    
    return 0;
}