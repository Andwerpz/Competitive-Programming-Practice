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

//Codeforces - 1783B

//first, note that the number of differences that we can make is n^2 - 1, namely 1, 2, 3, ..., n^2 - 1. 

//next, consider solving the problem on a 1D array. It's pretty easy to see that if you arrange the values like
//1, n^2, 2, n^2 - 2, ..., then you'll actually get all the possible differences. 

//finally, if we just wind the 1D array around the matrix, then we'll get the maximum amount of differences
//in the matrix, solving the problem. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        int l = 1;
        int r = n * n;
        bool flag = false;
        vvi ans(n, vi(n));
        for(int i = 0; i < n; i++){
            if(i % 2 == 0){
                for(int j = 0; j < n; j++){
                    if(!flag){
                        ans[i][j] = l ++;
                    }
                    else {
                        ans[i][j] = r --;
                    }
                    flag = !flag;
                }
            }
            else {
                for(int j = n - 1; j >= 0; j--){
                    if(!flag){
                        ans[i][j] = l ++;
                    }
                    else {
                        ans[i][j] = r --;
                    }
                    flag = !flag;
                }
            }
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                cout << ans[i][j] << " ";
            }
            cout << "\n";
        }
    }
    
    return 0;
}