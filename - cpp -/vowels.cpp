#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

//Codeforces - 383E

//we can solve using SOS dp. Represent each word as a 24 long bitmask. For example 
//'ace' -> 101010000000000000000000

//if we try out any bitmask of vowels, then note that any valid word is going to have non-zero intersection with
//the vowel bitmask. However, counting words with non-zero intersection is hard. We instead want to count the number
//of invalid words, and take the complement. 

//for a given vowel mask, a word is invalid if it is a subset of the complement of the vowel mask. So for each vowel
//mask, we need to compute how many words it's complement is a superset for. This can be solved in O(n * 24) 
//with SOS dp. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int BITS = 24;
    vl dp((1 << BITS), 0);
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){ 
        string s;
        cin >> s;
        int a = 0;
        for(int j = 0; j < 3; j++){
            a |= (1 << (s[j] - 'a'));
        }
        dp[a] ++;
    }
    for(int i = 0; i < BITS; i++){
        for(int j = 0; j < (1 << BITS); j++){
            if(j & (1 << i)) {
                dp[j] += dp[j ^ (1 << i)];
            }
        }
    }
    ll ans = 0;
    for(int i = 0; i < (1 << BITS); i++){
        ans ^= (n - dp[i]) * (n - dp[i]);
    }
    cout << ans << "\n";
    
    return 0;
}