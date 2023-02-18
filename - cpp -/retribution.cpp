#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 05 D

//at first, trying to simulate the problem might seem challenging, but the trick is to notice that you can 
//just tabulate all the pairs between judges and tarring / feathering spots, and sort them in the desired order. 

//from there, just keep track of which judges / tarring / feathering spots you've already assigned. 

ld getDist(pair<ld, ld> a, pair<ld, ld> b){
    return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

ld solve(vector<pair<ld, ld>> a, vector<pair<ld, ld>> b) {
    vector<bool> v(a.size());
    vector<bool> v2(b.size());
    ld ans = 0;
    vector<pair<int, int>> p(0);
    for(int i = 0; i < a.size(); i++){
        for(int j = 0; j < b.size(); j++){
            p.push_back({i, j});
        }
    }
    sort(p.begin(), p.end(), [&](pair<int, int> a1, pair<int, int> a2) -> bool {
        ld dist1 = getDist(a[a1.first], b[a1.second]);
        ld dist2 = getDist(a[a2.first], b[a2.second]);
        if(dist1 != dist2) {
            return dist1 < dist2;
        }
        if(a1.first != a2.first){
            return a1.first < a2.first;
        }
        return a1.second < a2.second;
    });
    for(int i = 0; i < p.size(); i++){
        if(v[p[i].first]) {
            continue;
        }
        if(v2[p[i].second]){
            continue;
        }
        v[p[i].first] = true;
        v2[p[i].second] = true;
        ld dist = getDist(a[p[i].first], b[p[i].second]);
        //cout << dist << "\n";
        ans += dist;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, p;
    cin >> n >> m >> p;
    vector<pair<ld, ld>> j(n);
    vector<pair<ld, ld>> t(m);
    vector<pair<ld, ld>> f(p);
    for(int i = 0; i < n; i++){
        cin >> j[i].first >> j[i].second;
    }
    for(int i = 0; i < m; i++){
        cin >> t[i].first >> t[i].second;
    }
    for(int i = 0; i < p; i++){
        cin >> f[i].first >> f[i].second;
    }
    cout << fixed << setprecision(10) << solve(j, t) + solve(j, f) << "\n";
    
    return 0;
}
