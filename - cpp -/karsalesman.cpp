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

//Codeforces - 2022B

//let the maximum element of the array be m. If m is greater than ceil(sum / x), then even if we sell a car
//from the maximum in every turn, m will be the last pile remaining, so the answer is m moves. 

//otherwise, the answer is always ceil(sum / x). 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll n, x;
        cin >> n >> x;
        vl a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        reverse(a.begin(), a.end());
        ll sum = 0;
        for(int i = 0; i < n; i++){
            sum += a[i];
        }
        if(a[0] > (sum + x - 1) / x) {
            cout << a[0] << "\n";
        }
        else {
            cout << (sum + x - 1) / x << "\n";
        }
    }
    
    return 0;
}