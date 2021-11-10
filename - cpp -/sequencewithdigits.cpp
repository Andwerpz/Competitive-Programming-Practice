
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1355A

//just simulate the problem. If the minimum digit becomes 0, then a will stop increasing. 

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        ll a, k;
        cin >> a >> k;
        ll ans = 0;
        if(k == 1){
            ans = a;
        }
        for(int i = 1; i < k; i++){
            string s = to_string(a);
            int minDigit = 10;
            int maxDigit = 0;
            for(int j = 0; j < s.size(); j++){
                int next = s[j] - '0';
                minDigit = min(next, minDigit);
                maxDigit = max(next, maxDigit);
            }
            if(minDigit == 0){
                ans = a;
                break;
            }
            a += minDigit * maxDigit;
            if(i == k - 1){
                ans = a;
            }
        }
        cout << ans << endl;
    }

    return 0;
}



