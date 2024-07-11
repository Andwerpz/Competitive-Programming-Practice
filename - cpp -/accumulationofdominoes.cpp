#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1725A

//you can just place dominoes horizontally along the rows. 
//the one edge case is if each row is only 1 wide, which then you need to place dominoes vertically. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n, m;
    cin >> n >> m;
    cout << (m == 1? n - 1 : n * (m - 1)) << "\n";
    
    return 0;
}