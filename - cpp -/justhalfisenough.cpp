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

//UIUC IPL Team Tryout 2025 - H

//consider an arbitrary order. Let the number of edges that are satisfied be K. Then, if you reverse this
//arbitrary order, the amount of edges that are satisfied are now M - K. One of them have to be >= M / 2,
//so just pick the one that satisfies the most edges. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        int gcnt = 0, bcnt = 0;
        for(int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            if(u < v) gcnt ++;
            else bcnt ++;
        }
        // cout << "GCNT BCNT : " << gcnt << " " << bcnt << "\n";
        if(gcnt >= bcnt) {
            for(int i = 1; i <= n; i++) cout << i << " ";
            cout << "\n";
        }
        else {
            for(int i = n; i >= 1; i--) cout << i << " ";
            cout << "\n";
        }
    }
    
    return 0;
}