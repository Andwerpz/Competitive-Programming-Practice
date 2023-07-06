#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1847C

//notice that anyone summoned must have a strength equal to a subarray sum of the original array. 
//thus, the problem is just finding the maximum xor subarray sum in the array. 

//we can do this using a trie. 
//note that since the range on a[i] is so small, < 2^8, we can just do brute force checking. 

struct TrieNode {
    int val;
    TrieNode* child[2];

    TrieNode() {
        val = 0;
        child[0] = nullptr;
        child[1] = nullptr;
    }
};

struct Trie {
    TrieNode* root;

    Trie() {
        root = new TrieNode();
        this -> insert(0);
    }

    void insert(int val) {
        TrieNode* ptr = this->root;
        //cout << "INSERT : " << val << endl;
        for(int i = 31; i >= 0; i--){
            bool cur = val & (1 << i);
            //cout << cur << " ";
            if(ptr->child[cur] == nullptr) {
                ptr->child[cur] = new TrieNode();
            }
            ptr = ptr->child[cur];
        }
        //cout << endl;
        ptr->val = val;
    }

    int query(int val) {    //returns the maximum xor sum with val and anything inside the trie
        TrieNode* ptr = this->root;
        //cout << "QUERY : " << val << endl;
        for(int i = 31; i >= 0; i--){
            bool cur = val & (1 << i);
            //cout << cur << endl;
            if(ptr->child[1 - cur] != nullptr) {
                ptr = ptr->child[1 - cur];
            }
            else {
                ptr = ptr->child[cur];
            }
        }
        //cout << endl;
        return val ^ ptr->val;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        Trie t = Trie();
        int sum = 0;
        int ans = 0;
        for(int i = 0; i < n; i++) {
            sum ^= a[i];
            ans = max(ans, t.query(sum));
            t.insert(sum);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
