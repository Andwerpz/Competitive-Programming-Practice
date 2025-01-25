#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//for strings
struct Trie {
    struct TrieNode {
        TrieNode* c[26];
        bool isWord = false;    //true if a word ends on this node
        int numWords = 0;   //counts how many words use this node as prefix
    };

    TrieNode head;

    Trie() {
        this->head = TrieNode();
    }

    void insert(string s){
        TrieNode* ptr = &head;
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
        TrieNode* ptr = &head;
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

//can move this inside, just won't run locally. Seems like allocating memory on heap is way slower. 
static const int N = (1e5 + 100) * 30;
int trie_c[N][2], trie_subt[N];
struct TrieXOR {
    int nc = 1;

    TrieXOR() {
        clear();
    }

    void clear() {
        nc = 1;
        trie_c[0][0] = -1, trie_c[0][1] = -1;
        trie_subt[0] = 0;
    }

    int size() {
        return trie_subt[0];
    }

    void insert(int x) {
        int ptr = 0;
        trie_subt[0] ++;
        for(int i = 29; i >= 0; i--){   
            bool bit = x & (1 << i);
            if(trie_c[ptr][bit] == -1){
                trie_subt[nc] = 0;
                trie_c[nc][0] = -1, trie_c[nc][1] = -1;
                trie_c[ptr][bit] = nc;
                nc ++;
            }
            ptr = trie_c[ptr][bit], trie_subt[ptr] ++;
        }
    }

    int count(int x) {
        int ptr = 0;
        for(int i = 29; i >= 0; i--){
            bool bit = x & (1 << i);
            if(trie_c[ptr][bit] == -1)
                return 0;
            ptr = trie_c[ptr][bit];
        }
        return trie_subt[ptr];
    }

    void erase(int x) {
        if(count(x) == 0)
            return;
        int ptr = 0;
        trie_subt[0] --;
        for(int i = 29; i >= 0; i--){
            bool bit = x & (1 << i);
            ptr = trie_c[ptr][bit], trie_subt[ptr] --;
        }
    }

    //what's the maximum value of x ^ a, given that a is an element in the trie
    int query_max(int x) {
        if(size() == 0)
            return -1;
        int ans = 0, ptr = 0;
        for(int i = 29; i >= 0; i--){
            bool bit = x & (1 << i);
            if(trie_c[ptr][!bit] != -1 && trie_subt[trie_c[ptr][!bit]] != 0)
                ans += (1 << i), ptr = trie_c[ptr][!bit];
            else 
                ptr = trie_c[ptr][bit];
        }
        return ans;
    }

    int query_min(int x) {
        if(size() == 0)
            return -1;
        int ans = 0, ptr = 0;
        for(int i = 29; i >= 0; i--){
            bool bit = x & (1 << i);
            if(trie_c[ptr][bit] != -1 && trie_subt[trie_c[ptr][bit]] != 0)
                ptr = trie_c[ptr][bit];
            else
                ans += (1 << i), ptr = trie_c[ptr][!bit];
        }
        return ans;
    }
};