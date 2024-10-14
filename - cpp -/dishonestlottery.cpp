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

//2024 ICPC NAQ - E

//implementation

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    map<int, int> m;
    for(int i = 0; i < 10 * n; i++){
        for(int j = 0; j < 5; j++){
            int x;
            cin >> x;
            m[x] ++;
        }
    }
    vi ans(0);
    for(auto i = m.begin(); i != m.end(); i++){
        if(i->second > 2 * n) {
            ans.push_back(i->first);
        }
    }
    sort(ans.begin(), ans.end());
    if(ans.size() == 0){
        cout << "-1\n";
        return 0;
    }
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] << " ";
    }
    cout << "\n";
    
    return 0;
}