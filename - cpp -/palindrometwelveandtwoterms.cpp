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

//Codeforces - 2234B

//convenient mod is convenient. 
//observe that 12 is a convenient mod, for every number < 12 (except 10), they are all palindromes. 

//we have a + b = n
//rewriting we get a = n - b
//since b is a multiple of 12, we can say equivalently that a = n (mod 12), a <= n. 

//so for n % 12 != 10, we can just assign a = n % 12.
//for n % 12 = 10, then the smallest palindrome we can do is a = 22, so the only case
//that is impossible is n = 10. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        ll n;
        cin >> n;
        if(n == 10) {
            cout << "-1\n";
            continue;
        }
        ll a = n % 12;
        if(a == 10) a += 12;
        ll b = n - a;
        cout << a << " " << b << "\n";
    }
    
    return 0;
}