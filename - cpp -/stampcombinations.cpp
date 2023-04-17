#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 10 H

//sliding window. 

//it doesn't tle because n * m <= 10^7

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    ll sum = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        sum += a[i];
    }
    for(int i = 0; i < q; i++){
        ll next;
        cin >> next;
        ll rsum = 0;
        bool isValid = false;
        int r = 0;
        for(int j = 0; j < n; j++){
            while(r != n && (sum - rsum > next || r < j)) {
                rsum += a[r ++];
            }
            if(sum - rsum == next) {
                isValid = true;
                break;
            }
            rsum -= a[j];
        }
        cout << (isValid? "Yes\n" : "No\n");
    }
    
    return 0;
}
