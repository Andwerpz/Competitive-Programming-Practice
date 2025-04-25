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

//UTPC Contest 03-22-24 Div. 1 - J

//bitset cheese or intended? ok, it's bitset cheese, but their intended solution isn't much better, using an unproved
//complexity. 

//suppose we maintain a 'connectivity matrix' where c[i][j] = true iff j is reachable from i. Then, we can answer some query
//(u, v) in O(1) time by just checking if c[v][u] = true. However, we also need to add the edge, and this will change the 
//connectivity. 

//actually, it won't change the connectivity *that* much. node u will be able to visit everything that node v can visit, 
//and every node that can visit node u can then visit whatever node u can newly visit. However, performing these updates can 
//take up to O(n^2) time, so we probably need a faster way right?

//actually, bitsets are perfect here. If c[i] is a bitset representing all the nodes node i can visit, and we want to update
//c[j] with c[i], we can just do c[j] |= c[i]. So now we have O(q * n^2 / 64), which is definitely fast enough. 

//one more thing: how do we actually initially build c? There's a way to do it in O(n^2) using scc's and topological sort, but
//that's a pain to implement. The naive all-source dfs solution takes O(n^3) and isn't bitset compatible. Instead, we can do 
//this: we'll iterate through all the nodes, and for each edge check all the nodes it can go to. Suppose c[i][j] = true. Then, 
//assign c[i] |= c[j]. How many times do we need to iterate through all the nodes until nothing changes? Actually, around 
//log_2(N) times. This is because after every iteration, the 'range' of c[i] doubles. 

//So the final complexity is O(n^3 * log_2(N) / 64)

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m, q;
    cin >> n >> m >> q;
    vector<bitset<1000>> c(n);
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        u --, v --;
        c[u][v] = true;
    }
    //init c
    for(int i = 0; i < 11; i++){
        for(int j = 0; j < n; j++) for(int k = 0; k < n; k++) {
            if(c[j][k]) c[j] |= c[k];
        }
    }
    //handle queries
    while(q--){
        int u, v;
        cin >> u >> v;
        u --, v --;
        cout << (c[v][u]? "YES" : "NO") << "\n";
        c[u][v] = true;
        c[u] |= c[v];
        for(int i = 0; i < n; i++) if(i != u && c[i][u]) c[i] |= c[u];
    }
    
    return 0;
}