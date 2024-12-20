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

//AtCoder - ARC151C

//Let's consider each chunk of unmarked squares seperately. Since the entire game is simply the sum
//of games played on each of these chunks, if we can find the grundy number for each chunk
//individually, then we can xor them to find the grundy number for the entire game. 

//For chunks that are flanked by two different numbers, it will always take an even amount of moves
//to complete the game. This is because when placing a number anywhere, you split it into an even and
//odd section, but since you spent a move, the odd section cancels out. Therefore, the grundy
//number is 0 (first player always loses)

//For chunks that are flanked by two same numbers, it will always take an odd amount of moves. 
//Therefore, the grundy number is 1 (first player always wins)

//For chunks that have a set number only on one side, the grundy number is n (where n is the size
//of the chunk). We can prove this via induction. 

//For chunks that have no set numbers on either side, the grundy number is n / 2. We can prove this 
//by looking at the grundy number for the chunks that have 1 set side. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n, m;
    cin >> n >> m;
    vl x(m), y(m);
    for(int i = 0; i < m; i++){
        cin >> x[i] >> y[i];
    }
    if(m == 0) {
        cout << (n % 2? "Takahashi" : "Aoki") << "\n";
        return 0;
    }
    ll g = 0;
    for(int i = 0; i < m - 1; i++){
        if(y[i + 1] == y[i]) g ^= 1;
    }
    g ^= x[0] - 1;
    g ^= n - x[m - 1];
    cout << (g != 0? "Takahashi" : "Aoki") << "\n";
    
    return 0;
}