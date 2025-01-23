#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef array<int, 2> pii;
typedef array<ll, 2> pll;
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

//Codeforces - 2061A

//for the first even, we can either use one even number, or 2 odd numbers. After the first even, the remaining
//sum will always be odd, so we can't use any more even numbers, but 1 odd number will get one point. 

//so for the first number, we should use an even if possible, otherwise use 2 odds. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        int ecnt = 0, ocnt = 0;
        for(int i = 0; i < n; i++){
            int a;
            cin >> a;
            if(a % 2) ocnt ++;
            else ecnt ++;
        }
        int ans = 0;
        if(ecnt != 0) ans ++, ecnt --, ans += ocnt;
        else if(ocnt >= 2) ans ++, ocnt -= 2, ans += ocnt;
        cout << ans << "\n";
    }
    
    return 0;
}