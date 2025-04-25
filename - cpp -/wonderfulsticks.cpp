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

//Codeforces - 2096A

//can just construct the answer backwards. 

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
        int l = 1, r = n;
        vi ans(n);
        for(int i = n - 1; i > 0; i--){
            if(s[i - 1] == '<') ans[i] = l ++;
            else ans[i] = r --;
        }
        ans[0] = l;
        for(int i = 0; i < n; i++) cout << ans[i] << " ";
        cout << "\n";
    }
    
    return 0;
}