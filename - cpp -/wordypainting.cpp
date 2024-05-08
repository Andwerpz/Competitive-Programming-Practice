#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//UTPC Contest 03-22-24 Div. 1 - C

//just simulate it. For each cell, save a stack, and a frequency list. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    vector<vector<stack<char>>> s(n, vector<stack<char>>(n));
    vector<vector<map<char, int>>> f(n, vector<map<char, int>>(n));
    for(int i = 0; i < q; i++){
        int type;
        cin >> type;
        if(type == 0){
            char l;
            int r, c;
            cin >> l >> r >> c;
            f[r][c][l] ++;
            s[r][c].push(l);
        }
        else if(type == 1){
            int r, c;
            cin >> r >> c;
            if(s[r][c].size() == 0){
                continue;
            }
            char l = s[r][c].top();
            s[r][c].pop();
            f[r][c][l] --;
        }
        else if(type == 2){
            char l;
            int r, c;
            cin >> l >> r >> c;
            int cnt = f[r][c][l];
            int tot = s[r][c].size();
            cout << (2 * cnt > tot? "yes" : "no") << "\n";
        }
    }
    
    return 0;
}
