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

//Codeforces - 2122C

//note that we can rearrange the sum to something like this:
// \sum |x_a_i - x_b_i| + \sum |y_a_i - y_b_i|

//so an upper bound on the sum is if we separately pick pairs to maximize the x and y differences. 
//I'll show that we can actually pick pairs in 2D such that both x and y differences are maximized. 

// it's been so long that i've forgotten the proof, i'll leave it as an exercise to the reader :3

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<pair<pll, int>> a(n);
        for(int i = 0; i < n; i++) {
            cin >> a[i].first.first >> a[i].first.second;
            a[i].second = i;
        }
        sort(a.begin(), a.end());
        vector<pair<pll, int>> xl(n / 2), xh(n / 2);
        for(int i = 0; i < n; i++){
            if(i < n / 2) xl[i] = a[i];
            else xh[i - n / 2] = a[i];
        }
        sort(xl.begin(), xl.end(), [](pair<pll, int>& a, pair<pll, int>& b) -> bool {
            return a.first.second < b.first.second;
        });
        sort(xh.begin(), xh.end(), [](pair<pll, int>& a, pair<pll, int>& b) -> bool {
            return a.first.second > b.first.second;
        });
        ll dsum = 0;
        for(int i = 0; i < n / 2; i++){
            cout << xl[i].second + 1 << " " << xh[i].second + 1 << "\n";
            dsum += abs(xl[i].first.first - xh[i].first.first) + abs(xl[i].first.second - xh[i].first.second);
        }
        // cout << "DSUM : " << dsum << "\n";
    }
    
    return 0;
}