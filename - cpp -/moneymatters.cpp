#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 08 H

//connected components check

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<ll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<vector<int>> c(n, vector<int>(0));
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        c[u].push_back(v);
        c[v].push_back(u);
    }
    bool isValid = true;
    vector<bool> v(n, false);
    for(int i = 0; i < n; i++){
        if(v[i]){
            continue;
        }
        ll sum = 0;
        v[i] = true;
        stack<int> s;
        s.push(i);
        while(s.size() != 0){
            int cur = s.top();
            s.pop();
            sum += a[cur];
            for(int j = 0; j < c[cur].size(); j++){
                int next = c[cur][j];
                if(v[next]){
                    continue;
                }
                v[next] = true;
                s.push(next);
            }
        }
        isValid &= sum == 0;
    }
    cout << (isValid? "POSSIBLE\n" : "IMPOSSIBLE\n");
    
    return 0;
}
