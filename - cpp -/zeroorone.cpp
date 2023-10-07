#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//AtCoder - ABC293F

//for low b, we can just do a linear search, up to around b = 100. 

//then, we notice that if we want to write n in base b, it's going to look like a bitstring
//of length at most around 10, since b >= 100 as we already searched all b < 100. 

//so, for each bitstring of length 10, let's search for the maximum b where that value in
//base b is less than or equal to n. 

bool solve(lll n, lll base, int bits) {
    lll sum = 0;
    lll mul = 1;
    while(bits != 0){
        if(bits & 1) {
            sum += mul;
        }
        if(sum > n) {
            return false;
        }
        mul *= base;
        bits /= 2;
        if(mul > n && bits != 0){
            return false;
        }
    }
    return sum <= n;
}

bool is_eq(lll n, lll base, int bits) {
    lll sum = 0;
    lll mul = 1;
    while(bits != 0){
        if(bits & 1) {
            sum += mul;
        }
        if(sum > n) {
            return false;
        }
        mul *= base;
        bits /= 2;
        if(mul > n && bits != 0){
            return false;
        }
    }
    bool equal = sum == n;
    //cout << "IS EQUAL : " << (ll) n << " " << (ll) sum << " " << (ll) base << " " << equal << "\n";
    return equal;
}

void print_bstring(int bits) {
    for(int i = 0; i < 10; i++){
        cout << (bits & 1) << " ";
        bits /= 2;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll n;
        cin >> n;
        ll thresh = 100;
        ll ans = 0;
        for(ll i = 2; i < thresh; i++){
            bool isValid = true;
            ll tmp = n;
            while(tmp != 0){
                if(tmp % i > 1) {
                    isValid = false;
                    break;
                }
                tmp /= i;
            }
            if(isValid) {
                //cout << "GOOD BASE : " << i << "\n";
            }
            ans += isValid;
        }
        for(int i = 0; i < (1 << 10); i++){
            lll low = 2;
            lll high = 1e18;
            lll base = low;
            while(low <= high) {
                lll mid = low + (high - low) / 2;
                if(solve(n, mid, i)) {
                    base = max(base, mid);
                    low = mid + 1;
                }
                else {
                    high = mid - 1;
                }
            }
            //cout << "FOUND BASE : " << (ll) base << " ";
            //print_bstring(i);
            //cout << "\n";
            if(base >= thresh) {
                bool equal = is_eq(n, base, i);
                //cout << "IS EQUAL : " << equal << "\n";
                if(equal) {
                    //cout << "ADDING 1" << endl;
                    ans += 1;
                }
            }
        }
        cout << ans << "\n";
    }    
    
    return 0;
}
