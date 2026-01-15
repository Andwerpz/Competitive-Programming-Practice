#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

// ICPC PACNW 2025 - M

void solve() {
    array<int,3> a = {};
    array<int,3> b = {};
    array<int,3> c = {};

    for(auto &x : a) cin >> x;
    for(auto &x : b) cin >> x;
    for(auto &x : c) cin >> x;

    auto are_similar = [](array<int,3> a, array<int,3> b) -> bool {
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        return a == b;
    };

    int f = 0;

    for(int i = 0; i < 3; i++) {

        for(int chop = 5; chop < a[0]; chop += 5) {
            array<int,3> lhs = {chop, a[1], 180 - (chop + a[1])};
            int unchop = a[0] - chop;
            array<int,3> rhs = {unchop, a[2], 180 - (unchop + a[2])};

            int ok = 1;

            if(!(are_similar(lhs, b) || are_similar(lhs, c))) ok = 0;
            if(!(are_similar(rhs, b) || are_similar(rhs, c))) ok = 0;
            if(ok) f = 1;
        }

        rotate(a.begin(), a.begin() + 1, a.end());
    }

    cout << (f ? "YES" : "NO") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}