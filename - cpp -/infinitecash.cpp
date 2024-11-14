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

//NCPC 2024 - I

//verdict : use python

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    string s, d, m; cin >> s >> d >> m;

    int daysbefore0 = m.size() + 1;

    int daysbeforesalary = 0;
    if(d.size() < 30) {
        for(int i = 0; i < d.size(); i++) {
            if(d[d.size()-1-i] == '1') {
                daysbeforesalary += 1 << i;
            }
        }
    } else {
        daysbeforesalary = 1e9;
    }

    cout << "d0 : " << daysbefore0 << '\n';
    cout << "ds : " << daysbeforesalary << '\n';

    if(daysbeforesalary <= daysbefore0) {
        cout << "Infinite money!\n";
    } else {
        string res = "";
        while(daysbefore0) {
            if(daysbefore0 & 1) {
                res.push_back('1');
            } else {
                res.push_back('0');
            }
            daysbefore0 >>= 1;
        }
        reverse(res.begin(), res.end());
        cout << res << '\n';
    }
    
    return 0;
}