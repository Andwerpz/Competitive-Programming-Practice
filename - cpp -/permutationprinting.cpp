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

//Codeforces - 1930B

//in the permutation, any value above n / 2 is not going to be able to divide any other value. So we can
//use these values to 'insulate' the other values which are less than n / 2. 

//for example, if n = 6, then
//1 6 2 5 3 4
//works. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vi ans(0);
        int l = 1;
        int r = n;
        for(int i = 0; i < n / 2; i++){
            ans.push_back(l ++);
            ans.push_back(r --);
        }
        if(n % 2 == 1){
            ans.push_back(l ++);
        }
        for(int i = 0; i < n; i++){
            cout << ans[i] << " \n"[i == n - 1];
        }
    }
    
    return 0;
}