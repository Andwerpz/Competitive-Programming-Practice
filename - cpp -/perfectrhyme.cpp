#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef array<int, 2> pii;
typedef array<ll, 2> pll;
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

//SPOJ - PRHYME

//slightly annoying to implement trie problem. 

//to find the word with the longest shared suffix, we can use a trie storing words in the dictionary backwards. 
//however, we need to make sure that the word we get is not the same as the original word. This means for each node
//we have to store the smallest and second smallest string in the subtree. 

struct Trie {
    struct TrieNode {
        TrieNode* c[26];
        bool isWord = false;    //true if a word ends on this node
        int numWords = 0;   //counts how many words use this node as prefix
        int fmin = -1, smin = -1;
    };

    TrieNode head;

    Trie() {
        this->head = TrieNode();
    }

    void insert(string s, int dind){
        TrieNode* ptr = &head;
        for(int i = 0; i < s.size(); i++){
            if(ptr->fmin == -1) ptr->fmin = dind;
            else if(ptr->smin == -1) ptr->smin = dind;
            ptr->numWords ++;
            int ch = s[i] - 'a';
            if(ptr->c[ch] == nullptr) {
                ptr->c[ch] = new TrieNode();
            }
            ptr = ptr->c[ch];
        }
        ptr->numWords ++;
        ptr->isWord = true;
        if(ptr->fmin == -1) ptr->fmin = dind;
        else if(ptr->smin == -1) ptr->smin = dind;
    }

    TrieNode* query(string s, int badind) {
        TrieNode* ptr = &head;
        for(int i = 0; i < s.size(); i++){
            int ch = s[i] - 'a';
            if(ptr->c[ch] == nullptr || (ptr->c[ch]->fmin == badind && ptr->c[ch]->smin == -1)) break;
            ptr = ptr->c[ch];
        }
        return ptr;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    Trie t;
    vector<string> dict;
    while(true){
        string s;
        getline(cin, s);
        if(s.size() == 0) {
            break;
        }
        dict.push_back(s);
    }
    sort(dict.begin(), dict.end());
    for(int i = 0; i < dict.size(); i++){
        string s = dict[i];
        reverse(s.begin(), s.end());
        t.insert(s, i);
    }
    map<string, int> indmp;
    for(int i = 0; i < dict.size(); i++) indmp[dict[i]] = i;
    while(true) {
        string s, tmp;
        getline(cin, s);
        if(s.size() == 0){
            break;
        }
        tmp = s;
        reverse(tmp.begin(), tmp.end());
        Trie::TrieNode* ptr = t.query(tmp, indmp[s]);
        int ind = dict[ptr->fmin] == s? ptr->smin : ptr->fmin;
        cout << dict[ind] << "\n";
    }
    
    return 0;
}