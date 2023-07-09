#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1846G

//this is a graph problem. Each unique combination of symptoms are nodes (1 << n in total), and the medicines are directed edges from each node, with
//some cost, which is the number of days required to take the medicine. 

//we just want to find the shortest path from the start node to the node that represents no symptoms, or 0. 

//since all weights are positive (you don't go back in time by taking a medicine), we can use dijkstra. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        int start = 0;
        for(int i = 0; i < n; i++){
            char c;
            cin >> c;
            if(c == '1'){
                start += (1 << i);
            }
        }
        vector<vector<int>> a(m, vector<int>(3)); //days, cures, symptoms
        for(int i = 0; i < m; i++){
            cin >> a[i][0];
            for(int j = 0; j < n; j++){
                char c;
                cin >> c;
                if(c == '1'){
                    a[i][1] += (1 << j);
                }
            }
            for(int j = 0; j < n; j++){
                char c;
                cin >> c;
                if(c == '1'){
                    a[i][2] += (1 << j);
                }
            }
        }
        priority_queue<pair<int, int>> q;   //-distance, id
        vector<int> dist(1 << n, 1e9);
        q.push({0, start});
        while(q.size() != 0){
            int cur = q.top().second;
            int curd = -q.top().first;
            q.pop();
            if(curd >= dist[cur]) {
                continue;
            }
            dist[cur] = curd;
            for(int i = 0; i < m; i++){
                int next = cur;
                next -= (next & a[i][1]);
                next |= a[i][2];
                int nextd = min(dist[next], dist[cur] + a[i][0]);
                if(nextd < dist[next]) {
                    q.push({-nextd, next});
                }
            }
        }
        cout << (dist[0] == 1e9? -1 : dist[0]) << "\n";
    }
    
    return 0;
}
