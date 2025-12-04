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

//UTPC Contest 10-15-25 Div.1 - D

//alot of impl D:

int ctoi(char c) {
    if(c == 'V') return 0;
    else if(c == '>') return 1;
    else if(c == '^') return 2;
    else if(c == '<') return 3;
    assert(false);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<string> g(2);
    cin >> g[0] >> g[1];
    for(int i = 0; i < n; i++) {
        char a = g[0][i * 2];
        char b = g[1][i * 2];
        char c = g[0][i * 2 + 1];
        int ind = -1;
        if(b == '.' && c == '.') {
            ind = ctoi(a);
        }
        else if(b != '.') {
            ind = 4 + 4 * ctoi(b) + ctoi(a);
        }
        else if(c != '.') {
            ind = 4 + 16 + 4 * ctoi(a) + ctoi(c);
        }
        else assert(false);
        assert(ind != -1);
        // cout << "IND : " << ind << " ";
        if(ind < 26) cout << (char) ('A' + ind);
        else {
            ind -= 26;
            cout << ind;
        }
    }
    cout << "\n";
    
    return 0;
}