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

//HammerWars 2025 - B

//try adding the lines one by one and see how the number of regions changes
//observe that since no two lines are parallel and no three lines intersect at the same point, when you 
//add the ith line, the number of regions increases by exactly i. 

//from here, you just guess that the region graph is bipartite, and if there is an even amount of regions, 
//the number of red and blue regions is the same. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n;
    cin >> n;
    ll amt = n * (n + 1) / 2 + 1;
    cout << (amt % 2 ? "Arvind" : "Zhongtang") << "\n";
    
    return 0;
}