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

//University of Alberta Programming Contest 2025 Open - K

//we want to minimize the sum of |D * x[i] - f[i]|. Observe that D * x[i] is some floating point number. 
//consider starting all f[i] = 0, and then slowly adding 1 to each f[i]. Now, we just need to greedily add to f[i]
//where the sum will decrease the most. 

//We can safely add 1 to f[i] if f[i] + 1 < D * x[i], however if f[i] + 1 > D * x[i], then we need to be careful. 
//We can add all such situations to a priority queue, and take the ones that will benefit us the most. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, d;
    cin >> n >> d;
    ld ans = d;
    int b = d;
    priority_queue<ld> q;
    for(int i = 0; i < n; i++){
        ld x;
        cin >> x;
        x = d * x;
        ld f = floor(x);
        ans -= f;
        q.push(x - f);
        b -= ((int) f);
        // cout << "X : " << x << " " << f << "\n";
    }
    int rem = b;
    for(int i = 0; q.size() != 0 && i < b; i++){
        ld val = q.top();
        q.pop();
        rem --;
        ans += 1.0 - 2.0 * val;
    }
    ans += rem;
    cout << fixed << setprecision(10) << ans << "\n";
    
    return 0;
}