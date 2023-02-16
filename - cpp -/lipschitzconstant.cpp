#include <bits/stdc++.h>
typedef long long ll;
typedef double ld;
using namespace std;

//NCNA 2018 Regional F

//basically, we're just trying to find where is the maximum slope. 

//maximum slope will always be found when comparing two adjacent points. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<pair<ld, ld>> v(0);
    for(int i = 0; i < n; i++) {
        ld d;
        ld x;
        cin >> x >> d;
        v.push_back({x, d});
    }

    ld most = -1;

    pair<ld,ld> prev = {v[0].first, v[0].second};
    sort(v.begin(), v.end());

    for(int i = 1; i < n; i++) {
        most = max(most, abs(v[i].second - prev.second) / abs(v[i].first - prev.first));
        prev = {v[i].first, v[i].second};
    }

    cout << most << "\n";
    
    return 0;
}
