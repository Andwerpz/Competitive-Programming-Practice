#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef long double ld;

//NCPC 2025 - D

//suppose that you somehow have found the first element in the sequence. 
//then, you can determine the ordering of the remaining elements by just sorting them 
//in ascending order of distance to the first element. 

//so how do you find the first/last element in the sequence? Take an arbitrary element,
//and find the element that has largest distance to it. That element must be the first/last
//element. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int n;
    cin >> n;
    vector<ll> x(n), y(n);
    for(int i = 0; i < n; i++) cin >> x[i] >> y[i];
    int start = -1;
    ld mxdist = -1;
    for(int i = 0; i < n; i++){
        ll cdist = (x[0] - x[i]) * (x[0] - x[i]) + (y[0] - y[i]) * (y[0] - y[i]);
        if(cdist > mxdist) {
            mxdist = cdist;
            start = i;
        }
    }
    vector<pair<ll, int>> ord;
    for(int i = 0; i < n; i++) {
        ll cdist = (x[start] - x[i]) * (x[start] - x[i]) + (y[start] - y[i]) * (y[start] - y[i]);
        ord.push_back({cdist, i});
    }
    sort(ord.begin(), ord.end());
    ld ans = 0;
    for(int i = 0; i < n - 1; i++) {
        int u = ord[i].second;
        int v = ord[i + 1].second;
        ld cdist = (x[u] - x[v]) * (x[u] - x[v]) + (y[u] - y[v]) * (y[u] - y[v]);
        ans += sqrt(cdist);
    }
    cout << fixed << setprecision(10) << ans << "\n";

    return 0;
}