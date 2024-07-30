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

//Codeforces - 1991E

//if the graph is not bipartite, then play as alice and always put out the same two colors. 

//if the graph is bipartite, then we can always win as bob. Note that if you can manage to color 
//1 'color' of the graph with a single color, then bob automatically wins, as he can just use the
//other two colors to color the other 'color'. 

//next, note that regardless of what alice does, we can always color one 'color' with a single color. 
//If alice puts out a 1, we color the 'red' portion, otherwise she must have put out a 2, so we use that 
//to color the 'blue' portion. When one portion finishes, we can safely color the remainder of the
//other portion with 1 or 2, and 3s. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        vvi c(n);
        for(int i = 0; i < m; i++){
            int u, v;
            cin >> u >> v;
            u --;
            v --;
            c[u].push_back(v);
            c[v].push_back(u);
        }
        bool bipartite = true;
        vi color(n, -1);
        set<int> ca, cb;
        queue<int> q;
        color[0] = 0;
        q.push(0);
        while(q.size() != 0){
            int cur = q.front();
            q.pop();
            // cout << "CUR : " << cur << endl;
            if(color[cur] == 0){
                ca.insert(cur);
            }
            else {
                cb.insert(cur);
            }
            for(int j = 0; j < c[cur].size(); j++){
                int next = c[cur][j];
                if(color[next] == -1){
                    color[next] = color[cur] == 0? 1 : 0;
                    q.push(next);
                }
                if(color[next] == color[cur]) {
                    bipartite = false;
                }
            }
        }
        if(!bipartite) {
            //play as alice
            cout << "Alice" << endl;
            for(int i = 0; i < n; i++){
                cout << "1 2" << endl;
                int foo, bar;
                cin >> foo >> bar;
            }
        }
        else {
            //play as bob
            cout << "Bob" << endl;
            for(int i = 0; i < n; i++){
                int a, b;
                cin >> a >> b;
                int vert, col;
                if(ca.size() != 0 && cb.size() != 0){
                    if(a == 1 || b == 1){
                        col = 1;
                        vert = *ca.begin();
                        ca.erase(vert);
                    }
                    else {
                        col = 2;
                        vert = *cb.begin();
                        cb.erase(vert);
                    }
                }
                else {
                    if(cb.size() == 0){
                        //choose 1 or 3
                        col = a == 1 || b == 1? 1 : 3;
                        vert = *ca.begin();
                        ca.erase(vert);
                    }
                    else {
                        col = a == 2 || b == 2? 2 : 3;
                        vert = *cb.begin();
                        cb.erase(vert);
                    }
                }
                cout << vert + 1 << " " << col << endl;
            }
        }
    }
    
    return 0;
}