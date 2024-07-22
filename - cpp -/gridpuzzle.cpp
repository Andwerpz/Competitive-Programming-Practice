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
// typedef __int128 lll;
// typedef __float128 lld;

//Codeforces - 1990D

//the only pattern where you can save an operation using the 2x2 grid is when there is one 
//a[i] either 1 or 2, then an even amount of a[i] 3 or 4, followed by another 1 or 2. Just greedily take
//as many such patterns. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vi a(n + 1, 0);
        int ans = 0;
        set<int> s;
        int gsize = 0;
        for(int i = 0; i < n; i++){
            cin >> a[i];
            if(a[i] != 0){
                ans ++;
            }
        }
        for(int i = 0; i < n;){
            if(a[i] == 0 || a[i] > 2){
                i ++;
                continue;
            }
            int r = i + 1;
            int cnt = 0;
            while(r != n && (a[r] == 3 || a[r] == 4)){
                cnt ++;
                r ++;
            }
            if(r == n || a[r] > 2 || a[r] == 0 || cnt % 2 == 1){
                i ++;
                continue;
            }
            ans --;
            i = r + 1;
        }
    }
    
    return 0;
}