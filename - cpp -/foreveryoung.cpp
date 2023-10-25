#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2016 E

//probably the better approach is to notice that we can test all bases up to cbrt(y). 
//if a base is larger than cbrt(y), then the value in that base can't have more than 4 digits,
//so to cover all bases larger than cbrt(y), we can just try all values up to 1e4. 

bool is_base_valid(ll y, ll b, ll l) {
    ll num = 0;
    ll nr_dig = 0;
    while(y != 0){
        if(y % b >= 10){
            return false;
        }
        nr_dig ++;
        num *= 10ll;
        num += y % b;
        //cout << "NUM : " << num << "\n";
        //cout << "Y : " << y << "\n";
        y /= b;
    }
    ll tmp = 0;
    for(int i = 0; i < nr_dig; i++){
        tmp *= 10ll;
        tmp += num % 10;
        num /= 10;
    }
    //cout << "TMP : " << tmp << "\n";
    return tmp >= l;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll y, l; cin >> y >> l;

    //cout << is_base_valid(100, 33, 50) << "\n";

    ll ans = 10;
    if(l == 10) {
        ans = y;
    }
    ll b = 10;
    ll nr_b = 0;
    while(b < cbrt(y) + 100 && b < y) {
        // if(rand() % 1000000 == 0){
        //     cout << "B : " << b << endl;
        // }
        
        nr_b ++;
        if(is_base_valid(y, b - 1, l)) {
            ans = max(ans, b - 1);
        }
        while(y % b < 10) {
            if(is_base_valid(y, b, l)) {
                ans = max(ans, b);
            }
            b ++;
        }
        {
            ll low = b + 1;
            ll high = sqrt(y) + 1000;
            ll n_b = high;
            while(low <= high) {
                ll mid = low + (high - low) / 2;
                if((y / b) != (y / mid)) {
                    n_b = min(n_b, mid);
                    high = mid - 1;
                }
                else {
                    low = mid + 1;
                }
            }
            b = n_b;
        }
    }
    //cout << "NR_B : " << nr_b << "\n";

    for(ll i = l; i <= 10000; i++){
        ll low = 10;
        ll high = y;
        ll n_b = low;
        //cout << "I : " << i << "\n";
        while(low <= high) {
            ll mid = low + (high - low) / 2;
            lll val = 0;
            lll tmp = i;
            lll pow = 1;
            while(tmp != 0){
                val += pow * (tmp % 10);
                tmp /= 10;
                if(val > y){
                    break;
                }
                pow *= mid;
            }
            //cout << "VAL : " << val << "\n";
            if(val <= y) {
                n_b = max(n_b, mid);
                if(val == y){
                    ans = max(ans, n_b);
                }
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }
    }

    cout << ans << endl;

    return 0;
}
