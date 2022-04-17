
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

vector<ll> cost;

//CSES 1671

//it's just dikjstra's algorithm.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, ll>>> c(n, vector<pair<int, ll>>());
    for(int i = 0; i < m; i++){
        int a, b, w;
        cin >> a >> b >> w;
        a --;
        b --;
        c[a].push_back({b, (ll) w});
    }
    cost = vector<ll>(n, (ll) 1e18);
    cost[0] = 0;
    auto compare = [] (pair<int, ll> a, pair<int, ll> b) {return a.second > b.second;};
    priority_queue<pair<int, ll>, vector<pair<int, ll>>, decltype(compare)> q(compare);
    q.push({0, 0});
    vector<bool> v(n);
    while(q.size() != 0) {
        int curNode = q.top().first;
        ll curCost = q.top().second;
        q.pop();
        if(v[curNode]){
            continue;
        }
        v[curNode] = true;
        for(auto [nNode, nCost] : c[curNode]){
            if(cost[nNode] > curCost + nCost){
                cost[nNode] = curCost + nCost;
                q.push({nNode, cost[nNode]});
            }
        }
    }
    //cout << endl;
    for(ll i : cost){
        cout << i << " ";
    }
    cout << endl;
    
    return 0;
}
