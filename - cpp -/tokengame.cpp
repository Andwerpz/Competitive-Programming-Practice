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

//ICPC NAC 2021 - K

//first, let's establish a loss condition. Observe that we lose by the rules of the game if one token is at (1, 1) and
//the other is directly adjacent to it, so at (1, 2) or (2, 1). Notice that if the tokens are ever starting out directly
//adjacent, the second player to move can always make them adjacent again no matter what the first player does. This
//is our loss condition. 

//So if the first player can make the tokens directly adjacent, they win. This means that if abs(x1 - x2) <= 1 or
//abs(y1 - y2) <= 1, we can directly compute who will win. 

//so the remaining cases is where both abs(x1 - x2) > 1 and abs(y1 - y2) > 1. Observe that the first player to violate
//this rule loses, so we can make a new nim game where if you violate this rule, you lose. Observe that in this new
//game, the two tokens can actually never block each other, so we're free to consider the x and y axes independently. 

//for some axis, there are N^2 states, and computing the grundy value for that state is O(N), so O(N^3) total. Finally,
//to answer each query we can just iterate through all the moves. 

bool is_adj(int x1, int x2, int y1, int y2) {
    return (x1 == x2 && abs(y1 - y2) <= 1) || (y1 == y2 && abs(x1 - x2) <= 1);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    const int N = 300;
    vvi g(N, vi(N, -1));   
    vb v(2 * N, false);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(abs(i - j) <= 1) continue;
            for(int k = 0; k < 2 * N; k++) v[k] = false;
            //where can i move
            for(int k = 0; k < i; k++) if(abs(k - j) > 1) v[g[k][j]] = true;
            //where can j move
            for(int k = 0; k < j; k++) if(abs(i - k) > 1) v[g[i][k]] = true;
            int mex = 0;
            for(int k = 0; k < 2 * N; k++){
                if(!v[k]) break;
                mex = k + 1;
            }
            g[i][j] = mex;
        }
    }
    int t;
    cin >> t;
    while(t--){
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1 --, x2 --, y1 --, y2 --;
        int ans = 0;
        for(int i = 0; i < x1; i++){
            if(x1 > x2 && y1 == y2 && i <= x2) continue;
            if(abs(i - x2) <= 1 || abs(y1 - y2) <= 1) {
                ans += is_adj(i, x2, y1, y2);
                continue;
            }
            ans += (g[i][x2] ^ g[y1][y2]) == 0;
        }
        for(int i = 0; i < x2; i++){
            if(x2 > x1 && y1 == y2 && i <= x1) continue;
            if(abs(x1 - i) <= 1 || abs(y1 - y2) <= 1) {
                ans += is_adj(x1, i, y1, y2);
                continue;
            }
            ans += (g[x1][i] ^ g[y1][y2]) == 0;
        }
        for(int i = 0; i < y1; i++){
            if(y1 > y2 && x1 == x2 && i <= y2) continue;
            if(abs(x1 - x2) <= 1 || abs(i - y2) <= 1) {
                ans += is_adj(x1, x2, i, y2);
                continue;
            }
            ans += (g[x1][x2] ^ g[i][y2]) == 0;
        }
        for(int i = 0; i < y2; i++){
            if(y2 > y1 && x1 == x2 && i <= y1) continue;
            if(abs(x1 - x2) <= 1 || abs(y1 - i) <= 1) {
                ans += is_adj(x1, x2, y1, i);
                continue;
            }
            ans += (g[x1][x2] ^ g[y1][i]) == 0;
        }
        cout << ans << "\n";
    }
    
    return 0;
}