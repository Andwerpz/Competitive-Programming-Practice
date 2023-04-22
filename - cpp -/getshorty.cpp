#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 11 E

//just use dijkstra's 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    while(n != 0) {
        vector<vector<pair<int, ld>>> c(n, vector<pair<int, ld>>(0));
        for(int i = 0; i < m; i++){
            int a, b;
            cin >> a >> b;
            ld f;
            cin >> f;
            c[a].push_back({b, f});
            c[b].push_back({a, f});
        }
        priority_queue<pair<ld, int>> q;
        q.push({1.0, 0});
        vector<ld> maxSize(n, 0);
        maxSize[0] = 1;
        while(q.size() != 0){
            int cur = q.top().second;
            q.pop();
            ld size = maxSize[cur];
            //cout << "CUR : " << cur << " " << size << endl;
            for(int i = 0; i < c[cur].size(); i++){
                int next = c[cur][i].first;
                ld nextSize = size * c[cur][i].second;
                if(maxSize[next] + 1e-10 < nextSize) {
                    maxSize[next] = nextSize;
                    q.push({nextSize, next});
                }
            }
        }
        cout << fixed << setprecision(4) << maxSize[n - 1] << "\n";
        cin >> n >> m;
    }
    
    return 0;
}
