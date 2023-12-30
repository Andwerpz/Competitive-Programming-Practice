#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ACPC 2023 Fall Contest F

//for each value in the first group, try to see if you can use that value for all groups. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<set<int>> a(n, set<int>());
    for(int i = 0; i < n; i++){
        int m;
        cin >> m;
        char sep;
        cin >> sep;
        for(int j = 0; j < m; j++){
            int next;
            cin >> next;
            a[i].insert(next);
        }
    }
    bool is_valid = false;
    for(auto i = a[0].begin(); i != a[0].end(); i++){
        int val = *i;
        bool cur_valid = true;
        for(int j = 1; j < n; j++){
            if(a[j].find(val) == a[j].end()) {
                cur_valid = false;
                break;
            }
        }
        if(cur_valid) {
            is_valid = true;
            break;
        }
    }
    cout << (is_valid? "YES" : "NO") << "\n";
    
    return 0;
}
