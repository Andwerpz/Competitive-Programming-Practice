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

//ECNA 2023 - K

//we want to count the number of unique pairs of strings such that there is a valid clue 

//since string lengths are <= 20, we can do this by just brute forcing every pair of strings. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<string> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    map<pair<array<char, 4>, pii>, int> f;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(a[i].size() != a[j].size()) continue;
            if(i == j) continue;
            bool valid = true;
            int diffpos = -1;
            for(int k = 0; k < a[i].size() - 1; k++) {
                if(a[i][k] != a[j][k] && a[i][k + 1] != a[j][k + 1]) {
                    if(diffpos != -1) valid = false;
                    diffpos = k;
                }
            }
            if(diffpos == -1) continue;
            for(int k = 0; k < a[i].size(); k++) {
                if((k == diffpos || k == diffpos + 1)){
                    if(a[i][k] == a[j][k]) valid = false;
                }
                else if(a[i][k] != a[j][k]) valid = false;
            }
            if(!valid) continue;
            // cout << "PAIR : " << a[i] << " " << a[j] << "\n";
            f[{{a[i][diffpos], a[i][diffpos + 1], a[j][diffpos], a[j][diffpos + 1]}, {diffpos, (int) a[i].size()}}] ++;
        }
    }
    int ans = 0;
    for(auto i = f.begin(); i != f.end(); i++) {
        if(i->second == 1) ans ++;
    }
    assert((ans % 2) == 0);
    ans /= 2;
    cout << ans << "\n";
    
    return 0;
}