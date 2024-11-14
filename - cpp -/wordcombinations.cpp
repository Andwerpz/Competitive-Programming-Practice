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

//CSES - 1731

//dp + trie
//for each suffix, count the number of ways to build using dictionary. 

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    string s;
    cin >> s;
    Trie t;
    int k;
    cin >> k;
    for(int i = 0; i < k; i++){
        string a;
        cin >> a;
        t.insert(a);
    }    
    ll mod = 1e9 + 7;
    int n = s.size();
    vl dp(n + 1, 0);
    dp[n] = 1;
    for(int i = n - 1; i >= 0; i--){
        Trie::TrieNode* ptr = &t.head;
        for(int j = i; j < n; j++){
            if(ptr->c[s[j] - 'a'] == nullptr){
                break;
            }
            ptr = ptr->c[s[j] - 'a'];
            if(ptr->isWord) {
                dp[i] = (dp[i] + dp[j + 1]) % mod;
            }
        }
        // cout << dp[i] << "\n";
    }
    cout << dp[0] << "\n";
    
    return 0;
}