#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1909F1

//the hardest part of this problem is coming up with a good way to visualize it, once you have that, the problem
//becomes pretty easy. 

//the visualization is described in the editorial, i'm more concerned with how one would come up with it in the
//first place.

//i suppose we could view the permutation as 'tokens' on a n by n grid. Each row and column can only have 1 token
//in it, and the permutation is formed by going from row 1 to n and reading the column numbers of each token. 

//Then, the constraints formed by the array 'a' are just squares of size 1 to n with all of their corners
//coinciding at the top left corner of the grid. The square of size 1 must have a[1] tokens, the square of size
//2 must have a[2] tokens, etc...

//Then, the problem is asking how many ways are there to arrange the tokens. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll mod = 998244353;
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        if(a[0] >= 2 || a[n - 1] != n) {
            cout << "0\n";
            continue;
        }
        ll nr_side = 0;
        ll ans = 1;
        for(int i = 0; i < n; i++){
            int nr = a[i];
            if(i != 0){
                nr -= a[i - 1];
            }
            if(nr == 0){
                nr_side ++;
                continue;
            }
            if(nr == 1){
                ans = (ans * (nr_side * 2 + 1)) % mod;
            }
            if(nr == 2){
                ans = (ans * (nr_side)) % mod;
                ans = (ans * (nr_side)) % mod;
                nr_side --;
            }
            if(nr > 2) {
                ans *= 0;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
