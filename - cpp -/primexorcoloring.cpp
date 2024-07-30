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

//Codeforces - 1991D

//for small n up to 6, we can just hard code the answer. They're even provided in the samples. 

//for larger n, we can just print "1 2 3 4" repeating. This works because when you xor a and b where
//a = b under mod 4, the result is a multiple of 4, which cannot be prime. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        if(n == 3){
            cout << "2\n1 2 2\n";
            continue;
        }
        vi ans(n);  
        for(int i = 0; i < n; i++){
            ans[i] = 2 + ((i + 1) % 2);
        }
        ans[0] = 1;
        for(int i = 2; i <= n; i++){
            if(i % 4 == 2 || i % 4 == 3){
                continue;
            }
            if(i + 2 > n){
                continue;
            }
            if(i % 2 == 1){
                ans[i - 1] = 1;
            }
            else {
                ans[i - 1] = 4;
            }
        }
        int ptr = 0;
        for(int i = 0; i < n; i++){
            ptr = max(ptr, ans[i]);
        }
        cout << ptr << "\n";
        for(int i = 0; i < n; i++){
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}