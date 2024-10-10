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

//Calgary 2022 - G

//implementation

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    string line;
    getline(cin, line);
    while(!cin.eof()) {
        char c = line[0];
        int cnt = 1;
        for(int i = 1; i < line.size(); i++){
            if(line[i] != c){
                cout << cnt << c;
                c = line[i];
                cnt = 0;
            }
            cnt ++;
        }
        cout << cnt << c << "\n";
        getline(cin, line);
    }
    
    return 0;
}