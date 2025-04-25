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

//University of Alberta Programming Contest 2025 Open - C

//since s.size() <= 10, we can simply brute force. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    string s;
    cin >> s;
    int n;
    cin >> n;
    string t;
    getline(cin, t);
    getline(cin, t);
    int ans = 0;
    for(int i = 0; i <= (int) t.size() - s.size(); i++) {
        bool is_valid = true;
        for(int j = 0; j < s.size(); j++){
            if(t[i + j] != s[j]) is_valid = false;
        }
        ans += is_valid;
    }
    cout << ans << "\n";
    
    return 0;
}