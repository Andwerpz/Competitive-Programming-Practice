#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int, int>;

//ICPC World Finals 2015 A

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    long double p, a, b, c, d; cin >> p >> a >> b >> c >> d;
    int n; cin >> n;
    long double mx = 0;

    long double ans = 0;

    for (long double k = 1; k <= n; ++k) {
        long double price = p * (sin(a*k + b) + cos(c*k + d) + 2);
        if (price < mx) {
            ans = max(ans, mx - price);
        } else mx = price;
    } 


    cout << fixed << setprecision(10);
    cout << ans << endl;
    return 0;
}