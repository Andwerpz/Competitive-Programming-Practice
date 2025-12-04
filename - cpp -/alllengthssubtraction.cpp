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

//Codeforces - 2143A

//observe that removing the largest element has forced position. 
//then since there has to be exactly one '1' in the array, removing the second largest element is also forced. 
//this keeps going. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vi p(n);
        for(int i = 0; i < n; i++) cin >> p[i];
        int l = 0, r = n - 1;
        bool is_valid = true;
        for(int i = 0; i < n; i++) {
            if(p[l] == i + 1) l ++;
            else if(p[r] == i + 1) r --;
            else {
                is_valid = false;
                break;
            }
        }
        cout << (is_valid? "YES" : "NO") << "\n";
    }
    
    return 0;
}