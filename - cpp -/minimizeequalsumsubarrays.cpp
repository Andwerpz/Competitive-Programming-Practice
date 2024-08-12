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

//Codeforces - 1998B

//note that if you make q equal to p shifted over by 1 (with the end element wrapping around), no subarray sums will be 
//equal, except for the subarray that is the entire array. 

//this is because if you consider some subarray [l, r], and an adjacent subarray [l + 1, r + 1], they will not have
//the same sums in a permutation. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vi p(n);
        for(int i = 0; i < n; i++){
            cin >> p[i];
        }
        for(int i = 0; i < n; i++){
            cout << p[(i + 1) % n] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}