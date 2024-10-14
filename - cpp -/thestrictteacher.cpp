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

//Codeforces - 2005 B1 B2

//The optimal strategy for the teachers is to simply walk directly at the student. 
//therefore, we can just figure out the gap betwee the two adjacent teachers, and split the 
//difference.

//edge case is when you are on the edge (literally). 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m, q;
        cin >> n >> m >> q;
        set<int> s;
        for(int i = 0; i < m; i++){
            int a;
            cin >> a;
            s.insert(a);
        }
        for(int i = 0; i < q; i++){
            int x;
            cin >> x;
            int ans = -1;
            if(x < *s.begin()) {
                ans = *s.begin() - 1;
            }
            else if(x > *s.rbegin()) {
                ans = n - *s.rbegin();
            }
            else {
                auto ptr = s.lower_bound(x);
                int r = *ptr;
                ptr --;
                int l = *ptr;
                int diff = r - l - 1;
                // cout << "DIFF : " << diff << "\n";
                ans = (diff + 1) / 2;
            }
            cout << ans << "\n";
        }
    }
    
    return 0;
}