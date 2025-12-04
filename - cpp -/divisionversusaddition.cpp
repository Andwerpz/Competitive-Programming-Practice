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

//Codeforces - 2152D

//some intuition:
// - +1 moves are the most powerful on small numbers. 
// - therefore divide moves make +1 moves more powerful. 
// - Poby can guarantee that any number equal to a power of 2 can't gain an extra move. 
// - Rekkles can guarantee that any number not a power of 2 and at least 2 greater than the next lowest power of 2
//    can gain an extra move. 

//so the only edge case are numbers that are not a power of 2 and are exactly 1 greater than the next lowest 
//of 2. For these numbers, if Poby does a move, then they become powers of 2, and if Rekkles does a move, then
//they can guarantee an extra move. So initially they will fight over all these numbers, and the rest of
//the game is guaranteed. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int n, q;
        cin >> n >> q;
        vi a(n);
        vi s(n, 0), p2(n, 0);
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            if(__builtin_popcount(a[i]) == 2 && (a[i] % 2)) {
                p2[i] = 1;
            }
            int tmp = a[i];
            while(tmp != 1) {
                s[i] ++;
                tmp /= 2;
            }
            if(__builtin_popcount(a[i]) >= 2 && !p2[i]) {
                s[i] ++;
            }
        }
        vi spfx(n + 1, 0), p2pfx(n + 1, 0);
        for(int i = 1; i <= n; i++) {
            spfx[i] = spfx[i - 1] + s[i - 1];
            p2pfx[i] = p2pfx[i - 1] + p2[i - 1];
        }
        while(q--) {
            int l, r;
            cin >> l >> r;
            l --;
            int cs = spfx[r] - spfx[l];
            int cp2 = p2pfx[r] - p2pfx[l];
            cout << (cs + cp2 / 2) << "\n";
        }
    }
    
    return 0;
}