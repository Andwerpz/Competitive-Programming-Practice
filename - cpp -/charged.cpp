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

//Calgary 2022 - C

//implementation

ld calc_dist(ld x1, ld y1, ld x2, ld y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ld pi = acos(-1);
    int n, m, q;
    cin >> n >> m >> q;
    vector<pair<pii, bool>> c;
    vector<string> res(n, string(m, ' '));
    for(int i = 0; i < q; i++){
        int x, y;
        cin >> x >> y;
        char s;
        cin >> s;
        c.push_back({{x, y}, s == '+'});
        res[y - 1][x - 1] = s;
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(res[i][j] != ' '){
                continue;
            }
            ld x = j + 1;
            ld y = i + 1;
            ld p = 0;
            for(int k = 0; k < q; k++){
                ld nx = c[k].first.first;
                ld ny = c[k].first.second;
                bool s = c[k].second;
                p -= 1.0 / calc_dist(x, y, nx, ny) * (s? 1 : -1);
            }
            // cout << "P : " << p << "\n";
            if(abs(p) >= 1.0 / pi) {
                res[i][j] = p > 0? '%' : '0';
            }
            else if(abs(p) >= 1.0 / (pi * pi)) {
                res[i][j] = p > 0? 'X' : 'O';
            }   
            else if(abs(p) >= 1.0 / (pi * pi * pi)) {
                res[i][j] = p > 0? 'x' : 'o';
            }
            else {
                res[i][j] = '.';
            }
        }
    }
    for(int i = 0; i < n; i++){
        cout << res[i] << "\n";
    }
    
    return 0;
}