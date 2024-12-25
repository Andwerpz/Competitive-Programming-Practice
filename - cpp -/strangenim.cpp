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

//AtCoder - ARC91F

//This is a nim like game problem. Note that the whole game is just the sum of a bunch of small games
//played on many piles, so if we can just compute the grundy number for each small pile, just take the
//xor sum and that's the number for the big pile. 

//With these grundy number problems, it's often sufficient to just generate the first 100 or so numbers,
//and guess at a pattern to quickly compute. In this case, if k|a, then the grundy number is a / k, 
//and the rest of the grundy numbers simply repeat the original sequence. 

//When we compute these grundy numbers, note that the complexity is actually bounded by sqrt(a) and
//not a. This is because we can take multiple steps at a time when the increment stays constant. 

int calc_mex(vi& a) {
    sort(a.begin(), a.end());
    int ans = 0;
    for(int x : a) ans += x == ans;
    return ans;
}

int calc_grundy(int a, int k) {
    vi g(a + 1, -1);
    for(int i = 0; i <= a; i++){
        vi next;
        for(int j = 1; j <= i / k; j++){
            next.push_back(g[i - j]);
        }
        g[i] = calc_mex(next);
    }
    return g[a];
}

int calc_grundy_fast(int a, int k) {
    if(a < k) return 0;
    if(a % k == 0) {
        return a / k;
    }
    int inc = a / k + 1;
    int diff = a - (a / k) * k;
    int mult = (diff + inc - 1) / inc;
    return calc_grundy_fast(a - inc * mult, k);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    int g = 0;
    for(int i = 0; i < n; i++){
        int a, k;
        cin >> a >> k;
        g ^= calc_grundy_fast(a, k);
    }
    cout << (g == 0? "Aoki" : "Takahashi") << "\n";
    
    return 0;
}