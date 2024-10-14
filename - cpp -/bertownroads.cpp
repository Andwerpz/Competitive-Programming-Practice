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

//Codeforces - 118E

//take in a undirected graph, and determine whether or not it's possible to direct the edges such that the resulting
//directed graph is one big strongly connected component. 

//claim: if the original graph has no bridges, then it's always possible. 

//why? Consider the DFS tree of the graph. Direct the tree edges downwards, and the backedges upwards. If there are no
//bridges, then it should always be possible to travel from a node to one of its ancestors, so the two following should 
//hold:
//1. it's possible to get from the root to any node
//2. it's possible to get from any node to the root

//these two combined means that the entire graph is a SCC, and the problem is solved. 

//why is it impossible if there is a bridge? This one is kinda trivial if you think about it, but in context of the 
//DFS tree, it means that there exists a node for once you enter the subtree, it's impossible to exit. 

void calc_cd(int cur, int par, vvi& c, vi& vord, vi& min_vord, vvi& cd) {
    min_vord[cur] = vord[cur];
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(vord[next] == -1){
            cd[cur].push_back(next);
            vord[next] = vord[cur] + 1;
            calc_cd(next, cur, c, vord, min_vord, cd);
        }
        else if(vord[next] < vord[cur] && next != par) {
            cd[cur].push_back(next);
        }
    }
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == par){
            continue;
        }
        min_vord[cur] = min(min_vord[cur], min_vord[next]);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vvi c(n), cd(n);
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a --;
        b --;
        c[a].push_back(b);
        c[b].push_back(a);
    }
    vi vord(n, -1), min_vord(n, 1e9);
    vord[0] = 0;
    calc_cd(0, -1, c, vord, min_vord, cd);
    bool is_valid = true;
    for(int i = 1; i < n; i++){
        if(min_vord[i] >= vord[i]) {
            is_valid = false;
        }
    }
    if(!is_valid){
        cout << "0\n";
        return 0;
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < cd[i].size(); j++){
            cout << i + 1 << " " << cd[i][j] + 1 << "\n";
        }
    }
    
    return 0;
}