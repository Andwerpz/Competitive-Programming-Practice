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

//University of Alberta Programming Contest 2025 Open - G

//slight geo + sorting

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<pair<ld, string>> a;
    for(int i = 0; i < n; i++){
        ld x, y, m;
        cin >> x >> y >> m;
        string s;
        cin >> s;
        if(m == 0) continue;
        if((m > 0) ^ (y < 0)) continue;
        //mx + y = 0
        //x = -y / m
        a.push_back({x - y / m, s});
    }
    sort(a.begin(), a.end());
    for(int i = 0; i < a.size(); i++) cout << a[i].second << "\n";
    
    return 0;
}