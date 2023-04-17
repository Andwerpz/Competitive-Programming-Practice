#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 10 A

//you can just create a minimum spanning tree. 

//the key observation is that any minimum spanning tree connecting the dishes cannot have beams
//that violate the conditions; no crossing beams, and no beams crossing dishes. 

//this can be kind of 'proven' by seeing that if two beams cross, or if a beam crosses a dish, then there is always
//a better way to position that beam so that it doesn't violate the rules. 

vector<int> dsu;

int find(int a) {
    if(dsu[a] == a) {
        return a;
    }
    return dsu[a] = find(dsu[a]);
}

bool unify(int a, int b) {
    int ra = find(a);
    int rb = find(b);
    if(ra == rb) {
        return false;
    }
    dsu[rb] = ra;
    
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    dsu = vector<int>(n, 0);
    for(int i = 0; i < n; i++){
        dsu[i] = i;
    }
    vector<pair<ld, ld>> a(n, {0, 0});
    vector<ld> r(n, 0);
    for(int i = 0; i < n; i++){
        cin >> a[i].first >> a[i].second >> r[i];
    }
    vector<pair<ld, pair<int, int>>> c(0);
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            ld dist = sqrt(pow(a[i].first - a[j].first, 2) + pow(a[i].second - a[j].second, 2));
            dist -= r[i] + r[j];
            c.push_back({dist, {i, j}});
        }
    }
    sort(c.begin(), c.end());
    int cnt = 0;
    ld ans = 0;
    for(int i = 0; i < c.size(); i++){
        int u = c[i].second.first;
        int v = c[i].second.second;
        ld dist = c[i].first;
        if(find(u) != find(v)) {
            unify(u, v);
            ans += dist;
        }
    }
    cout << fixed << setprecision(10) << ans << "\n";
    
    return 0;
}
