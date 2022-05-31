#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1691C

//we only care about the first and last digits. A digit in the first position
//will contribute only 10, and a digit in the last position will contribute only 1.

//every other digit will contribute 11. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, k;
        cin >> n >> k;
        string s;
        cin >> s;
        int first = -1;
        int last = -1;
        int ans = 0;
        for(int i = 0; i < n; i++){
            if(s[i] == '1'){
                if(first == -1){
                    first = i;
                }
                last = i;
                if(i == 0){
                    ans += 10;
                }
                else if(i == n - 1){
                    ans += 1;
                }
                else {
                    ans += 11;
                }
            }
        }
        if(first == -1){
            cout << "0\n";
            continue;
        }
        bool lastInLast = last == n - 1;
        if(last != n - 1 && (n - 1) - last <= k){
            //cout << "SWAP LAST\n";
            lastInLast = true;
            k -= (n - 1) - last;
            ans -= 10;
            if(last == 0){
                ans += 1;
            }
        }
        if(first != 0 && first <= k && (first != last || !lastInLast)){
            //cout << "SWAP FIRST\n";
            ans -= 1;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
