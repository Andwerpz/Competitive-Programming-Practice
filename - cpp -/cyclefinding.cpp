#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSES - 1197

//use the bellman ford algorithm to find the cycle. 

//keep track of for each node, what is the 'previous' node. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<vector<ll>> c(m, vector<ll>(3, 0));
    for(int i = 0; i < m; i++){
        cin >> c[i][0] >> c[i][1] >> c[i][2];
        c[i][0] --;
        c[i][1] --;
    }
    vector<ll> d(n, 0);
    vector<ll> p(n, -1);
    int x = -1;
    for(int i = 0; i < n; i++){
        x = -1;
        for(int j = 0; j < m; j++) {
            int a = c[j][0];
            int b = c[j][1];
            ll cost = c[j][2];
            if(d[a] + cost < d[b]) {
                x = a;
                d[b] = d[a] + cost;
                p[b] = a;
            }
        }
    }
    if(x == -1) {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    for(int i = 0; i < n; i++){
        x = p[x];
    }
    vector<int> cycle(0);
    int f = x;
    while(true) {
        cycle.push_back(x);
        x = p[x];
        if(f == x){
            break;
        }
    }
    cycle.push_back(x);
    for(int i = cycle.size() - 1; i >= 0; i--) {
        cout << cycle[i] + 1 << " \n"[i == 0];
    }
    
    return 0;
}
