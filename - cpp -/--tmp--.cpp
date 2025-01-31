#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

struct TrieNode {
    int cnt;
    string small;
    TrieNode* c[26];
    TrieNode() {
        cnt = 0;
        small = "";
        for(int i = 0; i < 26; i++) {
            c[i] = nullptr;
        }
    }
};

void insert(string s, TrieNode* root) {
    assert(s.size());
    TrieNode* curr = root;
    curr->cnt++;
    if(curr->small == "" || s < curr->small) {
        curr->small = s;
    }
    for(int i = s.size() - 1; i >= 0; i--) {
        if(curr->c[s[i] - 'a'] == nullptr) {
            curr->c[s[i] - 'a'] = new TrieNode();
            curr->c[s[i] - 'a']->small = s;
        }
        curr = curr->c[s[i] - 'a'];
        curr->cnt++;
        assert(curr->small != "");
        curr->small = min(curr->small, s);
    }
}

string query(string s, TrieNode* root) {
    TrieNode* curr = root;
    for(int i = s.size() - 1; i >= 0; i--) { //iterate over characters in suffix
        if(curr->c[s[i] - 'a'] != nullptr && (curr->c[s[i] - 'a']->cnt > 1  || curr->c[s[i] - 'a']->small != s)) { //see if there exists a child with the next matching character that is not equal to the current word. 
            curr = curr->c[s[i] - 'a'];
        } else { //no further rhyming children
            break;
        }
    }

    if(curr->small != s) return curr->small;

    string res = "";
    for(int j = 0; j < 26; j++) {
        if(curr->c[j] != nullptr && curr->c[j]->small != s) {
            if(res == "" || curr->c[j]->small < res) {
                res = curr->c[j]->small;
            }
        }
    }
    assert(res != "");
    return res;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    TrieNode* root = new TrieNode();
    string s;

    set<string> vis;

    getline(cin, s);
    while(s != "") {
        if(vis.count(s) == 0) {
            insert(s,root);
        }
        vis.insert(s);
        getline(cin,s);
    }

    while(getline(cin,s)) {
        if(s.size() == 0) break;
        cout << query(s, root) << '\n';
    }

    return 0;
}

/*
a
b
aa
ab
ba
bb
aaa
aab
aba
abb
baa
bab
bba
bbb

a
b
aa
ab
ba
bb
aaa
aab
aba
abb
baa
bab
bba
bbb
aaaa
aaab
aaba
aabb
abaa
abab
abba
abbb
baaa
baab
baba
babb
bbaa
bbab
bbba
bbbb

*/