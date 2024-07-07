#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef std::pair<int, int> pii;
typedef std::pair<ll, ll> pll;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1369E

//first, observe that we can convert this into a graph problem. The ith friend represents an undirected edge between nodes
//x[i] and y[i]. When we call in a friend to eat, we remove the edge, and decrement each of the connected nodes by 1. 
//Our goal is to remove all the edges in such a way that after removing each edge, at least one of the nodes affected is
//non-negative. 

//Let's call a node 'good' if the value of the node is greater than or equal to the number of edges indicent on that node. 
//First, observe that if there are no good nodes in the graph, then removing all the edges is impossible. We can prove this 
//by observing that after removing an edge, the number of good nodes in the graph does not change. And if somehow we managed
//to remove all but one edge, the last edge would always be impossible to remove as it would be connected to two not-good
//nodes. 

//If we do find a good node in the graph, then we can always just remove all edges that connect to it last, as the good
//node provides enough value to remove the edges regardless of the other nodes the edges are connected to. Removing the node 
//last effectively removes that node and all it's incident edges from the graph. We can keep trying to find good nodes
//until we either can't, in which case we're dead, or we remove all the edges from the graph. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<int> w(n);
    for(int i = 0; i < n; i++){
        cin >> w[i];
    }
    vector<int> indeg(n, 0);
    vector<vector<pair<int, int>>> c(n);
    for(int i = 0; i < m; i++){
        int x, y;
        cin >> x >> y;
        x --;
        y --;
        indeg[x] ++;
        indeg[y] ++;
        c[x].push_back({y, i});
        c[y].push_back({x, i});
    }
    stack<int> ans;
    queue<int> q;
    vector<int> v(n, false), ve(m, false);
    for(int i = 0; i < n; i++){
        if(w[i] >= indeg[i]) {
            q.push(i);
            v[i] = true;
        }
    }
    while(q.size() != 0){
        int cur = q.front();
        q.pop();
        for(int i = 0; i < c[cur].size(); i++){
            int next = c[cur][i].first;
            int ind = c[cur][i].second;
            if(!ve[ind]) {
                ve[ind] = true;
                ans.push(ind);
            }
            indeg[next] --;
            if(w[next] >= indeg[next] && !v[next]) {
                v[next] = true;
                q.push(next);
            }
        }
    }
    if(ans.size() != m){
        cout << "DEAD\n";
    }
    else {
        cout << "ALIVE\n";
        while(ans.size() != 0){
            cout << ans.top() + 1 << " ";
            ans.pop();
        }
        cout << "\n";
    }

    return 0;
}