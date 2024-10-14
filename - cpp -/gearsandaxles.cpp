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

//2024 ICPC NAQ - G

//for each set of gears of the same size, we want to assign the largest gear to the smallest, 
//second largest to second smallest, and so on. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    map<int, vi> m;
    for(int i = 0; i < n; i++){
        int s, c;
        cin >> s >> c;
        m[s].push_back(c);
    }
    ld ans = 0;
    for(auto i = m.begin(); i != m.end(); i++){
        vi a = i->second;
        sort(a.begin(), a.end());
        int l = 0;
        int r = a.size() - 1;
        while(l < r){
            // cout <<" LR : " << l << " " << r << "\n";
            ld ratio = (ld) a[r] / (ld) a[l];
            // cout << "ASDF : " << a[r] << " " << a[l] << "\n";
            // cout << "R : " << r << "\n";
            ans += log(ratio);
            l ++;
            r --;
        }
    }
    cout << fixed << setprecision(10) << ans << "\n";
    
    return 0;
}