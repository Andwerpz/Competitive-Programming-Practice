#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef pair<int, int> pii;

//2025 ICPC Shenyang Regional - K

//lets say a frog at location A jumps over one at location B. 
//then the new location A' = A + (B - A) * 2 = 2B - A
//so the total delta is 2B - 2A

//now, lets say B jumps over C, we get B' = 2C - B, with total delta 2C - 2B
//observe that if we take the total sum of all deltas, we get 2C - 2A (interesting...)

//now, lets say that C jumps over A, which is at location A'
//the total delta is now (2C - 2A) + (2A' - 2C) = 2A' - 2A

//it seems like no matter what jump happens, the total delta will be of form
//2<last frog position> - 2<first frog position>
//since we know which frog jumped first, we can use this to get the last frogs position. 

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, s; cin >> n >> s;
    s--;

    vector<array<ll,4>> a(n);
    for(auto &x : a) for(auto &y : x) cin >> y;

    array<ll,2> net = {0,0};
    array<ll,2> sub = {a[s][0], a[s][1]};
    for(int i = 0; i < n; i++) {
        a[i][0] -= sub[0];
        a[i][1] -= sub[1];
        a[i][2] -= sub[0];
        a[i][3] -= sub[1];

        net[0] += a[i][2] - a[i][0];
        net[1] += a[i][3] - a[i][1];

        // cout << "i : " << i;
        // for(auto x : a[i]) cout << " " << x;
        // cout << '\n';
    }

    // cout << "net : " << net[0] << ", " << net[1] << '\n';

    net[0] /= 2;
    net[1] /= 2;

    for(int i = 0; i < n; i++) {
        if(a[i][2] == net[0] && a[i][3] == net[1]) {
            cout << i + 1 << '\n';
            return 0;
        }
    }

    assert(0);

    return 0;
}