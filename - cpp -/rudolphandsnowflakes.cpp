#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef __int128 lll;
using namespace std;

//Codeforces - 1846E1 / E2

//note that if we perform s steps, then the total number of nodes is k^0 + k^1 + k^2 + ... + k^s
//thus, we need to find k and s where this formula equals n. 

//for the easy version, it is sufficient to search for each k from 2 to 10^6, all s from 3 to 60, essentially
//brute force all possible k and s. 

//for the hard version, we can't do this as the last feasible k is 10^9, which is too slow to brute force. 
//thus, for each s, of which we search from 3 to 70, we can binary search the maximum k such that the sum is
//less than or equal to n. 

bool isValid(lll n, lll k, lll step) {
    lll sum = 0;
    lll ptr = 1;
    for(int i = 0; i < step; i++){
        sum += ptr;
        ptr *= k;
        if(sum > n) {
            return false;
        }
    }
    return true;
}

bool check(lll n, lll k, lll step) {
    if(k <= 1) {
        return false;
    }
    lll sum = 0;
    lll ptr = 1;
    for(int i = 0; i < step; i++){
        sum += ptr;
        ptr *= k;
        if(sum > n) {
            return false;
        }
    }
    return sum == n;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll tmp;
        cin >> tmp;
        lll n = tmp;
        bool valid = false;
        for(lll step = 3; step < 70; step++){
            lll low = 0;
            lll high = 1e9;
            lll ans = low;
            while(low <= high) {
                lll mid = low + (high - low) / 2;
                if(isValid(n, mid, step)) {
                    ans = max(ans, mid);
                    low = mid + 1;
                }
                else {
                    high = mid - 1;
                }
            }
            if(check(n, ans, step)) {
                //cout << "FOUND ANS : " << (ll) ans << " " << (ll) step << "\n";
                valid = true;
                break;
            }
        }
        cout << (valid? "YES\n" : "NO\n");
    }
    
    return 0;
}
