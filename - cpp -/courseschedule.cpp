#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSES - 1679

//classic topological sort problem. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<int> in(n, 0);
    vector<vector<int>> c(n, vector<int>(0));
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a --;
        b --;
        in[b] ++;
        c[a].push_back(b);
    }
    vector<int> ans(0);
    stack<int> s;
    for(int i = 0; i < n; i++){
        if(!in[i]) {
            s.push(i);
        }
    }
    while(s.size() != 0){
        int cur = s.top();
        s.pop();
        ans.push_back(cur);
        for(int i = 0; i < c[cur].size(); i++){
            int next = c[cur][i];
            in[next] --;
            if(!in[next]) {
                s.push(next);
            }
        }
    }
    if(ans.size() != n) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    for(int i = 0; i < n; i++){
        cout << ans[i] + 1 << " \n"[i == n - 1];
    }
    
    return 0;
}
