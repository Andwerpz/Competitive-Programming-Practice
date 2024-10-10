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

//Calgary 2022 - D

//implementation

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    string line;
    getline(cin, line);
    while(t--){
        ll a = 0, b = 0;
        getline(cin, line);
        for(int i = 0; i < line.size(); i += 2){
            a *= 10;
            a += line[i] - '0';
        }
        getline(cin, line);
        for(int i = 0; i < line.size(); i += 2){
            b *= 10;
            b += line[i] - '0';
        }
        a += b;
        vi res(0);
        while(a != 0){
            res.push_back(a % 10);
            a /= 10;
        }
        reverse(res.begin(), res.end());
        for(int i = 0; i < res.size(); i++){
            cout << res[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}