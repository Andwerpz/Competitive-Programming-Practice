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

//Codeforces - 1806B

//if the number of 0s is more than 1 + the number of non-zeroes, then you're forced to have a mex >= 1. 
//otherwise, you can always get a mex of 0. 

//the only case in which you'll have a mex of 2 is when you have an array of a bunch of 0s and 1s. 
//if you have a number greater than 1, you can guarantee a mex of 1. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vi a(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        int ocnt = 0;
        for(int i = 0; i < n; i++) ocnt += a[i] == 0;
        int nocnt = n - ocnt;
        if(nocnt == 0) {
            cout << "1\n";
            continue;
        }
        if(ocnt > nocnt + 1) {
            vi b(0);
            for(int i = 0; i < n; i++) if(a[i] != 0) b.push_back(a[i]);
            sort(b.begin(), b.end());
            reverse(b.begin(), b.end());
            if(b.size() != 0 && b[0] == 1) {
                cout << "2\n";
            }
            else {
                cout << "1\n";
            }
        }
        else {
            cout << "0\n";
        }
    }
    
    return 0;
}