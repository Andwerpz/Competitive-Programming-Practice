#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1762C

//notice that if the binary string consists of only 0 or 1, then each prefix, p, has
//2^(len(p) - 1) possible valid extensions, or in other words, all extensions are valid. 

//now consider the case where the first half of the string consists of '1' and the second half
//consists of only '0'. Notice that any valid extension including a digit from the '0' portion must have all '0's
//in the '1' portion in order to 'balance out' the '1's. So in order to make an extension to the prefix
//that contains the '0' portion, there is only 1 possible permutation in the '1' portion. 

//thus, we can just count how many consecutive same elements we've seen, and just add 2^amt to the answer every time. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll mod = 998244353;
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        string s;
        cin >> s;
        ll pow = 1;
        ll ans = 1;
        for(int i = 1; i < n; i++){
            pow = (pow * 2) % mod;
            if(s[i] != s[i - 1]) {
                pow = 1;
            }
            ans += pow;
            ans %= mod;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
