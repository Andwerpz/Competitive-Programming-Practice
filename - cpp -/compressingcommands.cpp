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

// BAPC 2023 - C

//this problem gives you a tree and asks you to pick a non-leaf node such that the sum of distances to all leaves
//is minimized. Once you build the tree, you can do the actual task in O(n)

struct node {
    int subt_cnt;
    bool is_file;
    map<string, node*> children;
    node() {
        subt_cnt = 0;
        is_file = false;
    }
};

node *root;

void add_file(vector<string>& parts, int pind, node *cur) {
    cur->subt_cnt ++;
    if(pind == parts.size()) {
        cur->is_file = true;
        return;
    }
    string part = parts[pind];
    // cout << "ADDING FILE : " << part << endl;
    if(cur->children.count(part) == 0) cur->children[part] = new node();
    add_file(parts, pind + 1, cur->children[part]);
}

ll solve(node *cur, ll cans, int n) {
    assert(!cur->is_file);
    ll ans = cans;
    for(auto i = cur->children.begin(); i != cur->children.end(); i++) {
        node *child = i->second;
        if(child->is_file) continue;
        ll nans = cans - child->subt_cnt + (n - child->subt_cnt);
        ans = min(ans, solve(child, nans, n));
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    root = new node();
    ll rans = 0;
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        vector<string> parts;
        for(int j = 0; j < s.size();) {
            assert(s[j] == '/');
            j ++;
            int r = j;
            while(r != s.size() && s[r] != '/') r ++;
            parts.push_back(s.substr(j, r - j));
            // cout << "PART : " << j << " " << r << " " << s.substr(j, r - j) << endl;
            j = r;
        }
        // cout << "DONE PARTS" << endl;
        add_file(parts, 0, root);
        rans += parts.size();
    }
    ll ans = solve(root, rans, n);
    cout << ans << "\n";
    
    return 0;
}