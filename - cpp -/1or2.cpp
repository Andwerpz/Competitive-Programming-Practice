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

//AtCoder - ARC121D

//big idea: consider simplified version of problem, then see how we can generalize to the full problem. 
// here, we prove an optimal solution given some restriction, and then guess that we can generalize to 
// the full problem. 

//Let's consider solving the problem with the restriction that we can only take 2 elements at a time. I claim
//that it's optimal to always match the largest with the smallest, second largest with second smallest, and so on. 

//Consider 4 elements A, B, C, D, with A <= B <= C <= D. Obviously choosing (A, B) and (C, D) is strictly worse, so we'll 
//consider the other option (A, C) and (B, D). Observe that max(A + C, B + D) >= max(A + D, B + C) because B + D >= A + D 
//and min(A + C, B + D) <= min(A + D, B + C) because A + C <= B + C, so this choice is also strictly worse. 

//How can we add back in choosing 1 element? Notice that choosing 1 element is equivalent to choosing some element and 0, and 
//adding 0s to the array should only make the answer strictly increase. Therefore, we can test adding between 0 and N 0s to the 
//array and solve with the 2 element restriction on each of these produced arrays. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vl a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    ll ans = 1e18;
    for(int i = 0; i <= n; i++){
        if((n + i) % 2) continue;
        vl tmp = a;
        for(int j = 0; j < i; j++){
            tmp.push_back(0);
        }
        sort(tmp.begin(), tmp.end());
        ll cmin = 1e18, cmax = -1e18;
        for(int j = 0; j < (n + i) / 2; j++) cmin = min(cmin, tmp[j] + tmp[tmp.size() - 1 - j]), cmax = max(cmax, tmp[j] + tmp[tmp.size() - 1 - j]);
        ans = min(ans, cmax - cmin);
    }
    cout << ans << "\n";
    
    return 0;
}