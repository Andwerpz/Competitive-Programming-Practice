#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

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
        
        vector<int> suf_arr;    //suffix array
        vector<int> leaf_cnt;   //number of leaves in subtree
        vector<int> lcp;    //longest common prefix between adjacent suffixes in suffix array. 

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

        //runs in amortized O(1) time
        void add_char(char c) {
            this -> chars.push_back(c);
            this -> tree_extend((int) this->chars.size() - 1);
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

    private:
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
        }

        struct SuffixState {
            SuffixNode* v;
            int pos;
            SuffixState(SuffixNode* v, int pos) : v{v}, pos{pos} {}
        };

        SuffixState ptr = SuffixState(nullptr, 0);

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    cin >> s;
    SuffixTree suft(s);
    queue<SuffixTree::SuffixNode*> q;
    q.push(suft.nodes[0]);
    while(q.size() != 0){
        SuffixTree::SuffixNode* cur = q.front();
        q.pop();
        cout << "LR : " << cur -> l << " " << cur -> r << "\n";
        for(auto i = cur -> children.begin(); i != cur -> children.end(); i++){
            q.push(i -> second);
        }
    }
    cout << "CONTAINS nana : " << suft.contains_string("nana") << "\n";
    cout << "SUF ARR : " << "\n";
    for(int i = 0; i < suft.suf_arr.size(); i++){
        cout << suft.suf_arr[i] << " ";
    }
    cout << "\n";
    cout << "LCP : " << "\n";
    for(int i = 0; i < suft.lcp.size(); i++){
        cout << suft.lcp[i] << " ";
    }
    cout << "\n";
    
    return 0;
}
