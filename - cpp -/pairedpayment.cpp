
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

vector<int> cost;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> c(n, vector<pair<int, int>>());
    for(int i = 0; i < m; i++){
        int v, u, w;
        cin >> v >> u >> w;
        v --;
        u --;
        c[u].push_back({v, w});
        c[v].push_back({u, w});
    }
    cost = vector<int>(n, 1e9);
    auto compare = [](int a, int b) {return cost[a] == cost[b]? a < b : cost[a] < cost[b];};
    set<int, decltype(compare)> s(compare);
    cost[0] = 0;
    vector<bool> v(n, false);
    v[0] = true;
    vector<bool> vm(n, false);
    s.insert(0);
    while(s.size() != 0){
        int cur = *s.begin();
        int curCost = cost[cur];
        s.erase(cur);
        for(pair<int, int> p1 : c[cur]){
            int mid = p1.first;
            int midCost = p1.second;
            if(vm[mid]){
                continue;
            }
            vm[mid] = true;
            for(pair<int, int> p2 : c[mid]){
                int next = p2.first;
                int nextCost = p2.second;
                int updCost = curCost + (midCost + nextCost) * (midCost + nextCost);
                if(s.find(next) != s.end()){
                    s.erase(next);
                    cost[next] = min(updCost, cost[next]);
                    s.insert(next);
                }
                else{
                    cost[next] = min(updCost, cost[next]);
                }
                if(!v[next]){
                    v[next] = true;
                    s.insert(next);
                }
            }
        }
    }
    for(int i : cost){
        if(i == 1e9){
            cout << "-1 ";
        }
        else{
            cout << i << " ";
        }
    }
    cout << endl;
    
    return 0;
}
