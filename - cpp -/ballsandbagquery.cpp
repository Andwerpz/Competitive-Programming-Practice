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

//AtCoder - ABC366C

//direct application of map

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int q;
    cin >> q;
    map<int, int> m;
    for(int i = 0; i < q; i++){
        int t;
        cin >> t;
        if(t == 1){
            int x;
            cin >> x;
            m[x] ++;
        }
        else if(t == 2){
            int x;
            cin >> x;
            m[x] --;
            if(m[x] == 0){
                m.erase(x);
            }
        }
        else {
            cout << m.size() << "\n";
        }
    }
    
    return 0;
}