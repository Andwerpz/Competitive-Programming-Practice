#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int, int>;

//ICPC World Finals 2020 Online E

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        ll h, p; cin >> h >> p;
        ll cnt = 0;
        ll ready = 1;
        ll rem = pow(2, h) - 1;

        while (ready < p && rem > 0) {
            cnt++;
            rem -= ready;
            ready *= 2;
        }

        cnt += (rem + p - 1) / p;

        cout << cnt << endl;
    }
    return 0;
}