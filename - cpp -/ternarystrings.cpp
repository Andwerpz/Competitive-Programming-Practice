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

//AtCoder - ARC127B

//Since there must be n strings with the first letter being '2', we'll want to greedily minimize
//the rest of those strings, as the remaining strings will never be lexicographically larger
//than the ones that start with '2'. 

//How can we minimize them? Well, using the rest of the letters provided, we can simply just count
//from 0 to n in base 3. This gives us the minimal maximum string. In order to enforce that each
//column must have n of each character, we can just make the other two thirds rotations of the
//first third. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, l;
    cin >> n >> l;
    vvi ans(n * 3, vi(l, -1));
    //set the first n strings
    for(int i = 0; i < n; i++){
        ans[i][0] = 2;
        int tmp = i;
        for(int j = l - 1; j > 0; j--){
            ans[i][j] = tmp % 3;
            tmp /= 3;
        }
    }
    //rest of strings are simply rotations of the first n
    for(int i = n; i < 2 * n; i++){
        for(int j = 0; j < l; j++){
            ans[i][j] = (ans[i - n][j] + 1) % 3;
        }
    }
    for(int i = 2 * n; i < 3 * n; i++){
        for(int j = 0; j < l; j++){
            ans[i][j] = (ans[i - n][j] + 1) % 3;
        }
    }
    for(int i = 0; i < 3 * n; i++){
        for(int j = 0; j < l; j++){
            cout << ans[i][j];
        }
        cout << "\n";
    }
    
    return 0;
}