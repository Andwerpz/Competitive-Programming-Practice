#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//AtCoder - ARC159A

//this is a trick problem; the answer will be exactly the same if you find the shortest path from
//(s % n) to (t % n). 

//the one edge case is if (s % n) == (t % n). 

int solve(int s, int t, int n, vector<vector<bool>>& adj) {
    vector<bool> v(n, false);
    vector<int> d(n, -1);
    queue<int> q;
    for(int i = 0; i < n; i++){
        if(adj[s][i]) {
            v[i] = true;
            d[i] = 1;
            q.push(i);
        }
    }
    while(q.size()) {
        int cur = q.front();
        //cout << "CUR : " << cur << endl;
        q.pop();
        for(int i = 0; i < n; i++){
            if(!adj[cur][i]) {
                continue;
            }
            int next = i;
            if(v[next]) {
                continue;
            }
            v[next] = true;
            d[next] = d[cur] + 1;
            q.push(next);
        }
    }
    return d[t];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    vector<vector<bool>> adj(n, vector<bool>(n, false));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int next;
            cin >> next;
            adj[i][j] = next;
        }
    }
    int q;
    cin >> q;
    for(int i = 0; i < q; i++) {
        ll s, t;
        cin >> s >> t;
        s --;
        t --;
        s %= n;
        t %= n;
        cout << solve(s, t, n, adj) << "\n";
    }
    
    return 0;
}
