#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 05 E

//you can deal with the positive and negative destinations seperately. 

//prioritize sending letters to the farthest destinations first. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    ll k;
    cin >> n >> k;
    vector<pair<ll, ll>> a(0);
    vector<pair<ll, ll>> b(0);
    for(int i = 0; i < n; i++){
        ll t, j;
        cin >> t >> j;
        if(t > 0){
            a.push_back({t, j});
        }
        else {
            b.push_back({-t, j});
        }
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    ll ans = 0;
    int ptr = 0;
    while(ptr != a.size()) {
        ll rep = a[ptr].second / k;
        ans += rep * a[ptr].first;
        a[ptr].second %= k;
        if(a[ptr].second == 0){
            ptr ++;
        }
        if(ptr == a.size()){
            break;
        }
        ans += a[ptr].first;
        ll sum = k;
        while(ptr != a.size() && sum != 0){
            ll diff = min(sum, a[ptr].second);
            a[ptr].second -= diff;
            sum -= diff;
            if(a[ptr].second == 0){
                ptr ++;
            }
        }
    }
    ptr = 0;
    while(ptr != b.size()) {
        ll rep = b[ptr].second / k;
        ans += rep * b[ptr].first;
        b[ptr].second %= k;
        if(b[ptr].second == 0){
            ptr ++;
        }
        if(ptr == b.size()){
            break;
        }
        ans += b[ptr].first;
        ll sum = k;
        while(ptr != b.size() && sum != 0){
            ll diff = min(sum, b[ptr].second);
            b[ptr].second -= diff;
            sum -= diff;
            if(b[ptr].second == 0){
                ptr ++;
            }
        }
    }
    cout << ans * 2 << "\n";
    
    return 0;
}
