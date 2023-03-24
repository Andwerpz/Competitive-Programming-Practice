#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<ll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<vector<int>> c(n, vector<int>(0));
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        for(int j = 0; j < n; j++){
            if(s[j] == 'N'){
                continue;
            }
            c[i].push_back(j);
        }
    }
    vector<vector<ll>> sa(n, vector<ll>(n, 0));
    vector<vector<int>> dista(n, vector<int>(n, 0));
    vector<vector<bool>> va(n, vector<bool>(n, false));
    for(int i = 0; i < n; i++){
        //cout << "START : " << i << "\n";
        //brute force haha
        vector<ll> s(n, 0);
        vector<int> dist(n, 1000000000);
        vector<bool> v(n, false);
        s[i] = a[i];
        dist[i] = 0;
        queue<int> q;
        q.push(i);
        while(q.size() != 0){
            int cur = q.front();
            q.pop();
            if(v[cur]){
                continue;
            }
            v[cur] = true;
            //cout << "NEXT : " << cur << " " << s[cur] << "\n";
            for(int j = 0; j < c[cur].size(); j++){
                int next = c[cur][j];
                if(v[next] || dist[next] < dist[cur] + 1){ 
                    continue;
                }
                dist[next] = dist[cur] + 1;
                s[next] = max(s[next], s[cur] + a[next]);
                q.push(next);
            }
        }
        dista[i] = dist;
        sa[i] = s;
        va[i] = v;
    }
    int q;
    cin >> q;
    while(q-- > 0){
        int u, v;
        cin >> u >> v;
        u --;
        v --;
        if(!va[u][v]){
            cout << "IMPOSSIBLE\n";
            continue;
        }
        else {
            cout << dista[u][v] << " " << sa[u][v] << "\n";
            continue;
        }
    }
    
    return 0;
}
