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

//Codeforces - 1998A

//just make all points horizontal to the target center. If k is odd, then you need to place a point on the center. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int x, y, k;
        cin >> x >> y >> k;
        int ptr = 1;
        if(k % 2 == 1){
            cout << x << " " << y << "\n";
            k --;
        }
        for(int i = 0; i < k / 2; i++){
            cout << x + ptr << " " << y << "\n" << x - ptr << " " << y << "\n";
            ptr ++;
        }
    }
    
    return 0;
}