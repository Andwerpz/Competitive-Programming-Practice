#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ICPC North America Qualifier 2022 H

ll solve(vector<ll>& a, ll s, ll k) {
    ll n = a.size();
    ll ans = 0;
    vector<ll> radii(n, 0);
    for(int i = 0; i < n; i++){
        radii[i] = s;
    }
    bool isValid = true;
    vector<ll> diff(0);
    sort(a.begin(), a.end());
    for(int i = 0; i < n; i++){
        ll diff = i == n - 1? k * 2 : abs(a[i + 1] - a[i]);
        if(diff < s * 2){
            isValid = false;
            break;
        }
        ll room = i == n - 1? k : diff - radii[i] - radii[i + 1];
        ll nextRadii = min(radii[i] + room, k);
        if(i != 0){
            ll pDiff = abs(a[i] - a[i - 1]);
            ll sub = pDiff - nextRadii - radii[i - 1];
            if(sub < 0){
                nextRadii += sub;
            }
        }
        radii[i] = nextRadii;
        ans += radii[i];
    }
    return (isValid? ans : -1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, s, k;
    cin >> n >> s >> k;
    ll ans = 0;
    vector<ll> a(n, 0);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        a[i] *= 2;
    }
    ll lAns = solve(a, s, k);
    reverse(a.begin(), a.end());
    ll rAns = solve(a, s, k);
    //cout << lAns << " " << rAns << "\n";
    cout << max(lAns, rAns) << "\n";
    
    return 0;
}