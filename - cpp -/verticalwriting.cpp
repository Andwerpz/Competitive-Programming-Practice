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

//AtCoder - ABC366B

//implementation

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n;
    cin >> n;
    vector<string> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    for(int i = 0; i < 100; i++){
        bool found = false;
        string line = "";
        for(int j = 0; j < n; j++){
            if(i < a[j].size()) {
                found = true;
                line.push_back(a[j][i]);
            }
            else {
                if(found) {
                    line.push_back('*');
                }
            }
        }
        if(!found) {
            break;
        }
        reverse(line.begin(), line.end());
        cout << line << "\n";
    }
    
    return 0;
}