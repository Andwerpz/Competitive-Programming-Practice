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

//Kattis - squarepegs

//first for each square or circular house, compute the minimum radius plot required to house it. 
//then, greedily assign the plots to houses, for each plot fit the biggest house you can into it. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ld epsilon = 1e-9;
    int n, m, k;
    cin >> n >> m >> k;
    vi r(n);
    for(int& x : r) cin >> x;
    vi a;   //for each house, what's the minimum radius it requires
    for(int i = 0; i < m; i++){
        int x;
        cin >> x;
        a.push_back(x + 1);
    }
    for(int i = 0; i < k; i++){
        ld x;
        cin >> x;
        ld diag = sqrt((x / 2) * (x / 2) + (x / 2) * (x / 2));
        a.push_back((int) (diag + 1.0 - epsilon));
    }
    sort(r.begin(), r.end());
    sort(a.begin(), a.end());
    // cout << "RA : " << "\n";
    // for(int x : r) cout << x << " ";
    // cout << "\n";
    // for(int x : a) cout << x << " ";
    // cout << "\n";
    int ans = 0;
    int aptr = a.size() - 1;
    for(int i = n - 1; i >= 0; i--){
        while(aptr != -1 && a[aptr] > r[i]) aptr --;
        if(aptr >= 0) {
            ans ++;
            aptr --;
        }
    }
    cout << ans << "\n";
    
    return 0;
}