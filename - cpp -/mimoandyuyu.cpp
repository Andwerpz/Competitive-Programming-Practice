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

//Codeforces - 2155E

//nice grundy game exercise

//for n = 1, all moves are forced so we can compute the result directly. Actually, the only thing that matters 
//is the number of tokens on column 1. 

//for n >= 2, moves are not forced so we have to do some analysis. 
//observe that if there are an even amount of tokens on each column, then Yuyu can always win as they just need
//to change the parity of each column back to even after Mimo's move. 

//Otherwise, there must exist a column with an odd amount of tokens. Mimo can then make the parity of every column
//even, and then guarantee a win. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m, k;
        cin >> n >> m >> k;
        map<int, int> f;
        for(int i = 0; i < k; i++) {
            int r, c;
            cin >> r >> c;
            r --, c --;
            f[c] ++;
        }
        bool mimo_win;
        if(n >= 2) {
            mimo_win = false;
            for(auto i = f.begin(); i != f.end(); i++) {
                if(i->first == 0) continue;
                if(i->second % 2) mimo_win = true;
            }
        }
        else {
            mimo_win = f[1] % 2;
        }
        cout << (mimo_win ? "Mimo" : "Yuyu") << "\n";
    }
    
    return 0;
}