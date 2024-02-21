#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC NAQ 2023 - J

struct TrieNode {
    int val = 0;
    map<int, TrieNode*> m;
    TrieNode() {}
};

void insert1(string s, TrieNode* root) {
    TrieNode* curr = root;
    for(char c : s) {
        if(curr->m.count(c) == 0) {
            curr->m[c] = new TrieNode();
        }  
        curr = curr->m[c];
        curr->val++;
    }
}

void insert2(string s, TrieNode* root) {
    TrieNode* curr = root;
    for(int i = 0; i < s.size(); i++) {
        int hash = (s[i] - 'a') * 26 + (s[s.size()-i-1] - 'a');
        if(curr->m.count(hash) == 0) {
            curr->m[hash] = new TrieNode();
        }
        curr = curr->m[hash];
        curr->val++;
    }
}

int query1(string s, TrieNode* root) {
    TrieNode* curr = root;
    for(char c : s) {
        if(curr->m.count(c)) {
            curr = curr->m[c];
        } else {
            return 0;
        }
    }
    return curr->val;
}

int query2(string s, string t, TrieNode* root) {
    reverse(t.begin(), t.end());
    TrieNode* curr = root;
    for(int i = 0; i < s.size(); i++) {
        int hash = (s[i] - 'a') * 26 + (t[i] - 'a');
        if(curr->m.count(hash)) {
            curr = curr->m[hash];
        } else {
            return 0;
        }
    }
    return curr->val;
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q; cin >> n >> q;
    TrieNode* rootp = new TrieNode();
    TrieNode* roots = new TrieNode();
    TrieNode* sp = new TrieNode();
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        insert1(s, rootp);
        insert2(s, sp);
        reverse(s.begin(), s.end());
        insert1(s,roots);
    }

    for(int i = 0; i < q; i++) {
        string a, b, c; cin >> a >> b >> c;
        int s = query1(b,rootp);
        int andd = query2(b,c, sp);
        reverse(c.begin(), c.end());
        int p = query1(c,roots);
        if(a == "AND") {
            cout << andd << '\n';
        } else if(a == "OR") {
            cout << p + s - andd << '\n';
        } else if(a == "XOR") {
            cout << p + s - andd * 2 << '\n';
        }
    }
    
    return 0;
}
