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

//Kattis - stopcounting

//you're able to claim some prefix and suffix of the array. Lets say that P, S are the averages of the 
//prefix and suffix respectively. Observe that if P > S, then we should just not take the suffix, and
//if S > P, we should not take the prefix. Therefore, there is no case where we would want to take both
//the prefix and suffix, as dropping the smaller average will always benefit us. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ld ans = 0;
    int n;
    cin >> n;
    vi a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    ld sum = 0;
    for(int i = 0; i < n; i++){
        sum += a[i];
        ans = max(ans, sum / (i + 1));
    }
    sum = 0;
    for(int i = n - 1; i >= 0; i--){
        sum += a[i];
        ans = max(ans, sum / (n - i));
    }
    cout << fixed << setprecision(10) << ans << "\n";
    
    return 0;
}