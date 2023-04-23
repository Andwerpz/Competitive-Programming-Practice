#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 12 A

//basic trie problem

struct TrieNode {
    vector<TrieNode*> c = vector<TrieNode*>(26, nullptr);
    bool isWord = false;    //true if a word ends on this node
    int numWords = 0;   //counts how many words use this node as prefix
};

struct Trie {
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    Trie t;
    t.head = TrieNode();
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        TrieNode* node = t.query(s);
        if(node == nullptr) {
            cout << "0\n";
        }
        else {
            cout << node->numWords << "\n";
        }
        t.insert(s);
    }
    
    return 0;
}
