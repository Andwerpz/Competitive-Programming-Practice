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

//AtCoder - AGC32B

//The problem asks us to construct a graph where the sum of adjacent node indices are the same for every node, 
//and the graph is simple and connected. This problem probably has a constructive solution, so let's build some 
//example graphs. 

//For n = 3, we can have edges (1, 3), (2, 3). 
//For n = 4, we can have edges (1, 2), (1, 3), (4, 2), (4, 3)

//The n = 4 case is rather interesting. We split the nodes into two groups of equal sum, and fully connect the 
//two groups with each other. This guarantees that the nodes are connected, and the sums are all the same. 

//I wonder if we can repeat this pattern with n = 5. For n = 5, the total sum is 15, so we can perhaps split into
//3 groups of 5. We can do this by splitting into groups 5, 1 and 4, 2 and 3. In fact, for any n >= 3, we can 
//easily do this. So our solution is split the nodes into a bunch of groups of equal sum, and then connect each 
//group's nodes to all other group's nodes. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    int tgt = (n % 2)? n : n + 1;
    vector<pii> e;
    for(int i = 1; i <= n; i++){
        for(int j = i + 1; j <= n; j++){
            if(i + j == tgt) continue;
            e.push_back({i, j});
        }
    }
    cout << e.size() << "\n";
    for(int i = 0; i < e.size(); i++){
        cout << e[i].first << " " << e[i].second << "\n";
    }
    
    return 0;
}