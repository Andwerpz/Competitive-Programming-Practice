#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

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