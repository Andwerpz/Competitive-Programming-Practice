#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef array<int, 2> pii;
typedef array<ll, 2> pll;
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

//Codeforces - 2061B

//a non-degenerate isosceles trapezoid can be made from sides of length a, b, c, c, where 2 * c > abs(a - b). 

//there are two cases:
// - there exists two disjoint pairs of sides that are equal. In this case, we can just form a rectangle
// - otherwise, there is only one pair of sides that are equal. Take this pair, and see if we can find sides
//   a and b that satisfy the condition. Since we want to minimize abs(a - b), we can just consider all adjacent
//   side length pairs in the sorted order. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vi a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        int eq_cnt = 0;
        for(int i = 0; i < n - 1;){
            if(a[i] == a[i + 1]) eq_cnt ++, i += 2;
            else i ++;
        }
        array<int, 4> ans = {-1, -1, -1, -1};
        if(eq_cnt >= 2) {
            for(int i = 0; i < n - 1;) {
                if(a[i] == a[i + 1]) {
                    if(ans[0] == -1) ans[0] = a[i], ans[1] = a[i];
                    else ans[2] = a[i], ans[3] = a[i];
                    i += 2;
                }
                else i ++;
            }
        }
        else if(eq_cnt == 1){
            int eq_ind = -1;
            for(int i = 0; i < n - 1; i++){
                if(a[i] == a[i + 1]) eq_ind = i;
            }
            vi b(0);
            for(int i = 0; i < n; i++) if(i != eq_ind && i != eq_ind + 1) b.push_back(a[i]);
            // cout << "BSIZE : " << b.size() << endl;
            for(int i = 0; i < b.size() - 1; i++){
                if(a[eq_ind] * 2 > b[i + 1] - b[i]) ans = {a[eq_ind], a[eq_ind], b[i], b[i + 1]};
            }
        }
        if(ans[0] == -1) cout << "-1\n";
        else cout << ans[0] << " " << ans[1] << " " << ans[2] << " " << ans[3] << "\n";
    }
    
    return 0;
}