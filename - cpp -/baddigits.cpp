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

//3rd Universal Cup Stage 31 : Wroclaw - B

//just generate the numbers as if the digits weren't there, then skip over them when printing. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        ll n, k, m;
        cin >> n >> k >> m;
        vb f(n, false);
        for(int i = 0; i < m; i++){
            string s;
            cin >> s;
            if('0' <= s[0] && s[0] <= '9') f[s[0] - '0'] = true;
            else f[10 + (s[0] - 'A')] = true;
        }
        vi dig(0);
        n -= m;
        while(k != 0){
            // cout << "DIG : " << k % n << endl;
            dig.push_back(k % n);
            k /= n;
        }
        string ans = "";
        for(int i = 0; i < dig.size(); i++){
            int d = dig[i];
            int ad = 0;
            while(f[ad]) ad ++;
            for(int j = 0; j < d; j++){
                ad ++;
                // cout << "AD : " << ad << endl;
                while(f[ad]) ad ++;
            }
            if(ad <= 9) ans.push_back('0' + ad);
            else ans.push_back('A' + (ad - 10));
        }
        reverse(ans.begin(), ans.end());
        cout << ans << "\n";
    }
    
    return 0;
}