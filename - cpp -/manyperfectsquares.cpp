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

//Codeforces - 1782D

//observe that we can compute the squareness of some x in O(n) time. 

//let's pick a pair of numbers a[i] and a[j], i < j, and force them to be perfect squares. Note that this actually 
//doesn't nail down the value of x, as we don't know how many squares are between them. 

//next, iterate over the amount of squares inbetween a[i] + x and a[j] + x. Note that if a[j] - a[i] is odd, then
//there must be an odd amount of squares between them, otherwise there must be an even amount. 

//lets say we're testing some gap k. How do we find x given a[i], a[j], and k? We can first derive this equation:
//a[j] - a[i] = k * (k - 1) + y * k. 
//y is the initial difference. 
//k * (k - 1) accounts for the arithmetic progression we get from adjacent differences of squares. 

//Solving for y we get y = (a[j] - a[i]) / k - (k - 1). Now a few things have to be true. 
//1. y must be an integer, this means that (a[j] - a[i]) must be divisible by k. 
//2. (y - 1)^2 >= a[i]. In other words, x >= 0 or a[i] must be less than the square we're boosting it up to. 
//3. y >= 0. 

//if all three are true, then we can say that x = (y - 1)^2, and test it. 

//A note on complexity. My rudimentary analysis gives around n^3 * sqrt(10^9), because we're testing every pair 
//of numbers, we have around sqrt(10^9) differences we need to test per pair, and every x we test costs
//n. This comes out to around 3 * 10^9 for n = 50, but ig there are some constant factors that I failed to 
//consider that allow this to run relatively fast (500 ms). 

int test_x(vl& a, ll x){
    // cout << "TEST X : " << x << "\n";
    int ans = 0;
    for(int i = 0; i < a.size(); i++){
        ll cur = a[i] + x;
        ll sq = floor(sqrt(cur));
        // cout << "CUR : " << cur << " " << (sq * sq == cur) << "\n";
        ans += sq * sq == cur;
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vl a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        int ans = 1;
        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++){
                ll diff = a[j] - a[i];
                ll amt = 2 - (diff % 2);
                while(true){
                    // cout << "AMT : " << amt << endl;
                    ll x = diff / amt - (amt - 1);
                    ll tmp = (x - 1) / 2;
                    if(x <= 0 || tmp * tmp < a[i]) {
                        break;
                    }
                    if((x % 2) != 1 || diff % amt != 0){
                        amt += 2;
                        continue;
                    }
                    ll psq = tmp * tmp;
                    ans = max(ans, test_x(a, psq - a[i]));
                    amt += 2;
                }
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}