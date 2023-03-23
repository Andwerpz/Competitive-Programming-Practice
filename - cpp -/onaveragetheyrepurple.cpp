#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 08 C

//notice that the minimum amount of switches is equal to the length of the shortest path

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<vector<int>> c(n, vector<int>(0));
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        c[a].push_back(b);
        c[b].push_back(a);
    }
    vector<int> dist(n, 0);
    queue<int> s;
    vector<bool> v(n, false);
    v[0] = true;
    s.push(0);
    while(s.size() != 0){
        int cur = s.front();
        s.pop();
        for(int i = 0; i < c[cur].size(); i++){
            int next = c[cur][i];
            if(v[next]) {
                continue;
            }
            v[next] = true;
            dist[next] = dist[cur] + 1;
            s.push(next);
        }
    }
    cout << dist[n - 1] - 1 << "\n";
    
    return 0;
}
