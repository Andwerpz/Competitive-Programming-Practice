#include <bits/stdc++.h>
typedef long long ll;
// typedef __int128 lll;
typedef long double ld;
// typedef __float128 lld;
using namespace std;

//Codeforces - 822E

//intuitively, one might think that this dp definition might work: 
//dp[max s pref][nr add segments][flag] = max t pref
//but depending on the transitions, you might get WA. 

//obviously, dp[max s pref][max t pref] = min seg cnt, should work (maybe plus a state for flags). 
//Transitions would be like:
//dp[i][j] -> dp[i + 1][j + 1] if the characters in s and t are equal
//dp[i][j] -> dp[i + 1][j] if we just want to skip the current character in s

//But that solution would TLE. To reduce complexity, we can swap t-pref with cnt to get the new dp state 
//dp[s-pref][cnt] = t-pref. We have to be careful with the transitions though. 
//dp[i][j] -> dp[i + 1][j] should be pretty straightforwards, we're just skipping the next element in s
//dp[i][j] -> dp[i + lcp][j + 1] is not obvious. lcp denotes the length of the longest common prefix between s and t
//at locations s[i] and t[dp[i][j]].

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

    Segtree() {}

    Segtree(int n, T updateNeutral, T queryNeutral, function<T(T, T)> fmodify, function<T(T, T)> fcombine) {
        this -> n = n;
        t = new T[2 * n];

        this -> fmodify = fmodify;
        this -> fcombine = fcombine;

        uneut = updateNeutral;
        qneut = queryNeutral;

        for(int i = 0; i < n; i++){
            t[i + n] = uneut;
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
        T l_res = qneut, r_res = qneut;
        bool l_none = true, r_none = true;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l % 2 == 1) {
                if(l_none) {
                    l_none = false;
                    l_res = t[l];
                }
                else {
                    l_res = fcombine(l_res, t[l]);
                }
                l++;
            }
            if (r % 2 == 1) {
                r--;
                if(r_none) {
                    r_none = false;
                    r_res = t[r];
                }
                else {
                    r_res = fcombine(t[r], r_res);
                }
            }
        }
        if(l_none) {
            return r_res;
        }
        if(r_none) {
            return l_res;
        }
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
    cin.tie(NULL);
    
    int n, m;
    string s, t;
    cin >> n >> s >> m >> t;
    int x;
    cin >> x;
    SuffixTree suft(s + "#" + t);
    vector dp(n + 1, vector(x + 1, -1));
    //base cases
    dp[0][0] = 0;
    //do dp
    for(int i = 0; i < n; i++){
        for(int j = 0; j <= x; j++){
            if(dp[i][j] == -1){
                continue;
            }
            //don't add
            dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
            //add
            if(j != x) {
                int lcp = suft.get_lcp(i, dp[i][j] + n + 1);
                dp[i + lcp][j + 1] = max(dp[i + lcp][j + 1], dp[i][j] + lcp);
            }
        }
    }
    bool is_valid = false;
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= x; j++){
            if(dp[i][j] == m){
                is_valid = true;
            }
        }
    }
    cout << (is_valid? "YES" : "NO") << "\n";
    
    return 0;
}
