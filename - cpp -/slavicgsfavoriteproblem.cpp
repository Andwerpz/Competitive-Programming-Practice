#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1760G

//notice that if you don't use the jump, the x value at a given node cannot be changed by
//travelling along edges to different nodes. This is because i ^ i = 0.

//so, from node a, figure out all of the possible x values that you can get by travelling to nodes. 
//then, from each x value, you can jump to another node. The goal is to jump to a node where travelling to 
//b will make x = 0 when you reach b. This means that the xor sum from that node to b must equal x. 

void bfs(vector<int>& d, vector<vector<pair<int, int>>>& c, int start, int b) {
    int n = d.size();
    stack<int> s;
    vector<bool> v(n, false);
    v[start] = true;
    s.push(start);
    d[start] = 0;
    while(s.size() != 0){
        int cur = s.top();
        s.pop();
        if(cur == b){
            continue;
        }
        for(int i = 0; i < c[cur].size(); i++){
            int next = c[cur][i].first;
            int weight = c[cur][i].second;
            if(v[next]){
                continue;
            }
            v[next] = true;
            d[next] = d[cur] ^ weight;
            s.push(next);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, a, b;
        cin >> n >> a >> b;
        a --;
        b --;
        vector<vector<pair<int, int>>> c(n, vector<pair<int, int>>(0));
        for(int i = 0; i < n - 1; i++){
            int u, v, w;
            cin >> u >> v >> w;
            u --;
            v --;
            c[u].push_back({v, w});
            c[v].push_back({u, w});
        }
        vector<int> da(n, -1);
        vector<int> db(n, -1);
        bfs(da, c, a, b);
        bfs(db, c, b, -1);
        // for(int i = 0; i < n; i++){
        //     cout << da[i] << " " << db[i] << "\n";
        // }
        set<int> s;
        for(int i = 0; i < n; i++){
            if(i == b){
                continue;
            }
            if(da[i] == -1){
                continue;
            }
            s.insert(da[i]);
        }
        bool isValid = false;
        for(int i = 0; i < n; i++){
            if(i == b){
                continue;
            }
            if(s.find(db[i]) != s.end()) {
                isValid = true;
            }
        }
        if(da[b] == 0){
            isValid = true;
        }
        cout << (isValid? "YES\n" : "NO\n");
    }
    
    return 0;
}
