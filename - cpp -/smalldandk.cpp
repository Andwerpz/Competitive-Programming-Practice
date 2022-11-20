#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ACPC Week 6E

//since the maximum degree of any vertex is 3, and you only have to search at most to distance 3, 
//that means that you'll search maximum 3^3 or 27 nodes, 28 if you count the starting node. 

//so, the conclusion is just to do a brute force bfs for each query. 

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
    vector<int> v(n, -1);
    int q;
    cin >> q;
    while(q-- > 0){
        int x, k;
        cin >> x >> k;
        x --;
        int ans = 0;
        queue<pair<int, int>> s;
        s.push({x, 0});
        v[x] = q;
        while(s.size() != 0){
            int next = s.front().first;
            int dist = s.front().second;
            s.pop();
            ans += next + 1;
            if(dist == k) {
                continue;
            }
            for(int i : c[next]) {
                if(v[i] != q) {
                    v[i] = q;
                    s.push({i, dist + 1});
                }
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}