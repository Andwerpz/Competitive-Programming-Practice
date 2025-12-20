#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef pair<int, int> pii;

//2025 ICPC Shenyang Regional - I

//implementation

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    set<pii> v;
    map<int, int> f;
    for(int i = 0; i < n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        if(v.count({a, b})) {
            cout << "0\n";
            continue;
        }
        v.insert({a, b});
        f[a] ++;
        int ans = 0;
        if(c < 240) ans = b;
        else if(c >= 240 && f[a] <= 3) ans = b;
        cout << ans << "\n";
    }

    return 0;
}