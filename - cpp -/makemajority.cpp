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
// typedef __int128 lll;
// typedef __float128 lld;

//Codeforces - 1988B

//we can first reduce any contiguous sequence of '0's into just 1 '0'. Then, if there are still more '0's than
//'1's, it's impossible, otherwise just select the entire string. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vi a(n);
        string line;
        cin >> line;
        for(int i = 0; i < n; i++){
            a[i] = line[i] - '0';
        }
        int zcnt = 0, ocnt = 0;
        for(int i = 0; i < n;){
            if(a[i] == 1){
                ocnt ++;
                i ++;
                continue;
            }
            int r = i;
            while(r != n && a[r] == 0){
                r ++;
            }
            i = r;
            zcnt ++;
        }
        cout << (ocnt > zcnt? "YES" : "NO") << "\n";
    }
    
    return 0;
}