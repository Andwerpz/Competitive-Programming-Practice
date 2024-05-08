#include <bits/stdc++.h>
typedef long long ll;
// typedef __int128 lll;
typedef long double ld;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1948D

//let's try to test whether there exists a tandem substring in S, of a given length A. 
//we test this in O(|S|) time, using a sliding window approach. 

//since we can afford |S|^2 time, we can just try all lengths A. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        string s;
        cin >> s;
        int n = s.size();
        int ans = 0;
        for(int i = 1; i <= n / 2; i++){
            int vcnt = 0;
            for(int j = 0; j < i; j++){
                vcnt += (s[j] == s[j + i]) || s[j] == '?' || s[j + i] == '?';
            }
            if(vcnt == i){
                ans = i;
                continue;
            }
            for(int j = 0; j + i * 2 < n; j++){
                vcnt -= (s[j] == s[j + i]) || s[j] == '?' || s[j + i] == '?';
                vcnt += (s[j + i] == s[j + i * 2]) || s[j + i] == '?' || s[j + i * 2] == '?';
                if(vcnt == i){
                    ans = i;
                    break;
                }
            }
        }
        cout << ans * 2 << "\n";
    }
    
    return 0;
}
