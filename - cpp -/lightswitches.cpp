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

//Codeforces - 1993C

//since the behaviour of all switches is cyclic with period 2 * k, we can just check all 2 * k
//timesteps after max(a[i]), and if there doesn't exist a timestep with all lights on, then it 
//should never happen. 

//if we get the first times when each light switch will turn on / off after max(a[i]), then
//notice that we can simulate the behaviour of light switches in O(n) time by keeping a 
//count of on light switches. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        vi a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        int mxa = -1;
        vvi ev(2 * k, vi(0));
        for(int i = 0; i < n; i++){
            mxa = max(mxa, a[i]);
            ev[a[i] % (2 * k)].push_back(i);
            ev[(a[i] + k) % (2 * k)].push_back(i);
        }
        vb on(n, false);
        int oncnt = 0;
        for(int i = 0; i < n; i++){
            int diff = mxa - a[i];
            if((diff % (2 * k)) < k){
                on[i] = true;
                oncnt ++;
            }
        }
        if(oncnt == n){
            cout << mxa << "\n";
            continue;
        }
        int ans = -1;
        int ptr = mxa;
        for(int i = 0; i < 4 * k; i++){
            ptr ++;
            for(int j = 0; j < ev[ptr % (2 * k)].size(); j++){
                int ind = ev[ptr % (2 * k)][j];
                oncnt += on[ind]? -1 : 1;
                on[ind] = !on[ind];
            }
            if(oncnt == n){
                ans = ptr;
                break;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}