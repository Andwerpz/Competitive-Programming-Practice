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

//Codeforces - 1673F

//the idea is to use bits on each road such that the cumulative xor sum of x values can uniquely identify which
//building the thief is at currently. 

//consider a 1d case. If we label the nodes from left to right as 0, 1, 2, ..., n - 1, then between two nodes i
//and i + 1, we can just set the edge weight to be i ^ (i + 1). However, this will not minimize the sum of edge
//weights. Actually, we can use a gray code here, and that will minimize the sum, while still providing all values
//from 0 to n - 1. 

//for the 2D case, we can use a 2D gray code. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    vvi g(n, vi(n));
    vi rbits, cbits;
    for(int i = 0; i < 10; i++){
        rbits.push_back(i * 2 + 1);
        cbits.push_back(i * 2);
    }
    int wsum = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n - 1; j++){
            int diff = j ^ (j + 1);
            int w = 0;
            for(int bit = 0; bit < cbits.size(); bit++){
                if(diff & (1 << bit)) {
                    w = 1 << cbits[bit];
                }
            }
            wsum += w;
            g[i][j + 1] = g[i][j] ^ w;
            cout << w << " ";
        }
        cout << endl;
    }
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n; j++){
            int diff = i ^ (i + 1);
            int w = 0;
            for(int bit = 0; bit < rbits.size(); bit++){
                if(diff & (1 << bit)) {
                    w = 1 << rbits[bit];
                }
            }
            wsum += w;
            g[i + 1][j] = g[i][j] ^ w;
            cout << w << " ";
        }
        cout << endl;
    }
    int x = 0;
    for(int i = 0; i < k; i++){
        int _x;
        cin >> _x;
        x ^= _x;
        int r, c;
        for(int j = 0; j < n; j++){
            for(int _k = 0; _k < n; _k++){
                if(g[j][_k] == x) {
                    r = j + 1;
                    c = _k + 1;
                }
            }
        }
        cout << r << " " << c << endl;
    }
    
    return 0;
}