#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 06 C

//always buy stock if the stock price is going to go up. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int d;
    cin >> d;
    vector<ll> a(d);
    for(int i = 0; i < d; i++){
        cin >> a[i];
    }
    ll ans = 100;
    ll stock = 0;
    for(int i = 0; i < d; i++){
        //sell all stock
        ans += stock * a[i];
        stock = 0;
        //if stock goes up, buy stock
        if(i != d - 1 && a[i] < a[i + 1]) {
            ll shares = ans / a[i];
            shares = min(shares, (ll) 100000);
            stock = shares;
            ans -= shares * a[i];
        }
        //cout << ans << " " << stock << "\n";
    }
    cout << ans << "\n";
    
    return 0;
}
