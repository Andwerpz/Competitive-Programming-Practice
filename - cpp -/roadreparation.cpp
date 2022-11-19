#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSES 1675

//if you find the minimum spanning tree connecting all the cities, then that's the road netowork 
//that you can build to minimize the cost. 

int find(vector<int>& c, int a){
    if(c[a] == a){
        return a;
    }
    return c[a] = find(c, c[a]);
}

bool unify(vector<int>& c, int a, int b) {
    int aRoot = find(c, a);
    int bRoot = find(c, b);
    c[aRoot] = bRoot;
    return aRoot != bRoot;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<vector<int>> conn(0);
    for(int i = 0; i < m; i++){
        int a, b, c;
        cin >> a >> b >> c;
        a --;
        b --;
        conn.push_back({a, b, c});
    }
    sort(conn.begin(), conn.end(), [](vector<int>& a, vector<int>& b) -> bool {return a[2] < b[2];});
    ll ans = 0;
    int cnt = 0;
    vector<int> dsu(n, 0);
    for(int i = 0; i < n; i++){
        dsu[i] = i;
    }
    for(int i = 0; i < m; i++){
        int a = conn[i][0];
        int b = conn[i][1];
        int c = conn[i][2];
        if(unify(dsu, a, b)) {
            cnt ++;
            ans += c;
        }
    }
    if(cnt == n - 1){
        cout << ans << "\n";
    }
    else {
        cout << "IMPOSSIBLE\n";
    }
    
    return 0;
}
