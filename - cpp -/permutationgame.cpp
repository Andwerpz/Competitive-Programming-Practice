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

//2025 Damascus University Programming Contest - E

//a permutation can be described as a collection of cycles. Note that once a cycle is chosen, the players will 
//alternate until all the nodes in the cycle are visited, then the next cycle will be chosen. 

//so the first player always wants to pick even cycles. It doesn't matter which order he picks the even cycles as
//he can adjust the parity so that he always comes out on top. 

//For the odd cycles, they will choose them in descending order of score delta. You can compute the score delta of 
//a odd cycle using some prefix sums. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vi p(n);
        for(int i = 0; i < n; i++) cin >> p[i];
        for(int i = 0; i < n; i++) p[i] --;
        ll ans = 0;
        vl odd(0);
        vb v(n, false);
        for(int i = 0; i < n; i++){
            if(v[i]) continue;
            int ptr = i;
            int cnt = 0;
            ll diff = 0;
            vl c;
            while(!v[ptr]) {
                v[ptr] = true;
                diff += (ptr + 1) * (cnt % 2? 1 : -1);
                c.push_back(ptr + 1);
                cnt ++;
                ptr = p[ptr];
            }
            diff = abs(diff);
            if(cnt % 2) {
                //find mxdiff
                ll sfx = 0;
                for(int j = c.size() - 1; j >= 0; j--){
                    sfx *= -1;
                    sfx += c[j];
                }
                diff = sfx;
                ll pfx = 0;
                for(int j = 0; j < c.size(); j++){
                    pfx *= -1;
                    pfx += c[j];
                    sfx -= c[j];
                    sfx *= -1;
                    diff = max(diff, pfx + sfx);
                }
                odd.push_back(diff);
            }   
            else ans += diff;
        }
        sort(odd.begin(), odd.end());
        reverse(odd.begin(), odd.end());
        for(int i = 0; i < odd.size(); i++) ans += odd[i] * (i % 2? -1 : 1);
        cout << ans << "\n";
    }
    
    return 0;
}