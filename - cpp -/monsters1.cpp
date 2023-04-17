#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1810E

//you can start a bfs on each 0 weight node to see if you started there, you could defeat all the monsters. 

//to perform the bfs starting on a node, use a priority queue to travel to the minimum node that you could go to next. 

//note that if you visit a different 0 node from your starting node during your bfs, you shouldn't start at that node, since 
//this bfs will defeat all the monsters defeatable starting from the different 0 node. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, m;
        cin >> n >> m;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        vector<vector<int>> c(n, vector<int>());
        for(int i = 0; i < m; i++){
            int u, v;
            cin >> u >> v;
            u --;
            v --;
            c[u].push_back(v);
            c[v].push_back(u);
        }
        bool isValid = false;
        vector<int> v1(n, -1);
        for(int i = 0; i < n; i++){
            if(a[i] != 0){
                continue;
            }
            if(v1[i] != -1){
                continue;
            }
            //cout << "START : " << i << "\n";
            vector<bool> v(n, false);
            v[i] = true;
            priority_queue<pair<int, int>> s;
            s.push({0, i});
            int cnt = 0;
            while(s.size() != 0){
                int cur = s.top().second;
                s.pop();
                if(a[cur] > cnt) {
                    break;
                }
                cnt ++;
                v1[cur] = i;
                for(int j = 0; j < c[cur].size(); j++){
                    int next = c[cur][j];
                    if(v[next]) {
                        continue;
                    }
                    v[next] = true;
                    s.push({-a[next], next});
                }
            }
            if(cnt == n){
                isValid = true;
                break;
            }
        }
        cout << (isValid? "YES\n" : "NO\n");
    }
    
    return 0;
}
