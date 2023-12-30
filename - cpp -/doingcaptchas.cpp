#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ACPC 2023 Fall Contest D

//take note of the invariant: when we apply the operation to flip the 2x2 square of bits, the parity of the count
//of 'X's on each row and column affected doesn't change. 

//we can show that if the parity of every row and column is even, then it is always possible to solve the captcha. 

//then, in order to compute the minimum flips to fix the parity, we just count the number of odd parity
//rows, r, and odd parity columns, c, and the answer is just the max out of those two. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<int> r_cnt(n, 0);
    vector<int> c_cnt(m, 0);
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        for(int j = 0; j < m; j++){
            if(s[j] == 'X') {
                r_cnt[i] ++;
                c_cnt[j] ++;
            }
        }
    }
    int r = 0;
    int c = 0;
    for(int i = 0; i < n; i++){
        r += r_cnt[i] % 2;
    }
    for(int j = 0; j < m; j++){
        c += c_cnt[j] % 2;
    }
    cout << max(r, c) << "\n";
    
    return 0;
}
