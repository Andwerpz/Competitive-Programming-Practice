#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSES 1672

//somehow, we need to speed up caching distances from a to b. 

bool comp(pair<ll, ll> a, pair<ll, ll> b) {
    return a.second == b.second? a.first < b.first : a.second < b.second;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> c(n, vector<int>(n, -1));
    for(int i = 0; i < m; i++){
        int a, b, cost;
        cin >> a >> b >> cost;
        a --;
        b --;
        if(c[a][b] == -1){
            c[a][b] = cost;
        }
        if(c[b][a] == -1){
            c[b][a] = cost;
        }
        c[a][b] = min(c[a][b], cost);
        c[b][a] = min(c[b][a], cost);
    }
    vector<vector<ll>> dist(n, vector<ll>(n, -1));
    for(int i = 0; i < n; i++){
        dist[i][i] = 0;
        set<pair<ll, ll>, decltype(comp)*> s(comp);
        s.insert({i, 0});
        while(s.size() != 0){
            pair<ll, ll> next = *s.begin();
            s.erase(next);
            int cur = next.first;
            ll curDist = next.second;
            if(curDist != dist[i][cur]){
                continue;
            }
            for(int j = 0; j < n; j++){
                if(c[cur][j] == -1){
                    continue;
                }
                if(dist[i][j] == -1 || dist[i][j] >= curDist + c[cur][j]) {
                    s.insert({j, curDist + c[cur][j]});
                    dist[i][j] = curDist + c[cur][j];
                }
            }
        }
    }
    for(int i = 0; i < q; i++){
        int a, b;
        cin >> a >> b;
        a --;
        b --;
        cout << dist[a][b] << "\n";
    }
    
    return 0;
}
