#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int, int>;
ll MOD = 1e9 + 7;

//2023 Columbia University Local Contest E

//just return the binary of the flipped cards

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string s; cin >> s;

    ll cnt = 0;
    ll two = 1;
    while (s.size()) {
        if (s.back() == 'O') {
            cnt = (cnt + two) % MOD;
        }
        s.pop_back();
        two *= 2;
        two %= MOD;
    }

    cout << cnt << endl;

    return 0;
}