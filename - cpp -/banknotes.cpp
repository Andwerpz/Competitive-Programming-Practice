
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//Codeforces - 1606C

//getting some weird out of bounds errors. Going to go try this in java, see if that works.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        ll n, k;
        cin >> n >> k;
        k ++;
        ll prev = 0;
        ll ans = 0;
        cin >> prev;
        for(int i = 1; i < n; i++){
            ll next;
            cin >> next;
            ll powerDiff = next - prev;
            ll max = pow(10ll, powerDiff) - 1ll;
            ans += pow(10ll, prev) * min(max, k);
            k -= min(max, k);
            prev = next;
            if(k <= 0){
                break;
            }
        }
        string temp = "";
        if(k != 0){
            temp = to_string(k);
        }
        if(n == 1){
            cout << k << endl;
        }
        else{
            cout << temp << ans << endl;
        }
    }
    
    return 0;
}
