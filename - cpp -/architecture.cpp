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

//Kattis - architecture

//let a be the row maxes and b be the column maxes. 
//if max(a) != max(b), then it's always impossible. WLOG, max(a) > max(b). Then, there's no way for the max(a)
//row to be satisfied without unsatisfying one column in b. 

//otherwise, max(a) = max(b). In this case it's always possible. Just place the max building, and have all other 
//buildings 'hide' behind the max. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int r, c;
    cin >> r >> c;
    vi a(r), b(c);
    for(int& x : a) cin >> x;
    for(int& x : b) cin >> x;
    cout << (*max_element(a.begin(), a.end()) == *max_element(b.begin(), b.end())? "possible" : "impossible") << "\n";
    
    return 0;
}