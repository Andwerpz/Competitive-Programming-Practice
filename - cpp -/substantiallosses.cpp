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

//Meta Hacker Cup 2024 Round 1 - C

//If we're currently at our minimum weight W, we want to compute the expected time to get to weight W - 1. 
//If we can find that, then the answer is simply (W - G) times that. 

//For simplicity, lets say that we currently weight 0, and we want to get to -1. E[x] = expected amount of time
//to get to weight -1 starting from weight x. 

//obviously, E[-1] = 0, and for most x, E[x] = (E[x - 1] + E[x + 1]) / 2 + 1. 
//the exception is E[L] = E[L - 1] + 1, as we cannot go to L + 1. This is actually our way in to solve the problem:
//E[L - 1] = (E[L] + E[L - 2]) / 2 + 1
//2E[L - 1] = E[L - 1] + E[L - 2] + 3
//E[L - 1] = E[L - 2] + 3

//we can see that this pattern repeats : E[L - 2] = E[L - 3] + 5, and in general, E[L - N] = E[L - N - 1] + N * 2 + 1
//Therefore, E[0] = E[-1] + L * 2 + 1 = L * 2 + 1. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ifstream in("--in--.txt");
    streambuf *cinbuf = cin.rdbuf(); //save old buf
    cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
    
    ofstream out("--out--.txt");
    streambuf *coutbuf = cout.rdbuf(); //save old buf
    cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

    ll mod = 998244353;
    int t;
    cin >> t;
    int casi = 0;
    while(t--){
        casi ++;
        ll g, w, l;
        cin >> w >> g >> l;
        ll ans = (2ll * l + 1) % mod;
        ans = (ans * ((w - g) % mod)) % mod;
        cout << "Case #" << casi << ": " << ans << "\n";
    }
    
    return 0;
}