#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Codeforces - 1936C

//the idea is to try to encode whatever we can do; upgrade an attribute, or use a pokemon to challenge, 
//into a graph, which we can then run dijkstra's algorithm to get the answer. 

//the immediate problem with this approach is that it requires way too many nodes to do; if we want 
//to keep track of a relationship between every pokemon, accounting for every attribute, that's 
//(n * m)^2 nodes, which is way too many. 

//the two observations that will help here is that 
//1. we only should use each pokemon once. 
//2. each attribute is relevant at most once. 

//the first observation is relatively obvious; if we get rid of a pokemon from the arena, there's no 
//point in putting it back. The second one is a little harder to see, but the idea is that it's never
//optimal to increase the same attribute on two seperate pokemon; you might as well just increase
//that attribute on one pokemon, double the amount. 

//ok, now we can build the graph. First, we'll have a node for each pokemon, the ith of which is denoted
//by Ni. We'll also have two sets of auxillary nodes, X and Y, each corresponding to one attribute of a
//specific pokemon; Xi_j corresponds to the jth attribute of the ith pokemon, Y is similar. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        vector<ll> cost(n);
        for(int i = 0; i < n; i++){
            cin >> cost[i];
        }
        //attr[i][j].first = ith attr of jth pokemon
        //attr[i][j].second = pokemon index
        vector<vector<pair<ll, ll>>> attr(m, vector<pair<ll, ll>>(n));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                cin >> attr[j][i].first;
                attr[j][i].second = i;
            }
        }
        //for each attribute, sort pokemon by power
        for(int i = 0; i < m; i++){
            sort(attr[i].begin(), attr[i].end());
        }
        //build graph
        int ptr = 0;
        vector<int> node(n);
        vector<vector<int>> x(m, vector<int>(n)), y(m, vector<int>(n));
        for(int i = 0; i < n; i++){
            node[i] = ptr ++;
        }
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                x[i][j] = ptr ++;
                y[i][j] = ptr ++;
            }
        }
        vector<vector<pair<int, ll>>> c(ptr, vector<pair<int, ll>>(0));
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                int poke_ind = attr[i][j].second;
                int n0 = node[poke_ind];
                int x0 = x[i][j];
                int y0 = y[i][j];
                //connect node to x
                c[n0].push_back({x0, cost[poke_ind]});
                //connect y to node
                c[y0].push_back({n0, 0});
                //connect x to x + 1
                if(j != n - 1) {
                    int attr0 = attr[i][j].first;
                    int attr1 = attr[i][j + 1].first;
                    int x1 = x[i][j + 1];
                    c[x0].push_back({x1, attr1 - attr0});
                }
                //connect y to y - 1
                if(j != 0){
                    int y1 = y[i][j - 1];
                    c[y0].push_back({y1, 0});
                }
                //connect x to y
                c[x0].push_back({y0, 0});
            }
        }
        //run dijkstra to find shortest path from node[n - 1] to node[0]
        vector<ll> d(ptr, 1e18);
        priority_queue<pair<ll, int>> q;    //{-dist, cur}
        q.push({0, node[n - 1]});
        while(q.size() != 0){
            int cur = q.top().second;
            ll dist = -q.top().first;
            q.pop();
            if(dist >= d[cur]) {
                continue;
            }
            d[cur] = dist;
            for(int i = 0; i < c[cur].size(); i++){
                int next = c[cur][i].first;
                ll n_dist = dist + c[cur][i].second;
                q.push({-n_dist, next});
            }
        }
        cout << d[node[0]] << "\n";
    }
    
    return 0;
}
