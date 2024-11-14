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

//Alberta Collegiate Programming Contest 2024, Open Division - I

//for any group size <= 4, we can just brute force. 
//for groups sized > 4, since there are only 4 unique colors, they all must have the same colors. 

bool is_good(vector<vector<char>> c) {
    vector<set<char>> s(4);
    for(int i = 0; i < c.size(); i++){
        for(int j = 0; j < 4; j++){
            s[j].insert(c[i][j]);
        }
    }
    for(int i = 0; i < 4; i++){
        if(s[i].size() == c.size() || s[i].size() == 1){
            continue;
        }
        return false;
    }
    return true;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<vector<char>> a(n, vector<char>(4));
    map<vector<char>, int> m;
    int ans = 1;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 4; j++){
            cin >> a[i][j];
        }
        m[a[i]] ++;
    }
    //brute force all groups of size 4 or less
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            for(int k = j + 1; k < n; k++){
                for(int l = k + 1; l < n; l++){
                    if(is_good({a[i], a[j], a[k], a[l]})) {
                        ans = max(ans, 4);
                    }
                }
                if(is_good({a[i], a[j], a[k]})) {
                    ans = max(ans, 3);
                }
            }
            if(is_good({a[i], a[j]})) {
                ans = max(ans, 2);
            }
        }
    }
    //any group of size > 4 has to be all the same
    for(auto i = m.begin(); i != m.end(); i++){
        ans = max(ans, i->second);
    }
    cout << ans << "\n";
    
    return 0;
}