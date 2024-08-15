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

//Codeforces - 1887B

//the entire trick is figuring out how to simulate the problem with good enough complexity. 

//something to notice is that we can probably apply dijkstra as we only care about the least amount of time
//travels to get to some city; arriving there later will only diminish our possibilities. 

//so, for each city, we'll keep a list of times where this city was mentioned in the edge list. Then for each moment
//in time, we'll use a set to find the next time we'll travel to it, and then look for all outgoing edges from this city. 

//this should run in n * log(n). 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, t;
    cin >> n >> t;
    vector<map<int, vi>> c(t);
    vector<set<int>> ment(n);
    for(int i = 0; i < t; i++){
        int m;
        cin >> m;
        for(int j = 0; j < m; j++){
            int u, v;
            cin >> u >> v;
            u --;
            v --;
            c[i][u].push_back(v);
            c[i][v].push_back(u);
            ment[u].insert(i);
            ment[v].insert(i);
        }
    }
    vector<set<int>> t_occ(t);
    int k;
    cin >> k;
    for(int i = 0; i < k; i++){
        int a;
        cin >> a;
        a --;
        t_occ[a].insert(i);
    }
    priority_queue<pii> q;
    vi d(n, 1e9);
    d[0] = 0;
    q.push({0, 0});
    //dijkstra
    while(q.size() != 0){
        int cur = q.top().second;
        int dist = -q.top().first;
        q.pop();
        if(d[cur] < dist) {
            continue;
        }
        //find what 'time moments' mention cur
        for(auto i = ment[cur].begin(); i != ment[cur].end(); i++){
            int time = *i;
            //what's the soonest occurrence of the next time moment after dist?
            if(t_occ[time].lower_bound(dist) == t_occ[time].end()) {
                continue;
            }
            int occ = *t_occ[time].lower_bound(dist) + 1;
            //loop through all edges
            for(int j = 0; j < c[time][cur].size(); j++){
                int next = c[time][cur][j];
                if(occ < d[next]) {
                    d[next] = occ;
                    q.push({-occ, next});
                }
            }
        }
    }
    cout << (d[n - 1] == 1e9? -1 : d[n - 1]) << "\n";
    
    return 0;
}