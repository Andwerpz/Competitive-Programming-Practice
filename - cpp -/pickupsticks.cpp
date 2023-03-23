#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 08 D

//topological sort

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<vector<int>> c(n, vector<int>(0));
    vector<int> p(n, 0);
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a --;
        b --;
        c[a].push_back(b);
        p[b] ++;
    }
    stack<int> s;
    for(int i = 0; i < n; i++){
        if(p[i] == 0){
            s.push(i);
        }
    }
    vector<int> ans(0);
    while(s.size() != 0){
        int cur = s.top();
        s.pop();
        ans.push_back(cur + 1);
        for(int i = 0; i < c[cur].size(); i++){
            int next = c[cur][i];
            p[next] --;
            if(p[next] == 0){
                s.push(next);
            }
        }
    }
    if(ans.size() == n){
        for(int i = 0; i < n; i++){
            cout << ans[i] << "\n";
        }
    }
    else {
        cout << "IMPOSSIBLE\n";
    }
    
    return 0;
}
