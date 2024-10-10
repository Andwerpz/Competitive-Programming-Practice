#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Kattis - chopwood

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    set<int> leaves;
    set<int> n_leaves;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        a[i] --;
        n_leaves.insert(a[i]);
    }
    for(int i = 0; i < n; i++){
        if(!n_leaves.count(i)) {
            // cout << "START LEAF : " << i << endl;
            leaves.insert(i);
        }
    }
    //find last occurence of each element in v
    vector<int> last_occ(n, -1);
    {
        map<int, int> m;
        for(int i = 0; i < n; i++){
            m[a[i]] ++;
        }
        for(int i = 0; i < n; i++){
            m[a[i]] --;
            if(m[a[i]] == 0){
                last_occ[i] = a[i];
            }
        }
    }
    // cout << "TESTING VALID" << endl;
    bool is_valid = true;
    vector<int> ans(0);
    for(int i = 0; i < n; i++){
        if(leaves.size() == 0){
            is_valid = false;
            break;
        }
        int n_leaf = *leaves.begin();
        leaves.erase(n_leaf);
        ans.push_back(n_leaf);
        // cout << "N LEAF : " << n_leaf << endl;
        if(last_occ[i] != -1){
            // cout << "LAST OCC: " << last_occ[i] << endl;
            leaves.insert(last_occ[i]);
        }
    }
    // cout << "DONE LOOP" << endl;
    if(!is_valid) {
        cout << "Error\n";
    }
    else {
        // cout << ans.size() << endl;
        for(int i = 0; i < n; i++){
            cout << ans[i] + 1 << "\n";
        }
    }
    
    return 0;
}
