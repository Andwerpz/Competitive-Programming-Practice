#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1694B

//a string can be reduced to length 1 when it's last character is not equal to it's second last character. 
//obviously, length 1 strings are already length 1. 

//so we can iterate i from 0 to n - 1 and calculate how many subarrays ending at i are valid. 

//if s[i] == s[i - 1], then the answer is 1; the subarray of length 1 at i. 

//else, the answer is i + 1, since all subarrays ending at i are valid. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        ll n;
        cin >> n;
        string s;
        cin >> s;
        ll ans = 0;
        for(int i = 0; i < n; i++){
            if(i == 0){
                ans ++;
                continue;
            }
            if(s[i] == s[i - 1]){
                ans ++;
                continue;
            }
            ans += i + 1;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
