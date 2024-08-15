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

//Codeforces - 2004C

//note that optimal play just means taking the greatest element. We can sort the array in descending order, and
//observe that alice will take all even indexed elements, and bob will take all odd indexed elements. 

//To minimize the final score, we want to increase bob's elements such that they do not exceed alice's element, 
//because if they do, then we're just increasing alice's score. It's useful to note that the score of the
//game cannot go negative. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int t;
    cin >> t;
    while(t--){
        ll n, k;
        cin >> n >> k;
        vl a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        reverse(a.begin(), a.end());
        ll ans = 0;
        for(int i = 0; i + 1 < n; i += 2){
            ll diff = a[i] - a[i + 1];
            ll sub = min(diff, k);
            diff -= sub;
            k -= sub;
            ans += diff;
        }
        if(n % 2 == 1){
            ans += a[n - 1];
        }
        cout << ans << "\n";
    }
    
    return 0;
}