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

//Codeforces - 1930C

//each element a[i] starts at the value a[i] + i. Then, we can either take it as it is, or 
//take some elements before it and then take it. Taking elements before it effectively lowers the value of a[i]
//by 1 every time we do so, so for any element, we can redeem it's value in the range a[i] + i to a[i] + 1. 

//Due to the pidgeonhole principle, there is always a way to make the size of S equal to n. Therefore, we just 
//have to sort the values in descending order of a[i] + i, and greedily take the largest ones. 

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
            a[i] = a[i] + i + 1;
        }
        sort(a.begin(), a.end());
        reverse(a.begin(), a.end());
        for(int i = 1; i < n; i++){
            a[i] = min(a[i - 1] - 1, a[i]);
        }
        for(int i = 0; i < n; i++){
            cout << a[i] << " \n"[i == n - 1];
        }
    }
    
    return 0;
}