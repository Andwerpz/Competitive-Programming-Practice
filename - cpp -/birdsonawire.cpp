#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Lab 03 D

//you just need to greedily cram in as many birds as possible between each pair of adjacent birds. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll len, d;
    int n;
    cin >> len >> d >> n;
    vector<ll> a(n + 2);
    a[0] = 6 - d;
    a[n + 1] = (len - 6) + d;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    ll ans = 0;
    for(int i = 0; i < a.size() - 1; i++) {
        ll l = a[i];
        ll r = a[i + 1];
        ll diff = r - l - d;
        ans += diff / d;
    }
    cout << ans << "\n";
    
    return 0;
}
