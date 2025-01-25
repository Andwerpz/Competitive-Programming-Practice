#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef array<int, 2> pii;
typedef array<ll, 2> pll;
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

//Kattis - averageseasy, averageshard

//if a computer science student has iq less than average of the CS college, but greater than the 
//economics college, then he will trigger the funny moment. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    const ld epsilon = 1e-11;
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        ld aa = 0, ab = 0;
        vd a(n), b(m);
        for(int i = 0; i < n; i++) cin >> a[i];
        for(int i = 0; i < m; i++) cin >> b[i];
        for(int x : a) aa += x;
        for(int x : b) ab += x;
        aa /= n, ab /= m;
        int ans = 0;
        for(int x : a) if(aa - x > epsilon && x - ab > epsilon) ans ++;
        cout << ans << "\n";
    }
    
    return 0;
}