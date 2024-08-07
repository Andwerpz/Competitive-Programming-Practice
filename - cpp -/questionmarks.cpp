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

//Codeforces - 1993A

//just count the frequency of each letter, and if the frequency of a letter goes over n, then
//cap it there. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        string s;
        cin >> s;
        int a = 0, b = 0, c = 0, d = 0;
        for(int i = 0; i < n * 4; i++){
            a += s[i] == 'A';
            b += s[i] == 'B';
            c += s[i] == 'C';
            d += s[i] == 'D';
        }
        int ans = min(a, n) + min(b, n) + min(c, n) + min(d, n);
        cout << ans << "\n";
    }
    
    return 0;
}