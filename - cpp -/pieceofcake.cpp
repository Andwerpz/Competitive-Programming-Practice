#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ACPC Week 6C

//simple implementation problem

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    ll d; cin >> d;
    ll a[n];
    for (int i = 0; i < n; ++i) cin >> a[i];
    map<ll, ll> freq;
    for (auto x : a) {
        freq[x / d]++;
    }
    ll ans = 0;
    for (auto p : freq) {
        ans += p.second * (p.second - 1) / 2;
    }
    cout << ans << endl;
    return 0;
}
