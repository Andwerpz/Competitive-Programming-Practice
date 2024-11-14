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

//COCI 2020 - Contest 3, Problem 2

//nice nim-like game problem with trie. 

struct Trie {
    struct TrieNode {
        TrieNode* c[26];
        bool isWord = false;    //true if a word ends on this node
        int numWords = 0;   //counts how many words use this node as prefix
    };

    TrieNode* root;

    Trie() {
        this->root = new TrieNode();
    }

    void insert(string s){
        TrieNode* ptr = root;
        for(int i = 0; i < s.size(); i++){
            ptr->numWords ++;
            int ch = s[i] - 'a';
            if(ptr->c[ch] == nullptr) {
                ptr->c[ch] = new TrieNode();
            }
            ptr = ptr->c[ch];
        }
        ptr->numWords ++;
        ptr->isWord = true;
    }

    TrieNode* query(string s) {
        TrieNode* ptr = root;
        for(int i = 0; i < s.size(); i++){
            int ch = s[i] - 'a';
            ptr = ptr->c[ch];
            if(ptr == nullptr) {
                break;
            }
        }
        return ptr;
    }
};

bool can_win(Trie::TrieNode* r1, Trie::TrieNode* r2) {
    //if r1 has something that r2 does not, then can win
    bool ans = false;
    for(int i = 0; i < 26; i++){
        if(r1->c[i] == nullptr){
            continue;
        }
        if(r2->c[i] == nullptr){
            ans = true;
        }
        ans = ans || (!can_win(r2->c[i], r1->c[i]));
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    Trie t1, t2;
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        t1.insert(s);
    }
    cin >> n;
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        t2.insert(s);
    }
    bool nina_win = can_win(t1.root, t2.root);
    cout << (nina_win? "Nina" : "Emilija") << "\n";
    
    return 0;
}