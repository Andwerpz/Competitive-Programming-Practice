#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//CSES - 2102

//standard suffix tree problem. We can construct a suffix tree in O(n) time, and for each pattern 'p' we
//want to check is in the string, we only need O(|p|) time. 

struct SuffixTree {
    struct SuffixNode {
        //l, r: left and right boundaries [l, r) of the edge that leads to this node.   
        //parent: index of parent node
        //link: index of link node
        int l, r;
        SuffixNode* parent;
        SuffixNode* link;
        map<char, SuffixNode*> children;
        SuffixNode(int l = 0, int r = 0, SuffixNode* parent = nullptr) : l{l}, r{r}, parent{parent}, link{nullptr} {}
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

    vector<char> chars;
    vector<SuffixNode*> nodes;

    SuffixTree() {}

    SuffixTree(string s) {
        for(int i = 0; i < s.size(); i++){
            this->add_char(s[i]);
        }
    }

    //runs in amortized O(1) time
    void add_char(char c) {
        this -> chars.push_back(c);
        this -> tree_extend((int) this->chars.size() - 1);
    }

    //runs in O(|s|) time. 
    bool contains_string(string s) {
        int i = 0;
        SuffixNode* node = this->nodes[0];
        while(i != s.size()) {
            SuffixNode* child = node -> get_child(s[i]);
            if(child == nullptr) {
                return false;
            }
            node = child;
            for(int j = child -> l; j < min(child -> r, (int) this->chars.size()) && i < s.size(); j++){
                if(this->chars[j] != s[i]) {
                    return false;
                }
                i ++;
            }
        }
        return true;
    }

    private:
        struct SuffixState {
            SuffixNode* v;
            int pos;
            SuffixState(SuffixNode* v, int pos) : v{v}, pos{pos} {}
        };

        SuffixState ptr = SuffixState(nullptr, 0);

        void tree_extend(int pos) {
            if(pos == 0){
                nodes.push_back(new SuffixNode());
                ptr = SuffixState(nodes[0], 0);
            }
            while(true) {
                SuffixState nptr = go(ptr, pos, pos + 1);
                if(nptr.v != nullptr) {
                    ptr = nptr;
                    return;
                }

                SuffixNode* mid = split(ptr);
                SuffixNode* leaf = new SuffixNode(pos, 1e9, mid);
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
            SuffixNode* new_node = new SuffixNode(st.v -> l, st.v -> l + st.pos, par);
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
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        string next;
        cin >> next;
        cout << (suft.contains_string(next)? "YES" : "NO") << "\n";
    }
    
    return 0;
}
