#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef long long ll;
typedef vector<ll> vl;

//ICPC ECNA 2025 - A

//freebie

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    int S, M, L;
    S = 0, M = 0, L = 0;
    for(int i = 0; i < n; i++) {
        string t;
        cin >> t;
        int x;
        cin >> x;
        if(t == "S") S += x;
        else if(t == "M") M += x;
        else if(t == "L") L += x;
        else assert(false);
    }
    int ans = (S + 5) / 6 + (M + 7) / 8 + (L + 11) / 12;
    cout << ans << "\n";

    return 0;
}