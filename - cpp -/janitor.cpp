#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ACPC 2023 Fall Contest J

//for each recycling bin location, we can compute the x distance and y distance sums seperately. 

//to compute the x distance sum, we can use an offline prefix sum approach. Likewise for the y distance. 

//then, answering the queries becomes O(1). 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<ll> a_x_s(1e6, 0);
    vector<ll> a_y_s(1e6, 0);
    vector<ll> a_x(1e6, 0);
    vector<ll> a_y(1e6, 0);
    for(int i = 0; i < n; i++){
        ll x, y;
        cin >> x >> y;
        a_x[0] += x;
        a_y[0] += y;
        a_x_s[0] -= 1;
        a_y_s[0] -= 1;
        a_x_s[x] += 2;
        a_y_s[y] += 2;
    }
    ll slope = a_x_s[0];
    for(int i = 1; i < a_x.size(); i++){
        a_x[i] = a_x[i - 1] + slope;
        slope += a_x_s[i];
    }
    slope = a_y_s[0];
    for(int i = 1; i < a_y.size(); i++){
        a_y[i] = a_y[i - 1] + slope;
        slope += a_y_s[i];
    }
    int q;
    cin >> q;
    for(int i = 0; i < q; i++){
        int x, y;
        cin >> x >> y;
        cout << (a_x[x] + a_y[y]) * (ll) 2 << "\n";
    }
    
    return 0;
}
