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

//AtCoder - AGC5C

//The problem gives us a bunch of nodes with assigned distances, and asks us to create a tree such 
//that the maximum distance from each node to any other node is given by the assigned distance. 
//A well known fact about the longest distance from a node to any other node in the tree is that if
//you find the two nodes that make up the ends of the diameter of the tree, then the longest 
//distance must be to one of those two diameter endpoints. So we can probably start building our
//tree by first building the diameter path. 

//Once we have the diameter path, we can just hang the remaining nodes off of the diameter. A 
//remaining node is good if it has distance in range [(D + 1) / 2 + 1, D], where D is the diameter
//of the tree. To check whether it's possible, we just check whether the required distances are 
//available in the array. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vi a(n);
    for(int& x : a) cin >> x;
    vi f(n, 0);
    for(int x : a) f[x] ++;
    int maxd = -1, mind = 1e9;
    for(int x : a) maxd = max(maxd, x), mind = min(mind, x);
    bool ans = true;
    if((maxd + 1) / 2 != mind) ans = false;
    for(int i = maxd; i > mind; i--) f[i] -= 2;
    f[mind] --;
    if(maxd % 2) f[mind] --;
    for(int i = 0; i < n; i++) if (f[i] < 0 || (f[i] > 0 && i == mind)) ans = false;
    cout << (ans? "Possible" : "Impossible") << "\n";
    
    return 0;
}