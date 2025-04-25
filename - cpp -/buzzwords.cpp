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

//Kattis - buzzwords

//just make a suffix trie and do bfs on it. 

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
            int ch = s[i] - 'A';
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
            int ch = s[i] - 'A';
            ptr = ptr->c[ch];
            if(ptr == nullptr) {
                break;
            }
        }
        return ptr;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    while(true) {
        string s;
        getline(cin, s);
        if(s == "") break;
        {
            string tmp = "";
            for(int i = 0; i < s.size(); i++){
                if(s[i] != ' ') tmp.push_back(s[i]);
            }
            s = tmp;
        }
        int n = s.size();
        Trie t;
        for(int i = 0; i < n; i++) t.insert(s.substr(i));
        vi ans(n + 1, 0);
        queue<pair<int, Trie::TrieNode*>> q;
        q.push({0, &(t.head)});
        while(q.size() != 0){
            int d = q.front().first;
            Trie::TrieNode* ptr = q.front().second;
            q.pop();
            ans[d] = max(ans[d], ptr->numWords);
            for(int i = 0; i < 26; i++) if(ptr->c[i] != nullptr) q.push({d + 1, ptr->c[i]});
        }
        for(int i = 1; i <= n; i++) {
            if(ans[i] <= 1) break;
            cout << ans[i] << "\n";
        }
        cout << "\n";
    }
    
    return 0;
}