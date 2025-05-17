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

//ICPC NAC 2023 - J

//first string looks like 'ABA'. Second string looks like 'B'. Fix the first B and count how many A make it work. 
//there are around n^2 choices for B, each of which have n choices for A. Each choice for A can be tested in O(1) time
//by iterating from large A to small A. 

//finally, just have to gather all the cases where len(A) = 0. Can just iterate over all starting points of the two substrings. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    string s;
    cin >> s;
    int n = s.size();
    vvi lcp(n, vi(n, 0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; i + k < n && j + k < n; k++) {
                if(s[i + k] != s[j + k]) break;
                lcp[i][j] ++;
            }
        }
    }
    ll ans = 0;
    for(int l = 0; l < n; l++){
        for(int r = l + 1; r <= n; r++){
            //B = s[l, r)
            ll cnt = 0;
            int bl = r - l;
            for(int i = n; i >= 1; i--){
                //i = len(A)
                int fa = l - i, sa = r;
                if(fa >= 0 && sa < n && lcp[fa][sa] >= i) ans += cnt;
                if(n - (r + i - 1) >= bl) cnt += lcp[l][r + i - 1] >= bl;
                if(l - i + 1 >= bl) cnt += lcp[l][l - i + 1 - bl] >= bl;
            }
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            ans += min(j - i, lcp[i][j]);
        }
    }
    cout << ans << "\n";

    return 0;
}