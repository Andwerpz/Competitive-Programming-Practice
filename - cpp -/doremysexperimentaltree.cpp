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

//Codeforces - 1764F

//intuitively, f(i, j) is just the sum of distances for all other nodes to the path between i and j. 
//this means that if we hold i constant and vary j, with increasing path length comes decreasing value of f(i, j). 

//First, if we know that two nodes a and b are directly connected, we can compute the weight of the edge as 
//w = (f(a, a) + f(b, b) - 2 * f(a, b)) / n
//Now, we just need to figure out the structure of the tree, and we can just directly compute the edge weights after. 

//How to figure out the structure? Consider trying to find all nodes directly adjacent to node a. Since we know that 
//increased length will strictly decrease f, we know that the x with the value f(a, x) closest to f(a, a) is guaranteed
//to be adjacent to a. However, there might be multiple nodes that are directly adjacent to a. 

//We can simply sort the rest of the nodes by decreasing value of f(a, x). To test if a node is adjacent to a, just compare
//this node to the rest of the nodes we know are adjacent. For all nodes we know are adjacent, f(x, i) > f(x, y), where y is
//some adjacent node. This is because if x is adjacent, the path from x -> y should go through i and therefore be longer 
//than x -> i, and if x is not adjacent, there must be at least one node y s.t. the path x -> i goes through y. 

//Since the total amount of adjacent nodes is bounded by 2n, this should run in amortized O(n^2 * log(n)).

//the editorial claims that if we create a complete graph where the weight of edge (i, j) is f(i, j), then taking the MST
//will give us the tree structure. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vvl f(n, vl(n, -1));
    for(int i = 0; i < n; i++){
        for(int j = 0; j <= i; j++){
            cin >> f[i][j];
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            f[i][j] = f[j][i];
        }
    }
    for(int i = 0; i < n; i++){
        vector<pll> o(n);
        for(int j = 0; j < n; j++){
            o[j] = {f[i][j], j};
        }
        sort(o.begin(), o.end());
        reverse(o.begin(), o.end());
        vi adj;
        for(int j = 0; j < n; j++){
            int a = o[j].second;
            if(a == i) continue;
            bool is_adj = true;
            for(int x : adj){
                if(f[a][i] < f[a][x]) is_adj = false;
            }
            if(is_adj) {
                adj.push_back(a);
                if(a > i) {
                    ll w = (f[i][i] + f[a][a] - 2 * f[i][a]) / n;
                    cout << i + 1 << " " << a + 1 << " " << w << "\n";
                }
            }
        }
    }
    
    return 0;
}