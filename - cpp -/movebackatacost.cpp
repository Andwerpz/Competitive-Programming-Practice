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

//Codeforces - 2046B

//we can solve with max 1 swap per element. 

//an element needs to swap if there is an element behind it which is greater than it. First, identify
//all elements needing to be swapped (note that after swapping an element, new elements can become needing
//to be swapped)

//since it's always possible to sort the array given correct swapping order, you can just add 1 to all needed to 
//be swapped elements, and sort the array. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vl a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        //find minimum element to move
        ll sfx_min = 1e9 + 100;
        ll mn_move = 1e9 + 100;
        for(int i = n - 1; i >= 0; i--){
            sfx_min = min(sfx_min, a[i]);
            if(a[i] != sfx_min) {
                mn_move = min(mn_move, a[i]);
            }
        }
        //mark which elements we are moving
        sfx_min = 1e9 + 100;
        vb ism(n, false);
        for(int i = n - 1; i >= 0; i--){
            sfx_min = min(sfx_min, a[i]);
            if(a[i] != sfx_min || a[i] > mn_move + 1){
                a[i] ++;
            }
        }
        sort(a.begin(), a.end());
        for(int i = 0; i < n; i++){
            cout << a[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}