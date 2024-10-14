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

//Codeforces - 2005A

//palindromes that only consist of the same letter cannot be avoided. However, palindromes with 
//different letters can be avoided by clumping all of the occurrences of one letter together. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    string v = "aeiou";
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        string ans(n, ' ');
        for(int i = 0; i < n; i++){
            ans[i] = v[i % 5];
        }
        sort(ans.begin(), ans.end());
        cout << ans << "\n";
    }
    
    return 0;
}