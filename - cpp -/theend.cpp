#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef pair<int, int> pii;

//2025 ICPC Shenyang Regional - M

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    // cout <<( (8 * 7 * 6 * 5 * 4 * 3 * 2) << 7) << '\n';

    vector<array<ld,2>> a(8);
    for(auto &x : a) for(auto &y : x) cin >> y;

    vector<int> p(8);
    iota(p.begin(), p.end(), 0);

    ld res = 0;
    // reverse(p.begin(), p.end());

    while(1) {

        ld ans = 0;

        for(int bm = 0; bm < 1 << 7; bm++) {
            vector<int> cur = p;
            ld prob = 1;

            vector<int> nx;
            for(int j = 0; j < 4; j++) {
                if((bm >> j) & 1) { //a wins
                    nx.push_back(cur[j * 2]);
                    prob *= a[cur[j*2]][0] / (a[cur[j*2]][0] + a[cur[j*2+1]][1]);
                } else {
                    nx.push_back(cur[j * 2 + 1]);
                    prob *= a[cur[j*2+1]][1] / (a[cur[j*2]][0] + a[cur[j*2+1]][1]);
                }
            }

            cur = nx;
            nx.clear();
            for(int j = 0; j < 2; j++) {
                if((bm >> (j + 4)) & 1) {
                    nx.push_back(cur[j * 2]);
                    prob *= a[cur[j*2]][0] / (a[cur[j*2]][0] + a[cur[j*2+1]][1]);
                } else {
                    nx.push_back(cur[j * 2 + 1]);
                    prob *= a[cur[j*2+1]][1] / (a[cur[j*2]][0] + a[cur[j*2+1]][1]);
                }
            }

            cur = nx;
            nx.clear();

            for(int j = 0; j < 1; j++) {
                if((bm >> (j + 6)) & 1) {
                    nx.push_back(cur[j * 2]);
                    prob *= a[cur[j*2]][0] / (a[cur[j*2]][0] + a[cur[j*2+1]][1]);
                } else {
                    nx.push_back(cur[j * 2 + 1]);
                    prob *= a[cur[j*2+1]][1] / (a[cur[j*2]][0] + a[cur[j*2+1]][1]);
                }
            }

            cur = nx;
            if(cur[0] == 0) ans += prob;
        }

        // cout << "ans : " << ans << '\n';

        res = max(res, ans);

        if(!next_permutation(p.begin(), p.end())) break;
        // break;
    }

    cout << fixed << setprecision(10) << res << '\n';

    // cout << fixed << setprecision(10) << 0.329505822460368 / res << '\n';

    return 0;
}