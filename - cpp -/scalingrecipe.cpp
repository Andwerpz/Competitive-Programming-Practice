#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Kattis - scalingrecipe

ll gcd(ll a, ll b){
    if(b == 0){
        return a;
    }
    return gcd(b, a % b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, x, y;
    cin >> n >> x >> y;
    vector<ll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    ll g = gcd(x, y);
    x /= g;
    y /= g;
    for(int i = 0; i < n; i++){
        a[i] = (a[i] / x) * y;
        cout << a[i] << "\n";
    }
    
    return 0;
}
