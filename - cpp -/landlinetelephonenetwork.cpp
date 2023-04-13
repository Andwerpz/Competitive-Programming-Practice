#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

vector<int> dsu;

int find(int a){
    if(dsu[a] == a){
        return a;
    }
    return dsu[a] = find(dsu[a]);
}

void unify(int a, int b) {
    int ra = find(a);
    int rb = find(b);
    dsu[rb] = ra;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, p;
    cin >> n >> m >> p;
    dsu = vector<int>(n, 0);
    for(int i = 0; i < n; i++){
        dsu[i] = i;
    }
    vector<bool> insecure(n, false);
    for(int i = 0; i < p; i++){
        int next;
        cin >> next;
        next --;
        insecure[next] = true;
    }
    vector<vector<int>> c(0, vector<int>(3));
    for(int i = 0; i < m; i++){
        int a, b, cost;
        cin >> a >> b >> cost;
        a --;
        b --;
        int isinsecure = insecure[a] || insecure[b];
        c.push_back({isinsecure, cost, a, b});
    }
    sort(c.begin(), c.end());
    vector<bool> v(n, false);
    int cnt = 0;
    ll sum = 0;
    for(int i = 0; i < c.size(); i++){
        int a = c[i][2];
        int b = c[i][3];
        int cost = c[i][1];
        if(v[a] && insecure[a] || v[b] && insecure[b]) {
            continue;
        }
        if(find(a) == find(b)) {
            continue;
        }
        cnt ++;
        unify(a, b);
        sum += (ll) cost;
        v[a] = true;
        v[b] = true;
    }
    if(cnt == n - 1){
        cout << sum << "\n";
    }
    else {
        cout << "impossible\n";
    }
    
    return 0;
}
