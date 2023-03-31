#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 09 D

//bfs, and count how many dominoes fall. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, m, l;
        cin >> n >> m >> l;
        vector<vector<int>> c(n, vector<int>(0));
        vector<bool> v(n, false);
        queue<int> s;
        for(int i = 0; i < m; i++){
            int a, b;
            cin >> a >> b;
            a --;
            b --;
            c[a].push_back(b);
        }
        for(int i = 0; i < l; i++){
            int a;
            cin >> a;
            a --;
            v[a] = true;
            s.push(a);
        }
        int ans = 0;
        while(s.size() != 0){
            ans ++;
            int cur = s.front();
            s.pop();
            for(int i = 0; i < c[cur].size(); i++){
                int next = c[cur][i];
                if(v[next]){
                    continue;
                }
                v[next] = true;
                s.push(next);
            }
        }
        ans = 0;
        for(int i = 0; i < n; i++){
            ans += v[i];
        }
        cout << ans << "\n";
    }
    
    return 0;
}
