#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ICPC North America Qualifier 2022 K

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll a, b, c; cin >> a >> b >> c;
    ll ans = 11234576948;
    for (int i = 0; i < 4; ++i) {
        ll num = 0;
        if (i == 0) num = a + b;
        else if (i == 1) num = a - b;
        else if (i == 2) num = a * b;
        else if (a % b == 0) num = a / b;
        else continue; 
        ll orig_num = num;
        for (int j = 0; j < 4; ++j) {
            num = orig_num;
            if (j == 0) num += c;
            else if (j == 1) num -= c;
            else if (j == 2) num *= c;
            else if (num % c == 0) num /= c;
            else continue; 
            // cerr << "num : " << num << endl;
            if (num >= 0) ans = min(ans, num);
        }
        
    }


    // for (int i = 0; i < 4; ++i) {
    //     ll num = 0;
    //     if (i == 0) num = b + c;
    //     else if (i == 1) num = b - c;
    //     else if (i == 2) num = b * c;
    //     else if (b % c == 0) num = b / c;
    //     else continue; 
    //     for (int j = 0; j < 4; ++j) {
    //         if (j == 0) num += a;
    //         else if (j == 1) num = a - num;
    //         else if (j == 2) num *= a;
    //         else if (a % num == 0) num = a / num;
    //         else continue; 
    //         if (num >= 0) ans = min(ans, num);
    //     }
        
    // }


    cout << ans << endl;
    return 0;
}

