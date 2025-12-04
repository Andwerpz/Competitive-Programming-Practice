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

//Codeforces - 840A

//it's pretty apparent that the function value gets larger as n grows and k shrinks. 
//so why not just greedily combine the two? proof by AC.

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vi a(n), b(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];
    vi p(n, -1);
    vector<pii> ord(n);
    for(int i = 0; i < n; i++) ord[i] = {b[i], i};
    sort(ord.begin(), ord.end());
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    for(int i = 0; i < n; i++) p[ord[i].second] = a[i];
    for(int i = 0; i < n; i++) cout << p[i] << " ";
    cout << "\n";
    
    return 0;
}